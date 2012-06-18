namespace BinaryViewer {
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Text;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Documents;
    using System.Windows.Input;
    using Microsoft.Win32;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        public static RoutedCommand CutCommand = new RoutedCommand();
        public static RoutedCommand CopyCommand = new RoutedCommand();
        public static RoutedCommand PasteCommand = new RoutedCommand();
        public static RoutedCommand DelCommand = new RoutedCommand();

        #region Private State
        private const char commentChar = '#';
        private const string backupFile = "bv_setting.bak";
        private List<Data> clipBoard = new List<Data>();
        #endregion

        #region Initialize
        public MainWindow() {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e) {
            try {
                LoadTSV(backupFile);
            } catch (FileNotFoundException) {
                Debug.WriteLine("Backup File Not Found");
                dataGrid1.ItemsSource = LoadSampleData();
            } catch (Exception ex) {
                dataGrid1.ItemsSource = new List<Data>();
                MessageBox.Show(ex.ToString(), "Exception",
                    MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            SaveTSV(backupFile);
        }

        private List<Data> LoadSampleData() {
            List<Data> data = new List<Data>();

            data.Add(new Data() {
                IsEnabled = true,
                Type = DataType.Int32,
                Length = 1,
                Value = "7"
            });

            data.Add(new Data() {
                IsEnabled = true,
                Type = DataType.Unicode,
                Length = 16,
                Value = "Nana"
            });

            data.Add(new Data() {
                IsEnabled = true,
                Type = DataType.Float,
                Length = 1,
                Value = "7.77"
            });

            return data;
        }
        #endregion

        #region Convert
        public static byte[] DecimalToBytes(Decimal dec) {
            using (MemoryStream ms = new MemoryStream()) {
                using (BinaryWriter bw = new BinaryWriter(ms)) {
                    bw.Write(dec);
                    return ms.ToArray();
                }
            }
        }
        #endregion

        #region Load & Save Binary
        private void LoadBin(string filePath) {
            var newData = new List<Data>();
            using (var br = new BinaryReader(File.Open(filePath, FileMode.Open))) {
                try {
                    foreach (Data data in dataGrid1.ItemsSource) {
                        if (!data.IsEnabled || data.Length <= 0) { continue; }

                        switch (data.Type) {
                        case DataType.Byte: {
                                string s = "";
                                foreach (byte b in br.ReadBytes(data.Length)) {
                                    s += b.ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Int16: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadInt16().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Int32: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadInt32().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Int64: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadInt64().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.UInt16: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadUInt16().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.UInt32: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadInt32().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.UInt64: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadInt64().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Float: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadSingle().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Double: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadDouble().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Decimal: {
                                string s = "";
                                for (int i = 0; i < data.Length; ++i) {
                                    s += br.ReadDecimal().ToString() + " ";
                                }
                                data.Value = s;
                            }
                            break;
                        case DataType.Ascii: {
                                //byte[] asciiBytes = br.ReadBytes(data.Size);
                                //data.Value = Encoding.ASCII.GetString(asciiBytes);
                                data.Value = new string(br.ReadChars(data.Length));
                            }
                            break;
                        case DataType.Unicode: {
                                int byteLength = data.Length * 2;
                                byte[] asciiBytes = br.ReadBytes(byteLength);
                                data.Value = Encoding.Unicode.GetString(asciiBytes);
                            }
                            break;
                        case DataType.String:
                            data.Value = br.ReadString();
                            break;
                        default:
                            break;
                        }

                        newData.Add(data);
                    }
                } catch (EndOfStreamException ex) {
                    MessageBox.Show(ex.ToString(), "EndOfStreamException",
                        MessageBoxButton.OK, MessageBoxImage.Exclamation);
                } catch (Exception ex) {
                    MessageBox.Show(ex.ToString(), "Exception",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

            dataGrid1.ItemsSource = newData;
        }

        private void SaveBin(string filePath) {
            using (Stream st = new FileStream(filePath, FileMode.Create)) {
                try {
                    List<Data> list = new List<Data>((List<Data>)dataGrid1.ItemsSource);
                    foreach (Data data in list) {
                        if (!data.IsEnabled || data.Length <= 0) { continue; }

                        byte[] buf;
                        switch (data.Type) {
                        case DataType.Byte: {
                                buf = new byte[data.Length];
                                string[] ss = data.Value.Split(' ');
                                int length = Math.Min(buf.Length, ss.Length);
                                for (int i = 0; i < length; ++i) {
                                    buf[i] = byte.Parse(ss[i]);
                                }
                            }
                            break;
                        case DataType.Int16: {
                                buf = new byte[data.Length * 2];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(Int16.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Int32: {
                                buf = new byte[data.Length * 4];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(Int32.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Int64: {
                                buf = new byte[data.Length * 8];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(Int64.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.UInt16: {
                                buf = new byte[data.Length * 2];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(UInt16.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.UInt32: {
                                buf = new byte[data.Length * 4];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(UInt32.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.UInt64: {
                                buf = new byte[data.Length * 8];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(UInt64.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Float: {
                                buf = new byte[data.Length * 4];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(float.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Double: {
                                buf = new byte[data.Length * 8];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in BitConverter.GetBytes(double.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Decimal: {
                                buf = new byte[data.Length * 16];
                                string[] ss = data.Value.Split(' ');
                                for (int i = 0, j = 0; i < buf.Length && j < ss.Length; ++j) {
                                    foreach (byte b in DecimalToBytes(Decimal.Parse(ss[j]))) {
                                        buf[i] = b;
                                        ++i;
                                    }
                                }
                            }
                            break;
                        case DataType.Ascii: {
                                // TODO:
                                int byteLength = data.Length * 2;
                                byte[] bytes = Encoding.ASCII.GetBytes((string)data.Value);
                                buf = new byte[byteLength];
                                int length = Math.Min(bytes.Length, byteLength);
                                for (int i = 0; i < length; ++i) {
                                    buf[i] = bytes[i];
                                }
                            }
                            break;
                        case DataType.Unicode:
                        case DataType.String: {
                                int byteLength = data.Length * 2;
                                byte[] bytes = Encoding.Unicode.GetBytes((string)data.Value);
                                buf = new byte[byteLength];
                                int length = Math.Min(bytes.Length, byteLength);
                                for (int i = 0; i < length; ++i) {
                                    buf[i] = bytes[i];
                                }
                            }
                            break;
                        default:
                            buf = new byte[data.Length];
                            break;
                        }
                        st.Write(buf, 0, buf.Length);
                    }
                } catch (Exception ex) {
                    MessageBox.Show(ex.ToString(), "Exception",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }
        #endregion

        #region Load & Save Setting
        private void LoadTSV(string filePath) {
            var dataList = new List<Data>();
            using (var sr = new StreamReader(filePath, Encoding.UTF8)) {
                try {
                    while (sr.Peek() > -1) {
                        string line = sr.ReadLine();
                        if (line.Length < 4 || line[0] == commentChar) {
                            continue;
                        }

                        Data data = new Data();
                        string[] ss = line.Split('\t');

                        data.IsEnabled = ss.Length > 0 && ss[0] == "True";

                        if (ss.Length > 1) {
                            switch (ss[1]) {
                            case "Byte":
                                data.Type = DataType.Byte;
                                break;
                            case "Int16":
                                data.Type = DataType.Int16;
                                break;
                            case "Int32":
                                data.Type = DataType.Int32;
                                break;
                            case "Int64":
                                data.Type = DataType.Int64;
                                break;
                            case "UInt16":
                                data.Type = DataType.UInt16;
                                break;
                            case "UInt32":
                                data.Type = DataType.UInt32;
                                break;
                            case "UInt64":
                                data.Type = DataType.UInt64;
                                break;
                            case "Float":
                                data.Type = DataType.Float;
                                break;
                            case "Double":
                                data.Type = DataType.Double;
                                break;
                            case "Decimal":
                                data.Type = DataType.Decimal;
                                break;
                            case "Ascii":
                                data.Type = DataType.Ascii;
                                break;
                            case "Unicode":
                                data.Type = DataType.Unicode;
                                break;
                            case "String":
                                data.Type = DataType.String;
                                break;
                            default:
                                break;
                            }
                        }

                        if (ss.Length > 2) {
                            data.Length = int.Parse(ss[2]);
                        }

                        if (ss.Length > 3) {
                            data.Value = ss[3];
                        }

                        if (ss.Length > 4) {
                            data.Memo = ss[4];
                        }

                        dataList.Add(data);
                    }
                } catch (Exception ex) {
                    MessageBox.Show(ex.ToString(), "Exception",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

            dataGrid1.ItemsSource = dataList;
        }

        private void SaveTSV(string filePath) {
            using (var sw = new StreamWriter(filePath, false, Encoding.UTF8)) {
                try {
                    foreach (Data data in dataGrid1.ItemsSource) {
                        sw.WriteLine(String.Format(
                            "{0}\t{1}\t{2}\t{3}\t{4}",
                            data.IsEnabled,
                            data.Type,
                            data.Length,
                            data.Value,
                            data.Memo));
                    }
                } catch (Exception ex) {
                    MessageBox.Show(ex.ToString(), "Exception",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }
        #endregion

        #region Drag & Drop
        private void Window_PreviewDragOver(object sender, DragEventArgs e) {
            e.Handled = e.Data.GetDataPresent(DataFormats.FileDrop);
        }

        private void Window_Drop(object sender, DragEventArgs e) {
            string[] files = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (files != null) {
                if (files[0].IndexOf(".tsv") < 0) {
                    LoadBin(files[0]);
                } else {
                    LoadTSV(files[0]);
                }
            }
        }
        #endregion

        #region Menu
        private void MenuItem_Exit_Click(object sender, RoutedEventArgs e) {
            this.Close();
        }

        private void MenuItem_Bin_Open_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.DefaultExt = "dat";
            ofd.Filter = "Data|*.dat|All|*.*";
            if (ofd.ShowDialog() == true) {
                LoadBin(ofd.FileName);
            }
        }

        private void MenuItem_Bin_Save_Click(object sender, RoutedEventArgs e) {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.DefaultExt = "dat";
            sfd.Filter = "Data|*.dat|All|*.*";
            if (sfd.ShowDialog() == true) {
                SaveBin(sfd.FileName);
            }
        }

        private void MenuItem_Setting_Open_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.DefaultExt = "tsv";
            ofd.Filter = "TSV|*.tsv|All|*.*";
            if (ofd.ShowDialog() == true) {
                LoadTSV(ofd.FileName);
            }
        }

        private void MenuItem_Setting_Save_Click(object sender, RoutedEventArgs e) {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.DefaultExt = "tsv";
            sfd.Filter = "TSV|*.tsv|All|*.*";
            if (sfd.ShowDialog() == true) {
                SaveTSV(sfd.FileName);
            }
        }
        #endregion

        #region Context Menu
        private void DeleteData() {
            List<Data> newData = new List<Data>((List<Data>)dataGrid1.ItemsSource);
            int j = 0;
            for (int i = 0; i < dataGrid1.Items.Count; ++i) {
                DataGridRow row = (DataGridRow)dataGrid1.ItemContainerGenerator.ContainerFromIndex(i);
                if (row.IsSelected) {
                    newData.RemoveAt(i - j);
                    ++j;
                }
            }
            dataGrid1.ItemsSource = newData;
        }

        /// <summary>
        /// Deprecated
        /// </summary>
        private void DeleteSelectedData() {
            int index = dataGrid1.SelectedIndex;
            if (index < 0) { return; }
            List<Data> newData = new List<Data>((List<Data>)dataGrid1.ItemsSource);
            if (index >= newData.Count) { return; }
            newData.RemoveAt(index);
            dataGrid1.ItemsSource = newData;
        }

        private void CopyData() {
            clipBoard.Clear();
            foreach (Data data in dataGrid1.SelectedItems) {
                clipBoard.Add(data);
            }
        }

        private void PasteData() {
            List<Data> newData = new List<Data>((List<Data>)dataGrid1.ItemsSource);
            int index = Math.Max(0, dataGrid1.SelectedIndex);
            foreach (Data data in clipBoard) {
                newData.Insert(index, data);
                ++index;
            }
            dataGrid1.ItemsSource = newData;
        }

        private void MenuItem_Add_Click(object sender, RoutedEventArgs e) {
            List<Data> newData = new List<Data>((List<Data>)dataGrid1.ItemsSource);
            newData.Add(new Data() {
                IsEnabled = true,
                Type = DataType.Int32,
                Length = 1,
                Value = "0"
            });
            dataGrid1.ItemsSource = newData;
        }

        private void MenuItem_Insert_Click(object sender, RoutedEventArgs e) {
            List<Data> newData = new List<Data>((List<Data>)dataGrid1.ItemsSource);
            int index = Math.Max(0, dataGrid1.SelectedIndex);
            newData.Insert(index, new Data() {
                IsEnabled = true,
                Type = DataType.Int32,
                Length = 1,
                Value = "0"
            });
            dataGrid1.ItemsSource = newData;
        }

        private void MenuItem_Delete_Click(object sender, RoutedEventArgs e) {
            DeleteData();
        }

        private void MenuItem_DeleteAll_Click(object sender, RoutedEventArgs e) {
            dataGrid1.ItemsSource = new List<Data>();
        }

        private void MenuItem_Copy_Click(object sender, RoutedEventArgs e) {
            CopyData();
        }

        private void MenuItem_Paste_Click(object sender, RoutedEventArgs e) {
            PasteData();
        }

        private void MenuItem_Cut_Click(object sender, RoutedEventArgs e) {
            CopyData();
            DeleteData();
        }
        #endregion

        #region Command
        private void CutExecuted(object sender, ExecutedRoutedEventArgs e) {
            CopyData();
            DeleteData();
        }

        private void CopyExecuted(object sender, ExecutedRoutedEventArgs e) {
            CopyData();
        }

        private void PasteExecuted(object sender, ExecutedRoutedEventArgs e) {
            PasteData();
        }

        private void DelExecuted(object sender, ExecutedRoutedEventArgs e) {
            DeleteData();
        }
        #endregion
    }
}
