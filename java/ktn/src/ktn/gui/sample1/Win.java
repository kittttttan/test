package ktn.gui.sample1;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.math.BigInteger;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import java.awt.BorderLayout;
import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import java.awt.Component;
import javax.swing.SwingConstants;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

import ktn.Big;
import ktn.Prime;

public class Win {
    private static enum ExeType {
        FIBONACCI, FACTORIAL, PRIME
    };

    private JFrame frmKtn;
    private JTextField textFieldInput;
    private JTextArea textArea;
    private JScrollPane scrollPane;
    private JPanel panel;
    private JLabel lblMs;
    private JComboBox<ExeType> comboBox;
    private JPanel panel_1;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    Win window = new Win();
                    window.frmKtn.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the application.
     */
    public Win() {
        initialize();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        frmKtn = new JFrame();
        frmKtn.setTitle("ktn");
        frmKtn.setBounds(100, 100, 264, 260);
        frmKtn.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frmKtn.getContentPane().setLayout(new BorderLayout(0, 0));

        textArea = new JTextArea();
        textArea.setLineWrap(true);
        textArea.setEditable(false);
        textArea.setRows(8);
        textArea.setColumns(10);

        scrollPane = new JScrollPane(textArea);
        frmKtn.getContentPane().add(scrollPane);

        panel = new JPanel();
        frmKtn.getContentPane().add(panel, BorderLayout.NORTH);
        panel.setLayout(new BorderLayout(0, 0));

        comboBox = new JComboBox<ExeType>();
        comboBox.setModel(new DefaultComboBoxModel<ExeType>(ExeType.values()));
        comboBox.setSelectedIndex(0);
        panel.add(comboBox, BorderLayout.NORTH);

        panel_1 = new JPanel();
        panel.add(panel_1);
        panel_1.setLayout(new BoxLayout(panel_1, BoxLayout.X_AXIS));

        textFieldInput = new JTextField();
        textFieldInput.setText("77");
        textFieldInput.setHorizontalAlignment(SwingConstants.RIGHT);
        panel_1.add(textFieldInput);
        textFieldInput.setColumns(20);

        JButton btnExe = new JButton("Exe");
        panel_1.add(btnExe);
        btnExe.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                execute(event);
            }
        });

        lblMs = new JLabel("ready");
        frmKtn.getContentPane().add(lblMs, BorderLayout.SOUTH);
        lblMs.setHorizontalAlignment(SwingConstants.RIGHT);
        lblMs.setAlignmentX(Component.RIGHT_ALIGNMENT);
    }

    /**
     * [Exe]
     * @param event
     */
    private void execute(ActionEvent event) {
        try {
            String res;
            final String input = textFieldInput.getText();
            final int n = Integer.parseInt(input);
            final ExeType type = (ExeType) comboBox.getSelectedItem();
            final long start = System.currentTimeMillis();
            
            switch (type) {
            case FIBONACCI: {
                final BigInteger bi = Big.fib(n);
                res = order(input) +" fibonacci number is\n"+ bi.toString();
            }
                break;
            case FACTORIAL: {
                final BigInteger bi = Big.fact(n);
                res = input +"! =\n"+ bi.toString();
            }
                break;
            case PRIME: {
                final int p = Prime.sieve(n);
                res = order(input) +" prime number is\n"+ (p > 0 ? p : "undefined");
            }
                break;
            default:
                res = "Invalid Type: "+ type;
                break;
            }
            
            final long stop = System.currentTimeMillis();
            textArea.setText(res);
            lblMs.setText((stop - start) + "ms");
        } catch (Exception ex) {
            textArea.setText(ex.toString());
        }
    }
    
    private static String order(String order) {
        if (order == null) { return null; }
        
        final int length = order.length();
        if (length < 1) { return ""; }
        
        String suffix;
        final char first = order.charAt(0);
        if (length == 2 && first == '1') {
            suffix = "th";
        } else {
            final char last = order.charAt(length - 1);
            if (last == '1') {
                suffix = "st";
            } else if (last == '2') {
                suffix = "nd";
            } else if (last == '3') {
                suffix = "rd";
            } else {
                suffix = "th";
            }
        }
        return order + suffix;
    }
}
