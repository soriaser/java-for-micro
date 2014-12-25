package jmc.converter;

import java.util.Vector;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.Constant;
import org.apache.bcel.classfile.ConstantFieldref;
import org.apache.bcel.classfile.ConstantNameAndType;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.JavaClass;
import org.apache.bcel.classfile.Field;

public class JCFieldMap {

    private static Vector<JCField> fields = new Vector<JCField>();

    public static void add(JCField field) {
        fields.add(field);
    }

    public static void fill(JavaClass javaclasses[]) {
        for (int ii = 0; ii < javaclasses.length; ii++) {
            ConstantPool pool = javaclasses[ii].getConstantPool();
            Constant constants[] = pool.getConstantPool();

            for (int jj = 1; jj < constants.length; jj++) {
                if (Constants.CONSTANT_Fieldref == constants[jj].getTag()) {
                    int index = ((ConstantFieldref) 
                            constants[jj]).getNameAndTypeIndex();
                    String name = ((ConstantNameAndType)
                            constants[index]).getName(pool);
                    String type = ((ConstantNameAndType)
                            constants[index]).getSignature(pool);
                    String namePackage = ((ConstantFieldref) 
                            constants[jj]).getClass(pool);

                    byte id = 0x00;

                    Field fields[] = javaclasses[ii].getFields();
                    for (int kk = 0; kk < fields.length; kk++) {
                        if ((fields[kk].getName().equals(name)) &&
                                (fields[kk].getSignature().equals(type))) {
                            id = (byte) kk;
                            break;
                        }
                    }

                    add(new JCField(name, namePackage, type, (short) jj,
                            id, (byte) ii));
                }
            }
        }
    }


    public static short getFieldId(short index) {
        for (int ii = 0; ii < fields.size(); ii++) {
            if (fields.get(ii).getIndex() == index) {
                return fields.get(ii).getID();
            }
        }

        throw new InternalError("Field index not found");
    }

}
