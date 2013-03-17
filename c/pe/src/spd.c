/*
 * spd.c
 * http://kittttttan.web.fc2.com/c/spd
 */
#include <spd.h>

#include <math.h>

/*
 * Sum of proper divisors
 * @param[in] n
 * @return
 */
int spd(int n) {
  int sum = 1;
  int i;
  int isq;
  
  if (n < 2) return sum;
  
  isq = (int)floor(sqrt(n));
  
  for (i = 2; i < isq; ++i) {
    if (n % i == 0) {
      sum += i + n / i;
    }
  }
  
  if (n == isq * isq) {
    sum += isq;
  }

  return sum;
}
