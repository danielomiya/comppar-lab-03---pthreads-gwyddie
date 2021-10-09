#include <stdio.h>
#include <stdlib.h>

#define N 0xfffff
#define ITER 10

double saldo;

/**
 * @brief adds 5 to saldo N times
 *
 * @param ptr nothing
 * @return void* nothing
 */
void *depositos(void *ptr);

/**
 * @brief subtracts 2 from saldo N times
 *
 * @param ptr nothing
 * @return void* nothing
 */
void *saques(void *ptr);

int main() {
  int i;
  saldo = 1000.00;

  for (i = 0; i < ITER; i++) {
    if (i % 2 == 0)
      /* realiza uma "infinidade" de depositos, e.g. 2147483000 depositos de 5.0
       * unidades monetárias */
      depositos(NULL);
    else
      /* realiza uma "infinidade" de saques, e.g. 2147483000 saques de 2.0 unidades
       * monetárias */
      saques(NULL);
  }

  printf("Saldo final: %.2lf\n", saldo);

  return EXIT_SUCCESS;
}

void *depositos(void *ptr) {
  int i;
  for (i = 0; i < N; i++)
    saldo += 5;
  return NULL;
}

void *saques(void *ptr) {
  int i;
  for (i = 0; i < N; i++)
    saldo -= 2;
  return NULL;
}
