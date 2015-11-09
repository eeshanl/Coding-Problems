// Simple program to check if a string is a substring of another

#include <stdio.h>

// returns length of string
int stringLength(char * string) {
  char* str = string;
  int len = 0;
  while (*str != '\0') {
    len++;
    str++;
  }
  return len;
}

// Returns 1 if str2 is a substring of str1, 0 otherwise
// ex: isSubstring(helloworld, world) returns 1
int isSubstring(char* string1, char* string2) {
  int j = 0;
  for (int i = 0; i < stringLength(string1); i++) {
    if (string1[i] == string2[j]) {
      j++;
    }
  }
  return j == stringLength(string2);
}

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Please input 2 strings as arguments\n");
    return 1;
  }
  //char * str = "helloworld\0";
  //char * str2 = "world\0";
  printf("%d\n", isSubstring(argv[1], argv[2]));
  return 1;
}
