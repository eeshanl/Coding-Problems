// Enter argument to ask user how many fibonacci numbers they want to print

#include "stdio.h" // printf & fprintf
#include "stdlib.h" // for atoi

void printFib(unsigned long int n) {
  for (unsigned long int i = 0; i < n; i++) {
    static unsigned long int first = 0;
    static unsigned long int second = 1;
    static unsigned long int next = 1;
    if (i == n - 1) {
      printf("%lu\n", next);
    } else {
      printf("%lu ", next);
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
  unsigned long int n = atoi(argv[1]);
  printFib(n);
  return 0;
}
