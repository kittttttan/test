package ktn.gui.life;

import java.awt.Graphics;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.logging.Logger;

public class LifeCells {
    private static Logger logger = Logger.getLogger(LifeCells.class.getName());

    private int width;
    private int height;
    private int[][] cells;
    private int[][] temp;
    private int generation;

    public LifeCells() {
        this(16, 16);
    }

    public LifeCells(int w) {
        this(w, w);
    }

    public LifeCells(int w, int h) {
        width = w;
        height = h;
        cells = new int[height][width];
        temp = new int[height][width];

        reset();
    }

    public boolean load(File file) {
        boolean res = false;
        assert file != null : "file is null";
        logger.info(file.getPath());

        try (FileInputStream fis = new FileInputStream(file);
                InputStreamReader isr = new InputStreamReader(fis, "UTF-8");
                BufferedReader br = new BufferedReader(isr)) {
            String line;
            int i = 0;
            while ((line = br.readLine()) != null) {
                // logger.info(line);
                final int loop = line.length() < width ? line.length() : width;
                for (int j = 0; j < loop; ++j) {
                    if (line.charAt(j) == 'O') {
                        cells[i][j] = 1;
                    } else {
                        cells[i][j] = 0;
                    }
                }
                ++i;
                if (i >= height) {
                    break;
                }
            }
            res = true;
        } catch (FileNotFoundException e) {
            logger.severe(e.getMessage());
        } catch (IOException e) {
            logger.severe(e.getMessage());
        }
        
        return res;
    }

    public boolean save(File file) {
        boolean res = false;
        assert file != null : "file is null";
        logger.info(file.getPath());
        
        try (FileOutputStream fos = new FileOutputStream(file);
                OutputStreamWriter osw = new OutputStreamWriter(fos, "UTF-8");
                BufferedWriter bw = new BufferedWriter(osw)) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (cells[i][j] > 0) {
                        bw.write('O');
                    } else {
                        bw.write('.');
                    }
                }
                bw.newLine();
            }

            res = true;
        } catch (FileNotFoundException e) {
            logger.severe(e.getMessage());
        } catch (IOException e) {
            logger.severe(e.getMessage());
        }
        
        return res;
    }

    public void reset() {
        generation = 0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j] = 0;
                temp[i][j] = 0;
            }
        }
    }

    public void resize(int w, int h) {
        if (w == width && h == height) {
            return;
        }

        // copy
        int[][] newCells = new int[h][w];
        temp = new int[h][w];

        for (int i = 0; i < h; ++i) {
            if (i < height) {
                for (int j = 0; j < w; ++j) {
                    newCells[i][j] = j < width ? cells[i][j] : 0;
                    temp[i][j] = 0;
                }
            } else {
                for (int j = 0; j < w; ++j) {
                    newCells[i][j] = 0;
                    temp[i][j] = 0;
                }
            }
        }

        // swap
        int[][] t = cells;
        cells = newCells;
        newCells = t;

        width = w;
        height = h;
    }

    private int around(int y, int x) {
        int sum = 0;

        sum += cells[(y < 1 ? height : y) - 1][(x < 1 ? width : x) - 1];
        sum += cells[(y < 1 ? height : y) - 1][x];
        sum += cells[(y < 1 ? height : y) - 1][(x > width - 2 ? 0 : x + 1)];

        sum += cells[y][(x < 1 ? width : x) - 1];
        // sum += cells[y][x];
        sum += cells[y][(x > width - 2 ? 0 : x + 1)];

        sum += cells[(y > height - 2 ? 0 : y + 1)][(x < 1 ? width : x) - 1];
        sum += cells[(y > height - 2 ? 0 : y + 1)][x];
        sum += cells[(y > height - 2 ? 0 : y + 1)][(x > width - 2 ? 0 : x + 1)];

        return sum;
    }

    public int next() {
        int a = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                a = around(i, j);
                temp[i][j] = (a == 3 || (a == 2 && (cells[i][j] > 0))) ? 1 : 0;
            }
        }

        // swap
        int[][] t = cells;
        cells = temp;
        temp = t;

        ++generation;
        return generation;
    }

    public void draw(Graphics g, int size) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (cells[i][j] > 0) {
                    g.fillRect(size * j, size * i, size - 1, size - 1);
                }
            }
        }
    }

    public int inc(int x, int y) throws ArrayIndexOutOfBoundsException {
        cells[y][x] = cells[y][x] > 0 ? 0 : 1;

        return cells[y][x];
    }

    public int[][] getCells() {
        return cells;
    }

    public int getGeneration() {
        return generation;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }
}
