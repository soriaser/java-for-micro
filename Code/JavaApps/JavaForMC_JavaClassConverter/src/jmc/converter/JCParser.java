package jmc.converter;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.ConstantInteger;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.JavaClass;
import org.apache.bcel.classfile.Method;
import org.apache.bcel.generic.Type;

public class JCParser {

    public static byte getNumberOfArguments(Method method) {
        int arguments = 0;

        Type[] types = method.getArgumentTypes();

        for (int ii = 0; ii < types.length; ii++) {
            switch (types[ii].getType()) {
            case Constants.T_BYTE:
            case Constants.T_CHAR:
            case Constants.T_SHORT:
            case Constants.T_BOOLEAN:
                arguments++;
                break;
            case Constants.T_ARRAY:
                break;
            default:
                throw new InternalError("Argument not allowed");
            }
        }

        if (arguments > 255) {
            String message = "Number of arguments exceed maximum allowed";
            throw new InternalError(message);
        }

        return (byte) arguments;
    }

    public static short getNumberOfConstants(JavaClass javaclasses[],
            byte types[]) {
        short constants = 0;

        for (int ii = 0; ii < javaclasses.length; ii++) {
            constants += getNumberOfConstants(javaclasses[ii], types);
        }

        return constants;
    }

    public static short getNumberOfConstants(JavaClass javaclass,
            byte types[]) {
        return getNumberOfConstants(javaclass.getConstantPool(), types);
    }

    public static short getNumberOfConstants(ConstantPool pools[],
            byte types[]) {
        short constants = 0;

        for (int ii = 0; ii < pools.length; ii++) {
            constants += getNumberOfConstants(pools[ii], types);
        }

        return constants;
    }

    public static short getNumberOfConstants(ConstantPool pool, byte types[]) {
        short constants = 0;

        for (int jj = 0; jj < (int) pool.getLength(); jj++) {
            if (pool.getConstant(jj) != null) {
                for (int kk = 0; kk < (int) types.length; kk++) {
                    if (types[kk] == pool.getConstant(jj).getTag()) {
                        constants++;
                    }
                }
            }
        }

        return constants;
    }

    public static byte getNumberOfMethods(JavaClass javaclasses[], short flags) {
        int methods = 0;

        for (int ii = 0; ii < javaclasses.length; ii++) {
            methods += getNumberOfMethods(javaclasses[ii], flags);
        }

        if (methods > 255) {
            throw new InternalError("Number of methods exceed maximum allowed");
        }

        return (byte) methods;
    }

    public static byte getNumberOfMethods(JavaClass javaclass, short flags) {
        int methods = 0;

        for (int ii = 0; ii < (int) javaclass.getMethods().length; ii++) {
            if (javaclass.getMethods()[ii] != null) {
                if (((javaclass.getMethods()[ii].getAccessFlags() & flags) ==
                        flags) || (flags == (short) 0xFFFF)) {
                    methods++;
                }
            }
        }

        if (methods > 255) {
            throw new InternalError("Number of methods exceed maximum allowed");
        }

        return (byte) methods;
    }

    public static byte getNumberOfFields(JavaClass javaclasses[], short flags) {
        int fields = 0;

        for (int ii = 0; ii < javaclasses.length; ii++) {
            fields += getNumberOfFields(javaclasses[ii], flags);
        }

        if (fields > 255) {
            throw new InternalError("Number of fields exceed maximum allowed");
        }

        return (byte) fields;
    }

    public static byte getNumberOfFields(JavaClass javaclass, short flags) {
        int fields = 0;

        for (int ii = 0; ii < (int) javaclass.getFields().length; ii++) {
            if (javaclass.getFields()[ii] != null) {
                if (((javaclass.getFields()[ii].getAccessFlags() & flags) ==
                        flags) || (flags == (short) 0xFFFF)) {
                    fields++;
                }
            }
        }

        if (fields > 255) {
            throw new InternalError("Number of fields exceed maximum allowed");
        }

        return (byte) fields;
    }

    public static short[] getNumberValues(JavaClass javaclasses[],
            byte types[]) {
        int offset = 0;
        short values[] = new short[getNumberOfConstants(javaclasses, types)];

        for (int ii = 0; ii < javaclasses.length; ii++) {
            short poolValues[] = getNumberValues(javaclasses[ii], types);

            for (int jj = 0; jj < poolValues.length; jj++) {
                values[offset] = poolValues[jj];
                offset++;
            }
        }

        return values;
    }

    public static short[] getNumberValues(JavaClass javaclass, byte types[]) {
        return getNumberValues(javaclass.getConstantPool(), types);
    }

    public static short[] getNumberValues(ConstantPool pools[], byte types[]) {
        int offset = 0;
        short values[] = new short[getNumberOfConstants(pools, types)];

        for (int ii = 0; ii < pools.length; ii++) {
            short poolValues[] = getNumberValues(pools[ii], types);

            for (int jj = 0; jj < poolValues.length; jj++) {
                values[offset] = poolValues[jj];
                offset++;
            }
        }

        return values;
    }

    public static short[] getNumberValues(ConstantPool pool, byte types[]) {
        int offset = 0;
        String message = "";
        short values[] = new short[getNumberOfConstants(pool, types)];

        for (int jj = 0; jj < (int) pool.getLength(); jj++) {
            if (pool.getConstant(jj) != null) {
                for (int kk = 0; kk < (int) types.length; kk++) {
                    if (types[kk] == pool.getConstant(jj).getTag()) {
                        switch (types[kk]) {
                        case Constants.CONSTANT_Integer:
                            values[offset] = (short) ((ConstantInteger)
                                    pool.getConstant(jj)).getBytes();

                            if (values[offset] > Short.MAX_VALUE) {
                                message  = "Constant value exceeds maximum";
                                message += " short value";
                                throw new InternalError(message);
                            }

                            break;
                        default:
                            message = "Constant type not allowed";
                            throw new InternalError(message);
                        }
                        
                        offset++;
                    }
                }
            }
        }

        return values;
    }

    public static String[] getStringValues(JavaClass javaclasses[],
            byte types[]) {
        int offset = 0;
        String values[] = new String[getNumberOfConstants(javaclasses, types)];

        for (int ii = 0; ii < javaclasses.length; ii++) {
            String poolValues[] = getStringValues(javaclasses[ii], types);

            for (int jj = 0; jj < poolValues.length; jj++) {
                values[offset] = poolValues[jj];
                offset++;
            }
        }

        return values;
    }

    public static String[] getStringValues(JavaClass javaclass, byte types[]) {
        return getStringValues(javaclass.getConstantPool(), types);
    }

    public static String[] getStringValues(ConstantPool pools[], byte types[]) {
        int offset = 0;
        String values[] = new String[getNumberOfConstants(pools, types)];

        for (int ii = 0; ii < pools.length; ii++) {
            String poolValues[] = getStringValues(pools[ii], types);

            for (int jj = 0; jj < poolValues.length; jj++) {
                values[offset] = poolValues[jj];
                offset++;
            }
        }

        return values;
    }

    public static String[] getStringValues(ConstantPool pool, byte types[]) {
        int offset = 0;
        String message = "";
        String values[] = new String[getNumberOfConstants(pool, types)];

        for (int jj = 0; jj < (int) pool.getLength(); jj++) {
            if (pool.getConstant(jj) != null) {
                for (int kk = 0; kk < (int) types.length; kk++) {
                    if (types[kk] == pool.getConstant(jj).getTag()) {
                        switch (types[kk]) {
                        case Constants.CONSTANT_String:
                            values[offset] = pool.getConstantString(jj,
                                    Constants.CONSTANT_String);
                            break;
                        default:
                            message = "Constant type not allowed";
                            throw new InternalError(message);
                        }
                        
                        offset++;
                    }
                }
            }
        }

        return values;
    }

}
