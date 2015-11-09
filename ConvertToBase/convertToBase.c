// Converts a decimal number to its representation in any base up to 16

#include <stdio.h>
#include <stdlib.h>

char* convertToBase(int num, int base);
int digits(unsigned int num, int base);

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "Enter a number and a base as arguments.\n");
    exit(1);
  }
  printf("%s\n", convertToBase(atoi(argv[1]), atoi(argv[2])));
  return 1;
}

// Converts any integer to its representation in the base passed in
char* convertToBase(int num, int base) {
  const char num_key[16] = "0123456789abcdef";
  unsigned int unum = num;
  int digs = digits(unum, base);
  char* binNum = (char*) malloc(sizeof(char) * (digs + 1));
  int x = digs;
  while (unum / base > 0) {
    binNum[digs - 1] = num_key[unum % base];
    unum = unum / base;
    digs--;
  }
  binNum[0] = num_key[unum % base];
  binNum[x] = '\0';
  return binNum;
}

// Helper method to find how many digits are required to represent the number
// in the base specified
int digits(unsigned int num, int base) {
  int i = 0;
  while (num / base > 0) {
    i++;
    num = num / base;
  }
  return i + 1;
}
