#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *fib(void *ptr) {
  pthread_t thread1, thread2;
  int n, n1, n2;
  unsigned long int result;
  void *result1, *result2;

  n = *(int *)ptr;

  if (n <= 1) {
    result = n;
  } else {
    n1 = n - 1;
    n2 = n - 2;
    pthread_create(&thread1, NULL, fib, &n1);
    pthread_create(&thread2, NULL, fib, &n2);

    pthread_join(thread1, &result1);
    pthread_join(thread2, &result2);

    result = (unsigned long int)(result1) + (unsigned long int)(result2);
  }

  return (void *)(result);
}

int main(void) {
  pthread_t thread;
  int n;
  void *result;

  printf("Type the number of the sequence you'd like to calc: ");
  scanf("%d", &n);

  pthread_create(&thread, NULL, fib, &n);
  pthread_join(thread, &result);

  printf("%ld\n", (unsigned long int)(result));

  return EXIT_SUCCESS;
}
