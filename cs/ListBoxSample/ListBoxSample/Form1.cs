using System;
using System.Windows.Forms;

namespace ListBoxSample {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void helpHToolStripMenuItem_Click(object sender, EventArgs e) {
            showHelp();
        }

        private void exitXToolStripMenuItem_Click(object sender, EventArgs e) {
            this.Close();
        }

        private void Form1_Load(object sender, EventArgs e) {
            init();
        }

        private void Form1_DragEnter(object sender, DragEventArgs e) {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
                e.Effect = DragDropEffects.Copy;
            } else {
                e.Effect = DragDropEffects.None;
            }
        }

        private void Form1_DragDrop(object sender, DragEventArgs e) {
            string[] fileNames = (string[])e.Data.GetData(DataFormats.FileDrop, false);
            loadFileNames(fileNames);
        }

        private void removeRToolStripMenuItem_Click(object sender, EventArgs e) {
            removeSelectedItems();
        }

        private void selectAllAToolStripMenuItem_Click(object sender, EventArgs e) {
            selectAllItems();
        }

        private void listBox1_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyData == Keys.Delete) {
                removeSelectedItems();
            }
            if ((e.Modifiers & Keys.Control) == Keys.Control && (e.KeyData & Keys.A) == Keys.A) {
                selectAllItems();
            }
        }

        private void listBox1_SelectedValueChanged(object sender, EventArgs e) {
            updateStatus();
        }

        private void openOToolStripMenuItem_Click(object sender, EventArgs e) {
            open();
        }

        private void folderFToolStripMenuItem_Click(object sender, EventArgs e) {
            loadFolder();
        }

        private void saveSToolStripMenuItem_Click(object sender, EventArgs e) {
            save();
        }

        private void importIToolStripMenuItem_Click(object sender, EventArgs e) {
            import();
        }
    }
}
