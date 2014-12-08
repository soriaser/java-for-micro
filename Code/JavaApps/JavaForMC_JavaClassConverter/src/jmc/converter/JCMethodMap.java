package jmc.converter;

import java.util.Vector;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.Constant;
import org.apache.bcel.classfile.ConstantMethodref;
import org.apache.bcel.classfile.ConstantNameAndType;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.JavaClass;
import org.apache.bcel.classfile.Method;

public class JCMethodMap {

    private static Vector<JCMethod> methods = new Vector<JCMethod>();

    public static void add(JCMethod method) {
        methods.add(method);
    }

    public static void fill(JavaClass javaclasses[]) {
        for (int ii = 0; ii < javaclasses.length; ii++) {
            ConstantPool pool = javaclasses[ii].getConstantPool();
            Constant constants[] = pool.getConstantPool();

            for (int jj = 1; jj < constants.length; jj++) {
                if (Constants.CONSTANT_Methodref == constants[jj].getTag()) {
                    int index = ((ConstantMethodref) 
                            constants[jj]).getNameAndTypeIndex();
                    String name = ((ConstantNameAndType)
                            constants[index]).getName(pool);
                    String type = ((ConstantNameAndType)
                            constants[index]).getSignature(pool);
                    String namePackage = ((ConstantMethodref) 
                            constants[jj]).getClass(pool);

                    byte id = 0x00;

                    Method methods[] = javaclasses[ii].getMethods();
                    for (int kk = 0; kk < methods.length; kk++) {
                        if ((methods[kk].getName().equals(name)) &&
                                (methods[kk].getSignature().equals(type))) {
                            id = (byte) kk;
                            break;
                        }
                    }

                    add(new JCMethod(name, namePackage, type, (short) jj,
                            id, (byte) ii));
                }
            }
        }
    }


    public static short getMethodId(short index) {
        for (int ii = 0; ii < methods.size(); ii++) {
            if (methods.get(ii).getIndex() == index) {
                return methods.get(ii).getID();
            }
        }

        throw new InternalError("Method index not found");
    }

}
