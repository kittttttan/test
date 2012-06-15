namespace Struct {
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential, Pack = 4, CharSet = CharSet.Unicode)]
    public unsafe struct CStruct {
        public int i;
        public fixed char c16[16];
        public float f;
    }
}
