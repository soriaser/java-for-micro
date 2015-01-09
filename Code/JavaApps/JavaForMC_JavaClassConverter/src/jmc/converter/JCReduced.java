package jmc.converter;

import org.apache.bcel.classfile.JavaClass;

import com.sun.org.apache.bcel.internal.Constants;

public class JCReduced {

    private final static byte VERSION = 0x01;

    public final static byte SIZE_CONSTANT = 2;

    public final static byte SIZE_STRING_INDEX = 2;    

    private JCReducedMethod jcReducedMethods[];

    private JCReducedClass  jcReducedClasses[];

    private short  jcReducedConstants[];

    private byte   jcReducedConstantsTypes[] = {Constants.CONSTANT_Integer};

    private String jcReducedStrings[];

    private byte   jcReducedStringsTypes[] = {Constants.CONSTANT_String};

    private byte   jcReducedStaticFields = 0;

    public JCReduced(JavaClass javaclasses[]) {
        this.jcReducedMethods = new JCReducedMethod[JCParser.getNumberOfMethods(
                javaclasses, JCParser.ALL_FLAGS)];

        this.jcReducedClasses = new JCReducedClass[javaclasses.length];

        this.jcReducedConstants = JCParser.getNumberValues(javaclasses,
                this.jcReducedConstantsTypes);

        this.jcReducedStrings = JCParser.getStringValues(javaclasses,
                this.jcReducedStringsTypes);

        this.jcReducedStaticFields = JCParser.getNumberOfFields(javaclasses,
                (int) Constants.ACC_STATIC);

        int method = 0;

        for (int ii = 0; ii < javaclasses.length; ii++) {
            this.jcReducedClasses[ii] = new JCReducedClass((byte) ii);

            this.jcReducedClasses[ii].setStaticFields(
                    JCParser.getNumberOfFields(javaclasses[ii],
                            Constants.ACC_STATIC));

            if (!(javaclasses[ii].getSuperclassName().equals(
                    JCReducedConstants.API_PACKAGE_MICROAPPLICATION)) && 
                !(javaclasses[ii].getSuperclassName().equals(
                    JCReducedConstants.API_PACKAGE_OBJECT))) {
                throw new InternalError("Inheritance not supported yet");
            }

            for (byte jj = 0; jj < javaclasses[ii].getMethods().length; jj++) {
                this.jcReducedMethods[method] = new JCReducedMethod(
                        javaclasses[ii].getMethods()[jj], (byte) method,
                        (byte) ii);

                if (this.jcReducedMethods[method].isMain()) {
                    this.jcReducedClasses[ii].setAsMain(true);
                }

                method++;
            }

            if ((javaclasses[ii].getSuperclassName().equals(
                    JCReducedConstants.API_PACKAGE_MICROAPPLICATION)) &&
                    !(this.jcReducedClasses[ii].isMain())) {
                String message  = "Only main class can extend";
                       message += "Microaplication object";
                throw new InternalError(message);
            }
        }
    }

    public short getAllStringsSize() {
        int size = 0;

        for (int ii = 0; ii < this.jcReducedStrings.length; ii++) {
            size += this.jcReducedStrings[ii].getBytes().length;
        }

        if (size > Short.MAX_VALUE) {
            String message = "All Strings values toghether exceed maximum";
            message += "allowed";
            throw new InternalError(message);
        }

        return (short) size;
    }

    public JCReducedClass getClass(int index) {
        return this.jcReducedClasses[index];
    }

    public short getConstant(int index) {
        return this.jcReducedConstants[index];
    }

    public byte getMainMethodIndex() {
        for (int ii = 0; ii < this.jcReducedMethods.length; ii++) {
            if (this.jcReducedMethods[ii].isMain()) {
                return this.jcReducedMethods[ii].getId();
            }
        }

        throw new InternalError("Main method does not found");
    }

    public JCReducedMethod getMethod(int index) {
        return this.jcReducedMethods[index];
    }

    public byte getNumberOfMethods() {
        return (byte) this.jcReducedMethods.length;
    }

    public byte getNumberOfClasses() {
        return (byte) this.jcReducedClasses.length;
    }

    public short getNumberOfConstants() {
        return (byte) this.jcReducedConstants.length;
    }

    public byte getNumberOfStaticFields() {
        return this.jcReducedStaticFields;
    }

    public short getNumberOfStrings() {
        return (byte) this.jcReducedStrings.length;
    }

    public byte getVersion() {
        return VERSION;
    }

}
