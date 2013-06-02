#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {
  cout <<
    "char: " << sizeof(char) <<
    "\nshort: " << sizeof(short) <<
    "\nint: " << sizeof(int) <<
    "\nlong: " << sizeof(long) <<
    "\nlong long: " << sizeof(long long) <<
    "\npointer: " << sizeof(void*) <<
    "\nbool: " << sizeof(bool) << endl;

#ifdef _MSC_VER
    system("pause");
#endif
  
	return 0;
}

