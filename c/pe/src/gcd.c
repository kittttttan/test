/*
 * gcd.c - Greatest Common Divisor, Least Common Multiple
 * http://kittttttan.web.fc2.com/c/gcd
 */
#include <gcd.h>

#include <assert.h>

/*
 * Greatest Common Divisor
 * @param[in] a
 * @param[in] b
 * @return 
 */
unsigned long gcd(unsigned long a, unsigned long b) {
  unsigned long c;

  assert(b != 0);
  for (;;) {
    c = a % b;
    if (!c) { break; }
    a = b;
    b = c;
  }

  return b;
}

/*
 * Least Common Multiple
 * @param[in] a
 * @param[in] b
 * @return 
 */
unsigned long lcm(unsigned long a, unsigned long b) {
  unsigned long c;

  c = gcd(a, b);
  
  assert(c != 0);
  return a * b / c;
}
