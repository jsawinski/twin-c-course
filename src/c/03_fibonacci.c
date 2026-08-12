/* Die Fibonacci-Sequenz. */
#include <stdio.h>

int main() {
  int a = 0;
  int b = 1;

  for(int i = 1; i <= 16; i = i+1) {
    int next = a + b;
    a = b;
    b = next;

    printf("Fibonacci %d: %d\n", i, a);
  }
  return 0;
}
