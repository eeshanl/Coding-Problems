// Enter argument to ask user how many fibonacci numbers they want to print

#include "stdio.h"
#include "stdlib.h"

void printFib(int n) {
  for (int i = 0; i < n; i++) {
    static int first = 0;
    static int second = 1;
    static int next = 1;
    if (i == n - 1) {
      printf("%d\n", next);
    } else {
      printf("%d ", next);
    }
    next = first + second;
    first = second;
    second = next;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "enter arg\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  printFib(n);
  return 0;
}
