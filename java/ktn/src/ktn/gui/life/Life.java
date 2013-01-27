package ktn.gui.life;

import java.awt.EventQueue;

public class Life {
    private static Life window;
    private LifeFrame frame;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    window = new Life();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the application.
     */
    private Life() {
        initialize();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        frame = new LifeFrame();
    }

    public static Life getInstance() {
        return window;
    }

    public LifeFrame getFrame() {
        return frame;
    }
}
