namespace Struct {
    using System;
    using System.IO;
    using System.Runtime.InteropServices;
    using System.Windows;
    using Microsoft.Win32;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
        }

        #region Drag & Drop
        private void Window_PreviewDragOver(object sender, DragEventArgs e) {
            e.Handled = e.Data.GetDataPresent(DataFormats.FileDrop);
        }

        private void Window_Drop(object sender, DragEventArgs e) {
            string[] files = e.Data.GetData(DataFormats.FileDrop) as string[];
            if (files != null) {
                Load(files[0]);
            }
        }
        #endregion

        private void Load(string filePath) {
            var cst = Read<CStruct>(filePath);
            string res;
            unsafe {
                res = new string(cst.c16);
            }
            this.textBox1.Text = cst.i.ToString();
            this.textBox2.Text = res;
            this.textBox3.Text = cst.f.ToString();
        }

        private void Save(string filePath) {
            try {
                var s = new CStruct();
                s.i = int.Parse(this.textBox1.Text);
                s.f = float.Parse(this.textBox3.Text);
                var str = this.textBox2.Text;
                int length = Math.Min(16, str.Length);
                unsafe {
                    for (int i = 0; i < length; ++i) {
                        s.c16[i] = str[i];
                    }
                }
                byte[] buf = StructToByte(s);
                using (Stream st = new FileStream(filePath, FileMode.Create)) {
                    st.Write(buf, 0, buf.Length);
                }
            } catch (Exception ex) {
                MessageBox.Show(ex.ToString(), "Exception", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public static T Read<T>(string FileName) {
            byte[] buf;
            using (Stream s = new FileStream(FileName, FileMode.Open)) {
                buf = new byte[Marshal.SizeOf(typeof(T))];
                s.Read(buf, 0, buf.Length);
            }

            return ByteToStruct<T>(buf);
        }

        #region Convert
        public static byte[] StructToByte<T>(T strct) {
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(T)));

            try {
                Marshal.StructureToPtr(strct, ptr, false);
                byte[] bin = new byte[Marshal.SizeOf(typeof(T))];
                Marshal.Copy(ptr, bin, 0, Marshal.SizeOf(typeof(T)));
                return bin;
            } finally {
                if (IntPtr.Zero != ptr) { Marshal.FreeHGlobal(ptr); }
            }
        }

        public static T ByteToStruct<T>(byte[] bin) {
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(T)));

            try {
                Marshal.Copy(bin, 0, ptr, Marshal.SizeOf(typeof(T)));
                return (T)Marshal.PtrToStructure(ptr, typeof(T)); ;
            } finally {
                if (IntPtr.Zero != ptr) { Marshal.FreeHGlobal(ptr); }
            }
        }
        #endregion

        #region Dialog
        private void button_Load_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.FileName = "test";
            ofd.DefaultExt = "dat";
            ofd.Filter = "Data|*.dat|All|*.*";
            if (ofd.ShowDialog() == true) {
                Load(ofd.FileName);
            }
        }

        private void button_Save_Click(object sender, RoutedEventArgs e) {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.FileName = "test";
            sfd.DefaultExt = "dat";
            sfd.Filter = "Data|*.dat|All|*.*";
            if (sfd.ShowDialog() == true) {
                Save(sfd.FileName);
            }
        }
        #endregion
    }
}
