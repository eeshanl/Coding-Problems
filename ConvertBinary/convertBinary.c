#include <stdio.h>
#include <stdlib.h>

char* convertBinary(int num);

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Enter an argument.\n");
    exit(1);
  }
  printf("%s\n", convertBinary(atoi(argv[1])));
  return 1;
}

char* convertBinary(int num) {
  int x = 1;
  x = x << 30;
  unsigned int unum = num;
  char* binNum = (char*) malloc(sizeof(char) * 33);
  binNum[32] = '\0';
  if (num >= 0) {
    binNum[0] = '0';
  } else {
    binNum[0] = '1';
  }
  for (int i = 1; i < 32; i++) {
    if (unum / x > 0) {
      binNum[i] = '1';
      unum = unum % x;
    } else {
      binNum[i] = '0';
    }
    x >>= 1;
  }
  return binNum;
}
