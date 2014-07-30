package jmc.converter.api;

/**
 * Library containing IDs, packages and methods names.
 *
 * ID is composed by 2 bytes: MSB usually contains package information
 * and LSB contains the specific method information
 * 
 *                                MSB
 * -----------------------------------------------------------------
 * | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
 * -----------------------------------------------------------------
 * |   0   |   -   |   -   |   -   |   -   |   -   |   -   |   -   |
 * |   1   |   -   |   -   |   -   |   -   |   -   |   -   |   -   | API
 * |   1   |   X   |   X   |   X   |   -   |   -   |   -   |   -   | Package
 * |   1   |   -   |   -   |   -   |   X   |   X   |   X   |   X   | RFU
 *
 *
 *                                LSB
 * -----------------------------------------------------------------
 * | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
 * -----------------------------------------------------------------
 * |   X   |   X   |   X   |   X   |   X   |   X   |   X   |   X   | Method ID
 */
public class JMCAPIUtil {

    /** MSB JMC version byte */
    static final public byte JMC_VERSION_MSB = (byte) 0x00;

    /** LSB JMC version byte */
    static final public byte JMC_VERSION_LSB = (byte) 0x01;

    /** "java.mc" API common package name */
    static final public String JMC_API_PACKAGE = "java/mc";

    /** "java.mc.MicroApplication" API package name */
    static final public String PACKAGE_MICROAPPLICATION =
            JMC_API_PACKAGE + "/MicroApplication";

    /** "java.mc.ports" API package name */
    static final public String PACKAGE_PORTS = 
            JMC_API_PACKAGE + "/ports";

    /** "java.mc.MicroApplication./<init/>" method name */
    static final public String METHOD_INIT = "<init>";

    /** "java.mc.MicroApplication.main" method name */
    static final public String METHOD_MAIN = "main";

    /** "java.mc.MicroApplication.onLoad" method name */
    static final public String METHOD_ONLOAD = "onLoad";

    /** "java.mc.MicroApplication.sleep" method name */
    static final public String METHOD_SLEEP = "sleep";

    // Package IDs:
    //
    //                                MSB
    // -----------------------------------------------------------------
    // | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
    // -----------------------------------------------------------------
    // |   0   |   -   |   -   |   -   |   -   |   -   |   -   |   -   |
    // |   1   |   -   |   -   |   -   |   -   |   -   |   -   |   -   | API
    // |   1   |   X   |   X   |   X   |   -   |   -   |   -   |   -   | Pckg
    // |   1   |   -   |   -   |   -   |   X   |   X   |   X   |   X   | RFU

    /** ID for "java.mc.MicroApplication" (0x00) */
    static final public short ID_PACKAGE_MICROAPPLICATION = (short) 0x0000;

    // Method IDs:
    //
    //                                LSB
    // -----------------------------------------------------------------
    // | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
    // -----------------------------------------------------------------
    // |   X   |   X   |   X   |   X   |   X   |   X   |   X   |   X   |

    /** ID for "java.mc.MicroApplication./<init/>" (0x00) */
    static final public short ID_METHOD_INIT = (short) 0x0000;

    /** ID for "java.mc.MicroApplication.main" (0x01) */
    static final public short ID_METHOD_MAIN = (short) 0x0001;

    /** ID for "java.mc.MicroApplication.onLoad" (0x02) */
    static final public short ID_METHOD_ONLOAD = (short) 0x0002;

    /** ID for "java.mc.MicroApplication.sleep" (0x03) */
    static final public short ID_METHOD_SLEEP = (short) 0x0003;

    /**
     * Returns short containing MSB information depending on package name.
     *
     * @param name Package name to identify.
     * @return Short containing MSB information.
     */
    public static short getJMCAPIPackageId(String name) {
        short id = (short) 0x8000;

        if (name.contains(PACKAGE_MICROAPPLICATION)) {
            return (short) (id | ID_PACKAGE_MICROAPPLICATION);
        }

        return (short) 0xFFFF;
    }

    /**
     * Adds and returns short containing MSB provided from package id and LSB
     * containing information depending on method name.
     *
     * @param id Package ID information (MSB byte).
     * @param name Method name to identify.
     * @return Short containing ID.
     */
    public static short getJMCAPIMethodId(short id, String name) {
        switch (id) {
        case ID_PACKAGE_MICROAPPLICATION:
            if (name.contains(METHOD_INIT)) {
                return (short) (id | ID_METHOD_INIT);
            }

            if (name.contains(METHOD_MAIN)) {
                return (short) (id | ID_METHOD_MAIN);
            }
            
            if (name.contains(METHOD_ONLOAD)) {
                return (short) (id | ID_METHOD_ONLOAD);
            }

            if (name.contains(METHOD_SLEEP)) {
                return (short) (id | ID_METHOD_SLEEP);
            }
            break;
        }

        return -1;
    }
}
