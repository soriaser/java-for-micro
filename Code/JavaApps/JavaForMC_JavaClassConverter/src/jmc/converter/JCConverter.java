package jmc.converter;

import java.io.File;
import java.io.IOException;
import java.util.Vector;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.ClassFormatException;
import org.apache.bcel.classfile.ClassParser;
import org.apache.bcel.classfile.ConstantClass;
import org.apache.bcel.classfile.ConstantMethodref;
import org.apache.bcel.classfile.ConstantNameAndType;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.ConstantUtf8;
import org.apache.bcel.classfile.JavaClass;
import org.apache.bcel.classfile.Method;

import jmc.converter.api.JMCAPIUtil;
import jmc.converter.file.jmc.JMCFile;
import jmc.converter.file.jmc.JMCFileClass;
import jmc.converter.file.jmc.JMCFileField;
import jmc.converter.file.jmc.JMCFileMethod;

public class JCConverter {

    /**
     * Starts class to JMC converter.
     *
     * @param args At least one argument containing *.class file path
     */
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Invalid input arguments");
            System.exit(0);
        }

        Vector<Integer> methodRefIndexMap = new Vector<Integer>();

        Vector<Integer> fieldRefs = new Vector<Integer>();
        
        JMCFileClass jmcFileClass = null;

        try {
            JavaClass javaClass = (new ClassParser(args[0])).parse();
            ConstantPool pool = javaClass.getConstantPool();

            // First of all it is required to record all necessary data from
            // constant pool table stored in class file. What does it checks?
            //
            // + If Method_ref is found:
            //                  - It checks if it is an API method. In that
            //                    case, index to constant pool is mapped with
            //                    API method identifier
            //
            // + If Field_ref is found:
            //                  - Index is stored
            for (int index = 1; index < pool.getLength(); index++) {
                byte type = pool.getConstant(index).getTag();
                int idx = 0;

                switch (type) {
                case Constants.CONSTANT_Methodref:
                    // Get method ref
                    ConstantMethodref methodRef =
                        (ConstantMethodref) pool.getConstant(index);

                    // Get name index in constant pool
                    idx = ((ConstantClass)
                        pool.getConstant(methodRef.getClassIndex()))
                        .getNameIndex();

                    // Get method ref name
                    String name =
                        ((ConstantUtf8) pool.getConstant(idx)).getBytes();

                    // If name contains the JMC API package name, it means that
                    // it is a method ref to an API method, then index shall
                    // be mapped
                    if (name.contains(JMCAPIUtil.JMC_API_PACKAGE)) {
                        // An integer is used as index map using following
                        // information for every integer byte:
                        //
                        // | Byte 3 | Byte 2 | Byte 1 | Byte 0 |
                        // -------------------------------------
                        // | Cst. pool index |    API index    |

                        // Store constant pool index
                        int map = ((idx << 16) & 0xFFFF0000);

                        // Get method name
                        idx = ((ConstantNameAndType)
                            pool.getConstant(methodRef.getNameAndTypeIndex()))
                            .getNameIndex();

                        // Store corresponding API method index
                        map |= (JMCAPIUtil.getJMCAPIMethodId(
                            JMCAPIUtil.getJMCAPIPackageId(name),
                            ((ConstantUtf8) pool.getConstant(idx))
                                .getBytes()) & 0x0000FFFF
                            );

                        // Store in map of index vector which stores all
                        // index found during class parsing
                        methodRefIndexMap.add(map);
                    }
                    
                    break;
                case Constants.CONSTANT_Fieldref:
                    // Add field to vector
                    fieldRefs.add(new Integer(index));
                    break;
                }
            }

            // Starts to create JMC file data
            jmcFileClass = new JMCFileClass(); 

            // Add all field refs
            for (int field = 0; field < fieldRefs.size(); field++) {
                byte id = fieldRefs.get(field).byteValue();
                jmcFileClass.addField(new JMCFileField(id));
            }

            // Get methods from class file
            Method methods[] = javaClass.getMethods();

            // For every method in class file:
            //
            // 1. Check if it is a java.mc.MicroApplication method:
            //          - java.mc.MicroApplication.<init>
            //          - java.mc.MicroApplication.main
            //          - java.mc.MicroApplication.onLoad
            //          - java.mc.MicroApplication.sleep
            //
            // 2. If is java.mc.MicroApplication method, API method ID
            //    id used as method ID
            //
            // 3. If is not java.mc.MicroApplication method, method index in
            //    array is used as ID.
            for (int method = 0; method < methods.length; method++) {
                int idx = methods[method].getNameIndex();
                String name = ((ConstantUtf8) pool.getConstant(idx)).getBytes();

                // If method is java.mc.MicroApplication method, id will be
                // different from 0xFFFF.
                short id = JMCAPIUtil.getJMCAPIMethodId(
                        JMCAPIUtil.ID_PACKAGE_MICROAPPLICATION, name);

                // If is not a java.mc.MicroApplication method, index (without
                // take into account most siginifcant bit) is set as id
                switch (id) {
                case JMCAPIUtil.ID_METHOD_INIT:
                case JMCAPIUtil.ID_METHOD_MAIN:
                case JMCAPIUtil.ID_METHOD_ONLOAD:
                case JMCAPIUtil.ID_METHOD_SLEEP:
                    break;
                default:
                    id = (short) (method & 0x7FFF);
                    break;
                }

                // Create new JMCFileMethod and replace required bytes in
                // its bytecode
                JMCFileMethod jmcFileMethod = new JMCFileMethod(id,
                        methods[method].getCode().getCode());
                jmcFileMethod.replaceMethodRefsInCode(methodRefIndexMap);

                // Add method to JMC class
                jmcFileClass.addMethod(jmcFileMethod);
            }

        } catch (ClassFormatException | IOException exception) {
            System.out.println("Error");
            System.exit(0);
        }

        if (jmcFileClass != null) {
            JMCFile jmcFile = new JMCFile();
            jmcFile.addClass(jmcFileClass);

            String fileName = (new File(args[0])).getAbsolutePath();

            if (fileName.contains(".")) {
                fileName = fileName.substring(0, fileName.lastIndexOf("."));
            }

            fileName += ".jmc";

            jmcFile.createOutputFile(fileName);
        }
    }

}
