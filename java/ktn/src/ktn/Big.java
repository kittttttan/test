package ktn;

import java.math.BigInteger;

public class Big {
    /**
     * <pre>
     *  |a b|   |d e|   |ad+be bd+ce|
     *  |   | x |   | = |           |
     *  |b c|   |e f|   |bd+ce be+cf|
     * </pre>
     * 
     * @param a
     * @param b
     * @return
     */
    private static BigInteger[] utm2mul(BigInteger[] a, BigInteger[] b) {
        final BigInteger ad = a[0].multiply(b[0]);
        final BigInteger be = a[1].multiply(b[1]);
        final BigInteger bd = a[1].multiply(b[0]);
        final BigInteger ce = a[2].multiply(b[1]);
        final BigInteger bdce = bd.add(ce);
        final BigInteger cf = a[2].multiply(b[2]);
        final BigInteger[] m = { ad.add(be), bdce, be.add(cf) };
        return m;
    }

    /**
     * fibonacci
     * 
     * <pre>
     *    |1 1|^n   |fib(n+1) fib(n)  |
     *    |   |   = |                 |
     *    |1 0|     |fib(n)   fib(n-1)|
     * </pre>
     * 
     * @param n
     * @return <var>n</var>th fibonacci
     */
    public static BigInteger fib(int n) {
        if (n-- > 0) {
            if (n-- == 1) {
                return BigInteger.ONE;
            }
            BigInteger[] m0 = { BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO };
            BigInteger[] m = { BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO };
            for (; n > 0; n >>>= 1, m0 = utm2mul(m0, m0)) {
                if ((n & 1) == 1) {
                    m = utm2mul(m, m0);
                }
            }
            return m[0];
        }
        return BigInteger.ZERO;
    }
    
    public static BigInteger fact(int n) {
        BigInteger b = BigInteger.ONE;
 
        for (int i = 2; i < n + 1; ++i) {
            b = b.multiply(BigInteger.valueOf(i));
        }
 
        return b;
    }
}
