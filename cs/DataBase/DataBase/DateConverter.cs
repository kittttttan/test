using System;
using System.Windows;
using System.Windows.Data;
using System.Globalization;
using System.Diagnostics;

namespace DataBase {
    /// <summary>
    /// Convert Datetime to String
    /// </summary>
    [ValueConversion(typeof(DateTime), typeof(String))]
    public class DateConverter : IValueConverter {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            DateTime? ndate = value as DateTime?;
            if (ndate == null) {
                return "";
            }
            DateTime date = (DateTime)ndate;
            return date.ToShortDateString();
        }
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            string strValue = value as string;
            DateTime resultDateTime;
            if (DateTime.TryParse(strValue, out resultDateTime)) {
                return resultDateTime;
            }
            return DependencyProperty.UnsetValue;
        }
    }
}
