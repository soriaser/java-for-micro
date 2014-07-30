package jmc.converter.file.jmc;

import java.util.Vector;

public class JMCFile {

    private Vector<JMCFileClass> classes = new Vector<JMCFileClass>();

    public JMCFile() {}

    public void addClass(JMCFileClass jmcClass) {
        this.classes.add(new JMCFileClass(jmcClass));
    }

    public JMCFileClass getClass(int index) {
        return this.classes.get(index);
    }

    public int getNumberOfClasses() {
        return this.classes.size();
    }
}
