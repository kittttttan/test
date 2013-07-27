package ktn.beta.sample1;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import static java.awt.RenderingHints.KEY_ANTIALIASING;
import static java.awt.RenderingHints.VALUE_ANTIALIAS_ON;

public class Sample {
    private static Logger logger = Logger.getLogger(Sample.class.getName());
    
    private static final String TEXT_FILE = "assets/test.txt";
    private static final String PNG_FILE = "assets/test.png";

    /**
     * @param args
     */
    public static void main(String[] args) {
        SampleThread st = new SampleThread();
        Thread t = new Thread(st);
        t.start();

        for (int i = 1; i < 7; i += 2) {
            logger.info(String.format("%d", i));
        }

        try {
            t.join(77);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        logger.info("奈々!!");

        BufferedImage img = new BufferedImage(240, 240,
                BufferedImage.TYPE_INT_RGB);
        blueImage(img);

        File file = new File(PNG_FILE);
        try {
            ImageIO.write(img, "PNG", file);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            writeText();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            logger.info(readText());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void blueImage(BufferedImage img) {
        int w = img.getWidth();
        int h = img.getHeight();
        int d = (w * w + h * h);

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                img.setRGB(x, y, 255 - 255 * (x * x + y * y) / d);
            }
        }

        Graphics2D g = img.createGraphics();
        g.setRenderingHint(KEY_ANTIALIASING, VALUE_ANTIALIAS_ON);
        g.setColor(Color.GREEN);
        g.drawArc(w / 4, h / 4, w / 2, h / 2, 0, 360);
        g.dispose();
    }

    public static void writeText() throws IOException {
        FileOutputStream fos = new FileOutputStream(TEXT_FILE, true);
        try (OutputStreamWriter out = new OutputStreamWriter(fos, "UTF-8")) {
            out.write("水樹奈々\n");
        }
    }

    public static String readText() throws IOException {
        StringBuffer buf = new StringBuffer();
        FileInputStream fis = new FileInputStream(TEXT_FILE);
        try (
            InputStreamReader in = new InputStreamReader(fis, "UTF-8");
            BufferedReader reader = new BufferedReader(in);
        ) {
            String str = null;
            while ((str = reader.readLine()) != null) {
                buf.append(str);
                buf.append("\n");
            }
        }

        return buf.toString();
    }

    public static class SampleThread implements Runnable {
        @Override
        public void run() {
            for (int i = 0; i < 7; i += 2) {
                logger.info(String.format("%d", i));
            }
        }
    }
}
