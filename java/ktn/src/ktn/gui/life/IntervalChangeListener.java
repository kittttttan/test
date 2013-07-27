package ktn.gui.life;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Logger;

import javax.swing.JRadioButtonMenuItem;
import javax.swing.Timer;

public class IntervalChangeListener implements ActionListener {
    private static Logger logger = Logger.getLogger(IntervalChangeListener.class.getName());
    
    @Override
    public void actionPerformed(ActionEvent e) {
        final JRadioButtonMenuItem item = (JRadioButtonMenuItem) e.getSource();
        final String text = item.getText();

        try {
            final int ms = Integer.parseInt(text);
            logger.fine("interval: "+ ms);

            final LifeFrame frame = Life.getInstance().getFrame();
            final LifePanel panel = (LifePanel) frame.getContentPane();
            final Timer timer = panel.getTimer();
            timer.setDelay(ms);
            timer.setInitialDelay(ms);
        } catch (NumberFormatException ex) {
            logger.warning(ex.toString());
        }
    }
}
