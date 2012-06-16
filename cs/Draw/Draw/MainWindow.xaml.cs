namespace Draw {
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Windows;
    using System.Windows.Input;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using Microsoft.Win32;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        #region Private State
        private enum DrawType {
            Line = 0,
            Box,
            Circle,
        }
        private DrawType drawType = DrawType.Line;

        private const int imageWidth = 320;
        private const int imageHeight = 240;
        private int penThick = 6;
        private bool fill = false;

        private RenderTargetBitmap bitmap;
        private RenderTargetBitmap previewBitmap;
        private Stack<RenderTargetBitmap> bitmapHistory = new Stack<RenderTargetBitmap>();
        private DrawingVisual drawVisual = new DrawingVisual();
        private DrawingContext drawContext;
        private Brush brush = Brushes.Black;
        private Brush fillBrush;
        private Point ptLast;
        private Random rand = new Random();
        #endregion

        #region Initialize
        public MainWindow() {
            InitializeComponent();

            bitmap = new RenderTargetBitmap(imageWidth, imageHeight,
                96, 96, PixelFormats.Default);
            previewBitmap = new RenderTargetBitmap(imageWidth, imageHeight,
                96, 96, PixelFormats.Default);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e) {
            this.image1.Source = bitmap;
            this.tmpLayer.Source = previewBitmap;
            this.textBlock1.Text = drawType.ToString();
        }
        #endregion

        #region Calculate
        /// <summary>
        /// Convert mouse point to image position
        /// </summary>
        /// <param name="pt"></param>
        /// <returns></returns>
        private Point ConvertPoint(Point pt) {
            return new Point(imageWidth * pt.X / image1.ActualWidth, imageHeight * pt.Y / image1.ActualHeight);
        }

        /// <summary>
        /// Calculate distance
        /// </summary>
        /// <param name="pt1"></param>
        /// <param name="pt2"></param>
        /// <returns></returns>
        private double CalcDist(Point pt1, Point pt2) {
            return Math.Sqrt((pt1.X - pt2.X) * (pt1.X - pt2.X) + (pt1.Y - pt2.Y) * (pt1.Y - pt2.Y));
        }
        #endregion

        #region Drawing
        /// <summary>
        /// Start drawing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            Point pt = e.GetPosition(image1);
            Point rpt = ConvertPoint(pt);
            brush = new SolidColorBrush(Color.FromRgb(
                (byte)rand.Next(256), (byte)rand.Next(256), (byte)rand.Next(256)));
            if (fill) {
                fillBrush = new SolidColorBrush(Color.FromRgb(
                    (byte)rand.Next(256), (byte)rand.Next(256), (byte)rand.Next(256)));
            } else {
                fillBrush = null;
            }
            ptLast = rpt;
        }

        /// <summary>
        /// Preview drawing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void image_MouseMove(object sender, MouseEventArgs e) {
            if (e.LeftButton == MouseButtonState.Pressed) {
                Point pt = e.GetPosition(image1);
                Point rpt = ConvertPoint(pt);
                previewBitmap.Clear();
                drawContext = drawVisual.RenderOpen();
                Pen penDraw = new Pen(brush, penThick);
                switch (drawType) {
                case DrawType.Line:
                    drawContext.DrawLine(penDraw, ptLast, rpt);
                    break;
                case DrawType.Box:
                    drawContext.DrawRectangle(fillBrush, penDraw, new Rect(ptLast, rpt));
                    break;
                case DrawType.Circle: {
                        double r = CalcDist(ptLast, rpt);
                        drawContext.DrawEllipse(fillBrush, penDraw, ptLast, r, r);
                    }
                    break;
                default:
                    break;
                }
                drawContext.Close();
                previewBitmap.Render(drawVisual);
            }
        }

        /// <summary>
        /// Fix drawing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void image_MouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            bitmapHistory.Push((RenderTargetBitmap)bitmap.Clone());
            Point pt = e.GetPosition(image1);
            Point rpt = ConvertPoint(pt);
            drawContext = drawVisual.RenderOpen();
            Pen penDraw = new Pen(brush, penThick);
            switch (drawType) {
            case DrawType.Line:
                drawContext.DrawLine(penDraw, ptLast, rpt);
                break;
            case DrawType.Box:
                drawContext.DrawRectangle(fillBrush, penDraw, new Rect(ptLast, rpt));
                break;
            case DrawType.Circle: {
                    double r = CalcDist(ptLast, rpt);
                    drawContext.DrawEllipse(fillBrush, penDraw, ptLast, r, r);
                }
                break;
            default:
                break;
            }
            drawContext.Close();
            bitmap.Render(drawVisual);
            previewBitmap.Clear();
        }
        #endregion

        #region Menu Edit
        /// <summary>
        /// Clear image
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_Clear_Click(object sender, RoutedEventArgs e) {
            bitmapHistory.Push((RenderTargetBitmap)bitmap.Clone());
            bitmap.Clear();
        }

        /// <summary>
        /// Unlimited redo
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_Redo_Click(object sender, RoutedEventArgs e) {
            int count = bitmapHistory.Count;
            if (count > 0) {
                bitmap.Clear();
                drawContext = drawVisual.RenderOpen();
                drawContext.DrawImage(bitmapHistory.Pop(),
                    new Rect(0, 0, imageWidth, imageHeight));
                drawContext.Close();
                bitmap.Render(drawVisual);
            }
        }
        #endregion

        #region Menu File
        private void MenuItem_Exit_Click(object sender, RoutedEventArgs e) {
            this.Close();
        }

        /// <summary>
        /// Save as PNG
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_Save_Click(object sender, RoutedEventArgs e) {
            PngBitmapEncoder encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmap));
            var dlg = new SaveFileDialog();
            dlg.Filter = "PNG(*.png)|*.png";
            if (dlg.ShowDialog() == true) {
                using (FileStream stream = new FileStream(dlg.FileName,
                        FileMode.Create, FileAccess.Write)) {
                    try {
                        encoder.Save(stream);
                    } catch (Exception ex) {
                        MessageBox.Show(ex.ToString(), "Exception",
                            MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
        }

        private void MenuItem_Open_Click(object sender, RoutedEventArgs e) {
            var dlg = new OpenFileDialog();
            dlg.Filter = "PNG(*.png)|*.png";
            if (dlg.ShowDialog() == true) {
                using (FileStream stream = new FileStream(dlg.FileName,
                        FileMode.Open, FileAccess.Read)) {
                    try {
                        BitmapImage src = new BitmapImage();
                        src.BeginInit();
                        src.StreamSource = stream;
                        src.CacheOption = BitmapCacheOption.OnLoad;
                        src.EndInit();
                        //image1.Source = src;

                        bitmapHistory.Push((RenderTargetBitmap)bitmap.Clone());
                        bitmap.Clear();
                        drawContext = drawVisual.RenderOpen();
                        drawContext.DrawImage(src,
                            new Rect(0, 0, imageWidth, imageHeight));
                        drawContext.Close();
                        bitmap.Render(drawVisual);

                    } catch (Exception ex) {
                        MessageBox.Show(ex.ToString(), "Exception",
                            MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
        }
        #endregion

        #region Menu Type
        private void MenuItem_Line_Click(object sender, RoutedEventArgs e) {
            drawType = DrawType.Line;
            this.textBlock1.Text = drawType.ToString();
        }

        private void MenuItem_Box_Click(object sender, RoutedEventArgs e) {
            drawType = DrawType.Box;
            this.textBlock1.Text = drawType.ToString();
        }

        private void MenuItem_Circle_Click(object sender, RoutedEventArgs e) {
            drawType = DrawType.Circle;
            this.textBlock1.Text = drawType.ToString();
        }

        private void MenuItem_Fill_Click(object sender, RoutedEventArgs e) {
            fill = !fill;
        }
        #endregion
    }
}
