package ktn.gui.life;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Logger;

import javax.swing.JRadioButtonMenuItem;

public class SizeChangeListener implements ActionListener {
    private static Logger logger = Logger.getLogger(SizeChangeListener.class.getName());

    @Override
    public void actionPerformed(ActionEvent e) {
        final JRadioButtonMenuItem item = (JRadioButtonMenuItem) e.getSource();
        final String text = item.getText();

        try {
            final int size = Integer.parseInt(text);
            logger.info("size: "+ size);

            final LifeFrame frame = Life.getInstance().getFrame();
            final LifePanel panel = (LifePanel) frame.getContentPane();
            panel.setCellSize(size);
            panel.resizeCells();
            panel.repaint();
        } catch (NumberFormatException ex) {
            logger.warning(ex.toString());
        }
     }
}
