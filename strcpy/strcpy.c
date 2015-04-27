// Eeshan Londhe
// My implementation of the string copy functions in C

#include "stdio.h" // for printf
#include "stdlib.h" // for malloc

// Version similar to default stcpy function
void strCopy(char* copy, const char* org) {
  const char* orgPtr = org;
  char* copyPtr = copy;
  while (*orgPtr) {
    *copyPtr++ = *orgPtr++;
  }
}

// The way I would implement it. By allocating memory same size as string passed in.
char* strCopy2(const char* str) {
  char* copy = (char*) malloc(sizeof(str));
  char* copyPtr = copy;
  const char* strPtr = str;
  while (*strPtr) {
    *copyPtr++ = *strPtr++;
  }
  *copyPtr = *strPtr;
  return copy;
}

int main() {
  char str[20];
  char* word = "hello\0";
  strCopy(str, word);
  char* str2 = strCopy2(word);
  printf("%s\n", str);
  printf("%s\n", str2);
}
