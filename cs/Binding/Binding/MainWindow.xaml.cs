namespace Binding {
    using System;
    using System.ComponentModel;
    using System.Windows;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
        }

        private void ContentPanel_Loaded(object sender, RoutedEventArgs e) {
            ContentPanel.DataContext = new MyTime();
        }

        private void button1_Click(object sender, RoutedEventArgs e) {
            ((MyTime)ContentPanel.DataContext).Now = DateTime.Now.ToLongTimeString();
            ((MyTime)ContentPanel.DataContext).Count += 1;
            ((MyTime)ContentPanel.DataContext).Check ^= true;
            Checked ^= true;
        }

        #region Dependency Property
        public static readonly DependencyProperty MyProperty =
            DependencyProperty.Register("Checked", typeof(bool), typeof(MainWindow),
                new FrameworkPropertyMetadata(false));

        public bool Checked {
            get { return (bool)GetValue(MyProperty); }
            set { SetValue(MyProperty, value); }
        }
        #endregion
    }

    public class MyTime : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;

        public void NotifyPropertyChanged(string propertyName) {
            if (PropertyChanged != null) {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        private String now;
        public String Now {
            get { return now; }
            set { now = value; NotifyPropertyChanged("Now"); }
        }

        private double count;
        public double Count {
            get { return count; }
            set { count = value; NotifyPropertyChanged("Count"); }
        }

        private bool check;
        public bool Check {
            get { return check; }
            set { check = value; NotifyPropertyChanged("Check"); }
        }
    }
}
