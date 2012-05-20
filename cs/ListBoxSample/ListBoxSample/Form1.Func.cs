using System;
using System.IO;
using System.Windows.Forms;

namespace ListBoxSample {
    partial class Form1 {
        private void init() {
            string[] cmds = System.Environment.GetCommandLineArgs();
            foreach (string cmd in cmds) {
                Console.WriteLine(cmd);
            }

            toolStripStatusLabel1.Text = "Ready";
        }

        private void showHelp() {
            MessageBox.Show("(c)2012 kittttttan", "ListBoxSample", MessageBoxButtons.OK);
        }

        private void updateStatus() {
            toolStripStatusLabel1.Text = listBox1.Items.Count + " Items / " +
                listBox1.SelectedItems.Count + " Selected";
        }

        private void removeSelectedItems() {
            try {
                while (listBox1.SelectedIndex >= 0) {
                    listBox1.Items.RemoveAt(listBox1.SelectedIndex);
                }
            } catch (Exception ex) {
                toolStripStatusLabel1.Text = ex.Message;
            }

            updateStatus();
        }

        private void selectAllItems() {
            for (int i = 0; i < listBox1.Items.Count; ++i) {
                listBox1.SetSelected(i, true);
            }
        }

        private void loadFileNames(string[] fileNames) {
            try {
                foreach (string f in fileNames) {
                    FileAttributes attr = File.GetAttributes(f);
                    if ((attr & FileAttributes.Directory) == FileAttributes.Directory) {
                        string[] files = System.IO.Directory.GetFiles(f, "*", System.IO.SearchOption.AllDirectories);
                        listBox1.Items.AddRange(files);
                    } else {
                        listBox1.Items.Add(f);
                    }
                }
            } catch (Exception ex) {
                toolStripStatusLabel1.Text = ex.Message;
            }

            updateStatus();
        }
        private void open() {
            if (openFileDialog1.ShowDialog() == DialogResult.OK) {
                listBox1.Items.AddRange(openFileDialog1.FileNames);
                updateStatus();
            }
        }
        private void loadFolder() {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK) {
                try {
                    string[] files = System.IO.Directory.GetFiles(folderBrowserDialog1.SelectedPath, "*", System.IO.SearchOption.AllDirectories);
                    listBox1.Items.AddRange(files);
                } catch (Exception ex) {
                    toolStripStatusLabel1.Text = ex.Message;
                }
            }
        }
        private void import() {
            if (openFileDialog2.ShowDialog() == DialogResult.OK) {
                using (StreamReader r = new StreamReader(openFileDialog2.FileName)) {
                    string line;
                    while ((line = r.ReadLine()) != null) {
                        if (System.IO.File.Exists(line)) {
                            listBox1.Items.Add(line);
                        }
                    }
                }

                updateStatus();
            }
        }
        private void save() {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK) {
                System.IO.Stream stream;
                stream = saveFileDialog1.OpenFile();
                if (stream != null) {
                    System.IO.StreamWriter sw = new System.IO.StreamWriter(stream);
                    foreach (string item in listBox1.Items) {
                        sw.WriteLine(item);
                    }
                    sw.Close();
                    stream.Close();
                }
            }
        }
   }
}
