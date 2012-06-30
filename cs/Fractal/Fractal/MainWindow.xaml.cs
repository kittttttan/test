// build CSDll.dll and copy to folder includes Fractal.exe

namespace Fractal {
    using System;
    using System.Diagnostics;
    using System.Runtime.InteropServices;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        #region Private
        private const int limit = 0xff;
        private const double scale = 200.0;
        private const int width = (int)(3 * scale);
        private const int height = (int)(2 * scale);

        private WriteableBitmap wb;
        private int[] data = new int[width * height];
        #endregion

        public MainWindow() {
            InitializeComponent();
        }

        #region C#
        private int Lim(double x, double y) {
            int c = 0;
            double px = 0, py = 0, nx, ny;
            for (int i = 0; i < limit; ++i) {
                nx = px * px - py * py + x;
                ny = 2 * px * py + y;
                if (nx * nx + ny * ny > 4.0) {
                    c = i + 1;
                    break;
                } else {
                    px = nx;
                    py = ny;
                }
            }
            if (c == 0) { c = limit; }
            return c;
        }

        private void CalcMandel() {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    data[y * width + x] = Lim(x / scale - 2, y / scale - 1);
                }
            }
        }

        private void DrawMandel() {
            //int channel = 4;
            int width = wb.PixelWidth;
            int height = wb.PixelHeight;
            //int stride = wb.BackBufferStride;
            //int res = stride - channel * width;
            wb.Lock();

            unsafe {
                byte* pBackBuffer = (byte*)wb.BackBuffer;
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int t = data[y * width + x];
                        if (t < limit) {
                            t <<= 4;
                            if (t > 0xff) {
                                t = 0xff;
                            }
                        } else {
                            t = 0;
                        }
                        *pBackBuffer = (byte)t; ++pBackBuffer;
                        *pBackBuffer = 0; ++pBackBuffer;
                        *pBackBuffer = 0; ++pBackBuffer;
                        ++pBackBuffer;
                    }
                    //pBackBuffer += res;
                }
            }
            wb.AddDirtyRect(new Int32Rect(0, 0, width, height));
            wb.Unlock();

            this.image1.Source = wb;
        }
        #endregion

        #region Dll
        [DllImport("CSDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void CCalcMandel(IntPtr buf, int width, int height, int limit, double scale);

        private void DrawMandelC() {
            int channel = 4;
            int width = wb.PixelWidth;
            int height = wb.PixelHeight;
            int stride = wb.BackBufferStride;
            int res = stride - channel * width;
            wb.Lock();

            CCalcMandel(wb.BackBuffer, width, height, limit, scale);

            wb.AddDirtyRect(new Int32Rect(0, 0, width, height));
            wb.Unlock();

            this.image1.Source = wb;
        }
        #endregion

        #region Event
        private void Window_Loaded(object sender, RoutedEventArgs e) {
            wb = new WriteableBitmap(width, height, 96, 96, PixelFormats.Bgr32, null);
        }

        private void button_CS_Click(object sender, RoutedEventArgs e) {
            Stopwatch sw = new Stopwatch();
            sw.Start();

            CalcMandel();
            DrawMandel();

            sw.Stop();
            this.textBlock1.Text = sw.Elapsed.TotalMilliseconds + " ms";
        }

        private void button_C_Click(object sender, RoutedEventArgs e) {
            Stopwatch sw = new Stopwatch();
            sw.Start();

            DrawMandelC();

            sw.Stop();
            this.textBlock1.Text = sw.Elapsed.TotalMilliseconds + " ms";
        }

        private void button_Clear_Click(object sender, RoutedEventArgs e) {
            this.image1.Source = null;
        }
        #endregion
    }
}
