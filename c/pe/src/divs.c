/*
 * divs.c
 * http://kittttttan.web.fc2.com/c/divs
 */
#include <divs.h>

#include <math.h>

enum { MAX_DIVS_CNT = 256 };

/*
 * get divisors
 * @param[out] p divisors
 * @param[in]  n max length
 * @return length
 */
size_t get_divs(unsigned long *p, unsigned long n) {
  size_t i, len, limit;

  len = 0;
  limit = (size_t)sqrt(n);
  while ((n & 1) == 0) {
    p[len++] = 2;
    n >>= 1;
  }
  if (n == 1) {
    return len;
  }

  i = 3;
  while (i <= limit) {
    if (n % i == 0) {
      p[len++] = i;
      n /= i;
      if (n < i) {
        break;
      }
    } else {
      i += 2;
    }
  }
  if (n > 1) {
    p[len++] = n;
  }

  return len;
}

/*
 * count divisors
 * @param[in] n
 * @return 
 */
unsigned long cnt_divs(unsigned long n) {
  unsigned long p[MAX_DIVS_CNT];
  size_t i, l;
  unsigned long t, c;

  if (!n) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  if (n < 4) {
    return 2;
  }

  t = 0;
  c = 1;
  l = get_divs(p, n);
  for (i = 0; i < l; ++i) {
    if (i + 1 < l && p[i] == p[i + 1]) {
      ++t;
    } else {
      c *= t + 2;
      t = 0;
    }
  }

  return c;
}
