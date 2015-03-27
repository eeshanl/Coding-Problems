/* Eeshan Londhe
 * Program to reverse a C-Style string.
 */

#include <stdio.h>
#include <string.h>

void reverseString(char* str);

int main(int argc, char** argv) {
  char str[5] = "blah";
  printf("Original string: %s\n", str);
  reverseString(str);
  printf("Reversed string: %s\n", str);
  return 0;
}

void reverseString(char* str) {
  char* front = &str[0];
  char* back = &str[strlen(str) - 1];
  for (int i = 0; i < strlen(str) / 2; i++) {
    char backTemp = *front;
    *front = *back;
    *back = backTemp;
    front++;
    back--;
  }
}
