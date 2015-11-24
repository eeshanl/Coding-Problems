#include <stdlib.h>
#include <stdio.h>

void toLower(char* str);
void strClean(char* str);

int main(int argc, char** argv) {
  char str[5] = {'T', 'E', 'S', 'T', '\0'};
  char str2[5] = {'T', '}', '{', 'T', '\0'};
  printf("Original string: %s\n", str);
  toLower(str);
  printf("toLowered string: %s\n\n", str);
  printf("Original string: %s\n", str2);
  strClean(str2);
  printf("Cleaned string: %s\n", str2);
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

void strClean(char* str) {
  char* ptr = str;
  while (*ptr != '\0') {
    if ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) {
      ptr++;
    } else {
      char* ptr2 = ptr;
      while (*(ptr2+1) != '\0') {
        *ptr2 = *(ptr2 + 1);
        ptr2++;
      }
      *ptr2 = '\0';
    }

  }
}
