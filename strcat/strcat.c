// My implementation of the strcat function in C

#include "stdio.h" // for printf
#include "stdlib.h" // for malloc

// Passes in two char* ptrs
// returns a new char* ptr that contains the concatenation of the 2 strings
char* strCat(char* one, char* two) {
  char* cat = (char*) malloc(sizeof(one) + sizeof(two) - 1);
  char* catPtr = cat;
  char* onePtr = one;
  char* twoPtr = two;
  while (*onePtr) {
    *catPtr++ = *onePtr++;
  }
  while (*twoPtr) {
    *catPtr++ = *twoPtr++;
  }

  return cat;
}

int main() {
  char one[4] = {'O', 'n', 'e', '\0'};
  char two[4] = {'T', 'w', 'o', '\0'};
  char* result = strCat(one,two);
  printf("%s\n", result);
}
