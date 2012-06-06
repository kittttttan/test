namespace Wpf {
    using System.Windows;
    using System.Windows.Input;
    using System;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {

        private bool loadSetting = true;

        public MainWindow(string[] args) {
            LoadOption(args);

            InitializeComponent();

            CommandBinding binding = new CommandBinding(ApplicationCommands.Save);
            binding.CanExecute += new CanExecuteRoutedEventHandler(binding_CanExecute);
            binding.Executed += new ExecutedRoutedEventHandler(binding_Executed);
            CommandBindings.Add(binding);
        }

        void binding_CanExecute(object sender, CanExecuteRoutedEventArgs e) {
            e.CanExecute = textBox1.Text.Length > 0;
        }

        void binding_Executed(object sender, ExecutedRoutedEventArgs e) {
            SaveText();
        }

        #region Function
        private void LoadOption(string[] args) {
            foreach (string opt in args) {
                if (opt == "-s") {
                    loadSetting = false;
                }
            }
        }

        private void SaveText() {
            var dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.DefaultExt = "txt";
            dlg.FileName = "text.txt";
            dlg.Filter = "text file|*.txt|All|*.*";
            if (dlg.ShowDialog() == true) {
                using (var writer = new System.IO.StreamWriter(dlg.FileName)) {
                    writer.Write(textBox1.Text);
                }
            }
        }

        private void LoadText() {
            var dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = "txt";
            dlg.FileName = "text.txt";
            dlg.Filter = "text file|*.txt|All|*.*";
            if (dlg.ShowDialog() == true) {
                using (var reader = new System.IO.StreamReader(dlg.FileName)) {
                    string s = reader.ReadToEnd();
                    textBox1.Text = s;
                }
            }
        }

        private void ShowBounds() {
            this.textBlock1.Text = String.Format("({0}, {1}) {2}x{3}", this.Top, this.Left, this.Width, this.Height);
        }
        #endregion Function

        #region Event
        private void Window_Loaded(object sender, RoutedEventArgs e) {
            if (!loadSetting) {
                return;
            }

            if (Properties.Settings.Default.WindowPos.Left > 0) {
                this.Left = Properties.Settings.Default.WindowPos.Left;
            }
            if (Properties.Settings.Default.WindowPos.Top > 0) {
                this.Top = Properties.Settings.Default.WindowPos.Top;
            }
            if (Properties.Settings.Default.WindowPos.Width > 0) {
                this.Width = Properties.Settings.Default.WindowPos.Width;
            }
            if (Properties.Settings.Default.WindowPos.Height > 0) {
                this.Height = Properties.Settings.Default.WindowPos.Height;
            }
            this.WindowState = (WindowState)Properties.Settings.Default.WindowState;
            this.textBox1.Text = Properties.Settings.Default.LastText;

            this.textBlock1.Text = String.Format("({0}, {1}) {2}x{3}", this.Top, this.Left, this.Width, this.Height);

            ShowBounds();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            Properties.Settings.Default.WindowPos = RestoreBounds;
            Properties.Settings.Default.WindowState = (int)WindowState;
            Properties.Settings.Default.LastText = textBox1.Text;

            Properties.Settings.Default.Save();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e) {
            ShowBounds();
        }

        private void Window_LocationChanged(object sender, EventArgs e) {
            ShowBounds();
        }

        private void textBox1_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e) {
            this.label1.Content = this.textBox1.Text.Length;
        }
        #endregion Event

        #region Menu
        private void MenuItem_Save_Click(object sender, RoutedEventArgs e) {
            SaveText();
        }

        private void MenuItem_Exit_Click(object sender, RoutedEventArgs e) {
            this.Close();
        }

        private void MenuItem_Open_Click(object sender, RoutedEventArgs e) {
            LoadText();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e) {
            var cpy = (System.Reflection.AssemblyCopyrightAttribute)
                    Attribute.GetCustomAttribute(
                        System.Reflection.Assembly.GetExecutingAssembly(),
                        typeof(System.Reflection.AssemblyCopyrightAttribute));
            MessageBox.Show(cpy.Copyright, Properties.Resources.About);
        }
        #endregion Menu
    }
}
