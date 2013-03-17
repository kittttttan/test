/*
 * palindrome.c
 * http://kittttttan.web.fc2.com/c/palindrome
 */
#include <palindrome.h>

/*
 * original    reverse  is_palindrome
 *    12345 != 54321          0
 *     1221 == 1221           1
 * @param[in] n
 * @return 
 */
int is_palindrome(int n) {
  int ds[10], i, j;

  i = j = 0;
  while (n) {
    ds[i++] = n % 10;
    n /= 10;
  }

  while (i > j) {
    if (ds[--i] != ds[j++]) {
      return 0;
    }
  }

  return 1;
}
