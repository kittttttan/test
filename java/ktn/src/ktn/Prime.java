package ktn;

public class Prime {
    /**
     * Get <var>n</var>th prime number
     * 
     * @param n
     * @return prime number
     */
    public static int getPrime(int n) {
        if (n < 1) {
            return 0;
        }
        if (n < 2) {
            return 2;
        }
        
        int[] primes = new int[n];
        primes[0] = 2;
        primes[1] = 3;
        
        int index = 2, i, j, pj;
        boolean addflag;
        for (i = 5; index < n; i += 2) {
            addflag = true;
            for (j = 1; (pj = primes[j]) * pj <= i; ++j) {
                if (i % pj == 0) {
                    addflag = false;
                    break;
                }
            }
            if (addflag) {
                primes[index++] = i;
            }
        }
        return primes[index - 1];
    }

    /**
     * Get <var>n</var>th prime number
     * 
     * @param n
     * @return prime number
     */
    public static int sieve(int n) {
        if (n < 1) {
            return 0;
        }
        
        double times;
        if (n < 50) {
            times = 5;
        } else {
            times = Math.log(n) + 2;
        }
        
        final int limit = (int) Math.floor(n * times);
        final int sq = (int) Math.sqrt(limit);
        boolean[] s = new boolean[limit + 1];
        s[0] = false;
        s[1] = false;
        
        int i, j;
        for (i = 2; i < limit + 1; ++i) {
            s[i] = true;
        }
        for (i = 2; i < sq + 1; ++i) {
            if (s[i]) {
                for (j = i * i; j < limit + 1; j += i) {
                    s[j] = false;
                }
            }
        }
        
        int[] primes = new int[n];
        j = 0;
        for (i = 0; j < n; ++i) {
            if (s[i]) {
                primes[j++] = i;
            }
        }
        return primes[j - 1];
    }
}
