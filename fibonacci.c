#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void *handle_failure() {
  fprintf(stderr, "ERROR: Failed to join thread\n");
  exit(EXIT_FAILURE);
  return NULL;
}

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

    if (pthread_join(thread1, &result1) || pthread_join(thread2, &result2))
      return handle_failure();

    result = (unsigned long int)(result1) + (unsigned long int)(result2);
  }

  return (void *)(result);
}

int main(void) {
  struct timeval started_at, ended_at;
  double ms_spent;
  pthread_t thread;
  int n;
  void *result;

  printf("Type the number of the sequence you'd like to calc: ");
  scanf("%d", &n);

  gettimeofday(&started_at, NULL);
  pthread_create(&thread, NULL, fib, &n);

  if (pthread_join(thread, &result))
    handle_failure();

  gettimeofday(&ended_at, NULL);
  ms_spent = ((ended_at.tv_sec * 1000000 + ended_at.tv_usec) -
              (started_at.tv_sec * 1000000 + started_at.tv_usec));

  printf("%ld\n", (unsigned long int)(result));
  printf("spent %lf seconds calculating\n", (double)ms_spent / 1e+6);

  return EXIT_SUCCESS;
}
