package ktn.gui.life;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;
import javax.swing.Timer;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.util.logging.Logger;

public class LifePanel extends JPanel {
    private static final long serialVersionUID = 1L;
    private static Logger logger = Logger.getLogger(LifePanel.class.getName());

    private LifeCells cells = new LifeCells(64);
    private int cellSize = 6;
    private int generation = 0;

    private Timer timer = new Timer(100, new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            repaint();
            generation = cells.next();
        }
    });

    /**
     * Create the panel.
     */
    public LifePanel() {
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                LifePanel panel = (LifePanel) e.getSource();
                panel.resizeCells();
            }
        });
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                Point p = e.getPoint();
                final int x = p.x / cellSize;
                final int y = p.y / cellSize;
                logger.info("mouse: ("+ x +","+ y +")");
                try {
                    cells.inc(x, y);
                    repaint();
                } catch (ArrayIndexOutOfBoundsException ex) {
                    logger.warning(ex.toString());
                }
            }
        });
    }
    
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.setColor(Color.black);
        g.fillRect(0, 0, getWidth(), getHeight());

        g.setColor(Color.yellow);
        cells.draw(g, cellSize);
        
        g.setColor(Color.white);
        g.drawString("generation: " + generation, 10, 20);
    }
    
    public void reset() {
        logger.info("reset");
        
        cells.reset();
        generation = 0;
        repaint();
    }
    
    public void resizeCells() {
        final int width = getWidth();
        final int height = getHeight();
        final int w = width / cellSize;
        final int h = height / cellSize;
        
        cells.resize(w, h);
        logger.info("resize: "+ width +"x"+ height);
    }

    public Timer getTimer() {
        return timer;
    }

    public int getCellSize() {
        return cellSize;
    }

    public void setCellSize(int cellSize) {
        this.cellSize = cellSize;
    }

    public LifeCells getCells() {
        return cells;
    }
}
