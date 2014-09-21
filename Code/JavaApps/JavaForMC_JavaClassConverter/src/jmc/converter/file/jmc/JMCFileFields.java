package jmc.converter.file.jmc;

import java.util.Vector;

public class JMCFileFields extends JMCFileTLV {

    private Vector<JMCFileField> fields = new Vector<JMCFileField>();

    public final static int LENGTH_SIZE = 1;

    public JMCFileFields() {
        this.tag = JMCFileConstants.TAG_FIELDS;
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileFields(JMCFileFields fields) {
        this.tag = fields.getTag();
        this.fields = fields.getFields();
        this.lengthSize = LENGTH_SIZE;
    }

    public void addField(JMCFileField field) {
        fields.add(new JMCFileField(field));
    }

    public JMCFileField getField(int index) {
        return fields.get(index);
    }

    public Vector<JMCFileField> getFields() {
        return new Vector<JMCFileField>(this.fields);
    }

    public int getNumberOfFields() {
        return fields.size();
    }

    @Override
    public int getLength() {
        int length = 0;

        for (int ii = 0; ii < this.fields.size(); ii++) {
            // Get length from TLV and add length bytes and tag
            //length += this.fields.get(ii).getLength() + this.lengthSize + 1;
        }

        return length;
    }

    @Override
    public String getValue() {
        String value = "";

        for (int ii = 0; ii < this.fields.size(); ii++) {
            // Get length from TLV and add length (1 byte) and tag
            //value += this.fields.get(ii).getTLV();
        }

        return value;
    }
}
