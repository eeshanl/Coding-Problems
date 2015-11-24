#include <stdlib.h>
#include <stdio.h>

void toLower(char* str);

int main(int argc, char** argv) {
  char str[5] = {'T', 'E', 'S', 'T', '\0'};
  toLower(str);
  printf("%s\n", str);
  return 0;
}

void toLower(char* str) {
  char* ptr = str;
  while(*ptr != '\0') {
    if (*ptr >= 'A' && *ptr <= 'Z') {
      *ptr = *ptr + ('a' - 'A');
    }
    ptr++;
  }
}
