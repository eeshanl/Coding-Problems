// Eeshan Londhe
// Replace spaces in a string with "%20"
// Assumes string pased in is fewer thatn 100 chars

#include "stdio.h" // for printf

void replaceSpace(char* str) {
  int spaceCount = 0;
  int length = 0;
  char* strPtr = str;
  while (*strPtr) {
    if (*strPtr == ' ') {
      spaceCount++;
    }
    length++;
    strPtr++;
  }
  int newLength = length + spaceCount * 2;
  str[newLength] = '\0';
  for (int i = length - 1; i >= 0; i--) {
    if (str[i] == ' ') {
      str[newLength - 1] = '0';
      str[newLength - 2] = '2';
      str[newLength - 3] = '%';
      newLength = newLength - 3;
    } else {
      str[newLength - 1] = str[i];
      newLength = newLength - 1;
    }
  }
}

int main() {
  // Give enough memory for 100 chars. Need to give extra memory because we don't
  // know how many spaces there will be in the word.
  char str[100] = {'R', 'e', 'p', 'l', 'a', 'c', 'e', ' ', 't', 'h', 'i', 's', '\0'};
  printf("Original String: %s\n", str);
  replaceSpace(str);
  printf("Modified String: %s\n", str);
  return 0;
}
