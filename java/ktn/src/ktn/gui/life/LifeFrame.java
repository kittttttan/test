package ktn.gui.life;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JFileChooser;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.Timer;

import java.awt.event.KeyEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.logging.Logger;

import ktn.gui.RadioMenu;
import java.awt.event.InputEvent;
import java.io.File;

public class LifeFrame extends JFrame {
    private static final long serialVersionUID = 1L;
    private static Logger logger = Logger.getLogger(LifeFrame.class.getName());
    
    private LifePanel contentPane;
    private JMenuBar menuBar;
    private JMenu mnFilef;
    private RadioMenu mnInterval;
    private RadioMenu mnSize;
    private JMenuItem mntmStart;
    private JMenuItem mntmExitx;
    private JMenuItem mntmReset;
    private JMenuItem mntmOpen;
    private JMenuItem mntmSave;

    /**
     * Create the frame.
     */
    public LifeFrame() {
        setTitle("Life");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 417, 466);

        menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        mnFilef = new JMenu("File");
        mnFilef.setMnemonic('F');

        mntmExitx = new JMenuItem("Exit");
        mntmExitx.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0));
        mntmExitx.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        mntmStart = new JMenuItem("Start/Stop");
        mntmStart.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F5, 0));
        mntmStart.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                final Timer timer = contentPane.getTimer();
                if (timer.isRunning()) {
                    logger.info("stop");
                    timer.stop();
                } else {
                    logger.info("start");
                    timer.restart();
                }
            }
        });
        
        mntmOpen = new JMenuItem("Open");
        mntmOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, InputEvent.CTRL_MASK));
        mntmOpen.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                final Timer timer = contentPane.getTimer();
                if (timer.isRunning()) {
                    logger.info("stop");
                    timer.stop();
                }
                
                JFileChooser filechooser = new JFileChooser();
                FileFilter filter = new FileNameExtensionFilter("Text", "txt");
                filechooser.addChoosableFileFilter(filter);
                filechooser.setFileFilter(filter);
                
                int selected = filechooser.showOpenDialog(contentPane);
                switch (selected) {
                case JFileChooser.APPROVE_OPTION:
                    if (!contentPane.getCells().load(filechooser.getSelectedFile())) {
                        logger.warning("failed load");
                    }
                    contentPane.repaint();
                    break;
                case JFileChooser.CANCEL_OPTION:
                    logger.info("Cancel");
                    break;
                case JFileChooser.ERROR_OPTION:
                    logger.info("Error");
                    break;
                }
            }
        });
        
        mntmReset = new JMenuItem("Reset");
        mntmReset.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_R, 0));
        mntmReset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                contentPane.reset();
            }
        });
        
        mntmSave = new JMenuItem("Save");
        mntmSave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, InputEvent.CTRL_MASK));
        mntmSave.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                final Timer timer = contentPane.getTimer();
                if (timer.isRunning()) {
                    logger.info("stop");
                    timer.stop();
                }
                
                JFileChooser filechooser = new JFileChooser();
                FileFilter filterExcel = new FileNameExtensionFilter("Excel (*.xls)", "xls");
                FileFilter filterText = new FileNameExtensionFilter("Text (*.txt)", "txt");
                filechooser.addChoosableFileFilter(filterExcel);
                filechooser.addChoosableFileFilter(filterText);
                filechooser.setFileFilter(filterText);
                
                int selected = filechooser.showSaveDialog(contentPane);
                switch (selected) {
                case JFileChooser.APPROVE_OPTION:
                    File file = filechooser.getSelectedFile();
                    FileFilter ff = filechooser.getFileFilter();
                    boolean done = false;
                    if (ff.equals(filterExcel)) {
                    //if (file.getName().toLowerCase().endsWith(".xls")) {
                        done = contentPane.getCells().saveAsExcel(file);
                    } else {
                        done = contentPane.getCells().save(file);
                    }
                    if (!done) {
                        logger.warning("failed save");
                    }
                    break;
                case JFileChooser.CANCEL_OPTION:
                    logger.info("Cancel");
                    break;
                case JFileChooser.ERROR_OPTION:
                    logger.info("Error");
                    break;
                }
            }
        });
        
        mnFilef.add(mntmOpen);
        mnFilef.add(mntmSave);
        mnFilef.addSeparator();
        mnFilef.add(mntmStart);
        mnFilef.add(mntmReset);
        mnFilef.addSeparator();
        mnFilef.add(mntmExitx);
        menuBar.add(mnFilef);

        mnInterval = new RadioMenu("Interval", new Integer[]{ 33, 67, 100, 200, 500, 1000 });
        mnInterval.setSelectedIndex(2);
        mnInterval.addActionListener(new IntervalChangeListener());
        mnInterval.setMnemonic('I');
        menuBar.add(mnInterval);
        
        mnSize = new RadioMenu("Size", new Integer[]{ 4, 6, 8, 10 });
        mnSize.setMnemonic('S');
        mnSize.setSelectedIndex(1);
        mnSize.addActionListener(new SizeChangeListener());
        menuBar.add(mnSize);

        contentPane = new LifePanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        contentPane.setLayout(new BorderLayout(0, 0));
        setContentPane(contentPane);
    }

}
