// Eeshan Londhe
// My implementation of the stoi/atoi function in C.
// Enter argument to represent number

#include "stdio.h" // for printf

unsigned int stringToInteger(const char* strNum) {
  const char* ptr = strNum;
  unsigned int num = 0;
  while (*ptr) {
    if (*ptr + '0' > 105 || *ptr + '0' < 96) {
      return -1;
    } else {
      num *= 10;
      num += *ptr +'0' - 96;
      ptr++;
    }
  }
  return num;
}

int main(int argc, char** argv) {
  if (argc > 2) {
    fprintf(stderr, "too many args\n");
    return 1;
  }
  char* number = "123456789\0";
  printf("%d\n", stringToInteger(number));
  if (argc == 2) {
    printf("%d\n", stringToInteger(argv[1]));
  }
  return 0;
}
