package ktn.beta.gui.main;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JTree;
import java.awt.Component;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;
import javax.swing.JSplitPane;
import javax.swing.JScrollPane;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import ktn.gui.life.Life;
import ktn.gui.sample1.Win;

public class Frame extends JFrame {
    private static final long serialVersionUID = 1L;

    private JPanel contentPane;
    private JTree tree;
    private JPanel panel_1;
    private JButton btnStart;
    private JPanel panel;
    private JSplitPane splitPane;
    private JScrollPane scrollPane;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    Frame frame = new Frame();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the frame.
     */
    public Frame() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 240, 240);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(new BorderLayout(0, 0));

        panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        panel_1 = new JPanel();
        panel.add(panel_1);

        btnStart = new JButton("Start");
        btnStart.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                TreePath treePath = getTree().getSelectionPath();
                if (treePath == null) { return; }
                
                Object[] obj = treePath.getPath();
                
                final int length = obj.length;
                if (length < 3) { return; }
                
                if (obj[1].toString().equals("Gui")) {
                    if (obj[2].toString().equals("Win")) {
                        Win.main(null);
                    } else if (obj[2].toString().equals("Life")) {
                        Life.main(null);
                    }
                }
            }
        });
        btnStart.setAlignmentX(Component.CENTER_ALIGNMENT);
        panel.add(btnStart);

        tree = new JTree();
        tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
        tree.addTreeSelectionListener(new TreeSelectionListener() {
            public void valueChanged(TreeSelectionEvent e) {
                TreePath treePath = e.getPath();
                if (treePath != null) {
                    System.out.println(treePath.toString());
                }
            }
        });
        tree.setModel(new DefaultTreeModel(new DefaultMutableTreeNode("Apps") {

            private static final long serialVersionUID = 1L;

            {
                DefaultMutableTreeNode node_1;
                node_1 = new DefaultMutableTreeNode("Gui");
                node_1.add(new DefaultMutableTreeNode("Win"));
                node_1.add(new DefaultMutableTreeNode("Life"));
                add(node_1);
            }
        }));
        tree.setShowsRootHandles(true);

        scrollPane = new JScrollPane();
        scrollPane.setViewportView(tree);

        splitPane = new JSplitPane();
        splitPane.setDividerSize(3);
        splitPane.setLeftComponent(scrollPane);
        splitPane.setRightComponent(panel);
        contentPane.add(splitPane, BorderLayout.CENTER);
    }

    public JTree getTree() {
        return tree;
    }

}
