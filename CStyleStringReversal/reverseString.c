/* Eeshan Londhe
 * Program to reverse a C-Style string in place.
 */

#include <stdio.h>

void reverseString(char* str) {
  char* front = str;
  char* back = front;
  while (*back != '\0') {
    back++;
  }
  back--;
  while (front < back) {
    char backTemp = *front;
    *front++ = *back;
    *back-- = backTemp;
  }
}

int main(int argc, char** argv) {
  char str[5] = "blah";
  printf("Original string: %s\n", str);
  reverseString(str);
  printf("Reversed string: %s\n", str);
  return 0;
}
