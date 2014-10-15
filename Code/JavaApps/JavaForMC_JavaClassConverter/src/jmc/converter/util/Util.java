package jmc.converter.util;

public class Util {

    public static String byte2HexString(byte value) {
        StringBuilder strBuilder = new StringBuilder(2);
        strBuilder.append(String.format("%02X", value & 0xFF));

        return strBuilder.toString().toUpperCase();
    }

    public static String byteArray2HexString(byte array[]) {
        String str = "";

        for (int ii = 0; ii < array.length; ii++) {
            str += Util.byte2HexString(array[ii]);
        }

        return str;
    }
}
