namespace BinaryViewer {

    public enum DataType {
        Byte = 0,

        Int16,
        Int32,
        Int64,

        UInt16,
        UInt32,
        UInt64,

        Float,
        Double,
        Decimal,

        Ascii,
        Unicode,
        String,
    }

    public class Data {
        public bool IsEnabled { get; set; }
        public DataType Type { get; set; }
        public int Length { get; set; }
        public string Value { get; set; }
        public string Memo { get; set; }
    }
}
