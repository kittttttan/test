package ktn.gui;

import java.awt.event.ActionListener;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.JMenu;
import javax.swing.JRadioButtonMenuItem;

public class RadioMenu extends JMenu {
    private static final long serialVersionUID = 1L;
    
    private ButtonGroup group;

    public RadioMenu(String s, Object[] values) {
        super(s);
        
        group = new ButtonGroup();
        for (int i = 0; i < values.length; ++i) {
            JRadioButtonMenuItem item = new JRadioButtonMenuItem(String.valueOf(values[i]));
            group.add(item);
            this.add(item);
        }
    }
    
    public void setSelectedIndex(int index) {
        int i = 0;
        for (Enumeration<AbstractButton> en = group.getElements(); en.hasMoreElements(); ++i) {
            JRadioButtonMenuItem radio = (JRadioButtonMenuItem) en.nextElement();
            if (i == index) {
                radio.setSelected(true);
                break;
            }
        }
    }
    
    @Override
    public void addActionListener(ActionListener l) {
        for (Enumeration<AbstractButton> en = group.getElements(); en.hasMoreElements(); ) {
            JRadioButtonMenuItem radio = (JRadioButtonMenuItem) en.nextElement();
            radio.addActionListener(l);
        }
    }
}
