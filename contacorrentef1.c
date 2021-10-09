#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 0xfffff
#define N_THREADS 10

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
  pthread_t threads[N_THREADS];
  int i;
  saldo = 1000.00;

  for (i = 0; i < N_THREADS; i++) {
    if (i % 2 == 0)
      /* realiza uma "infinidade" de depositos, e.g. 2147483000 depositos de 5.0
       * unidades monetárias */
      pthread_create(&threads[i], NULL, depositos, NULL);
    else
      /* realiza uma "infinidade" de saques, e.g. 2147483000 saques de 2.0 unidades
       * monetárias */
      pthread_create(&threads[i], NULL, saques, NULL);
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(threads[i], NULL);
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
