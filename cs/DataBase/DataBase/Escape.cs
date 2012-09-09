namespace DataBase {
    /// <summary>
    /// Escape
    /// </summary>
    static class Escape {
        public static string HTML(string src) {
            return src.Replace("&", "&amp;").Replace("<", "&lt;").Replace(">", "&gt;");
        }

        public static string CSV(string src) {
            if (src.IndexOf(',') < 0) {
                return src;
            }

            return "\"" + src.Replace("\"", "\"\"") + "\"";
        }
    }
}
