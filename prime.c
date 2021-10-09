#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct task {
  int lower_limit, upper_limit, partition_size;
  int count;
  int *found;
};

/**
 * @brief checks if an input is a prime number
 *
 * @param number integer input
 * @return int boolean whether it is a prime number
 */
int is_prime(int number);

/**
 * @brief defines the range each thread should work with
 *
 * @param n upper range of numbers
 * @param id id of the thread
 * @param n_threads number of threads
 * @param size size of the partition range
 * @param start start of the partition
 * @param end end of the partition
 */
void define_range(int n, int id, int n_threads, int *size, int *start, int *end);

/**
 * @brief finds the prime numbers within a given range
 *
 * @param ptr pointer to a task instance
 * @return void* nothing
 */
void *find_primes(void *ptr);

/**
 * @brief prints the array (should only be used by the driver)
 *
 * @param arr array to print
 * @param n number of elements in array
 */
void print_arr(int *arr, int n);

int main(int argc, char *argv[]) {
  int limit, i, n_threads, total_found;
  pthread_t *threads;
  struct task *tasks;

  if (argc <= 1) {
    fprintf(stderr, "Usage: %s [upper limit]\n", argv[0]);
    return EXIT_FAILURE;
  }

  n_threads = atoi(getenv("NTHREADS"));
  limit = atoi(argv[1]);

  threads = malloc(n_threads * sizeof(pthread_t));
  tasks = malloc(n_threads * sizeof(struct task));

  for (i = 0; i < n_threads; i++) {
    define_range(limit, i, n_threads, &tasks[i].partition_size, &tasks[i].lower_limit,
                 &tasks[i].upper_limit);
    pthread_create(&threads[i], NULL, find_primes, &tasks[i]);
  }

  total_found = 0;

  /* aggregate from main thread so it'll be printed in order */
  for (i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
    total_found += tasks[i].count;

    printf("thread %d ", i);

    if (tasks[i].count > 0) {
      printf("found %d prime numbers: ", tasks[i].count);
      print_arr(tasks[i].found, tasks[i].count);
    } else {
      printf("found no prime numbers :(\n");
    }
    free(tasks[i].found);
  }
  printf("total of prime numbers found: %d\n", total_found);

  /* free resources */
  free(threads);
  free(tasks);

  return EXIT_SUCCESS;
}

int is_prime(int number) {
  int i;

  if (number <= 1)
    return 0;

  if (number <= 3)
    return 1;

  if (number % 2 == 0 || number % 3 == 0)
    return 0;

  for (i = 5; i * i <= number; i += 6)
    if (number % i == 0 || number % (i + 2) == 0)
      return 0;

  return 1;
}

void define_range(int n, int id, int n_threads, int *size, int *start, int *end) {
  int partition_size, lower_limit, upper_limit;
  partition_size = n / n_threads;
  lower_limit = id * partition_size;
  upper_limit = lower_limit + partition_size;

  if (id == n_threads - 1)
    /* add excess to last thread */
    upper_limit += n % partition_size;

  *size = partition_size;
  *start = lower_limit;
  *end = upper_limit;
}

void *find_primes(void *ptr) {
  struct task *task = (struct task *)ptr;
  int i;

  task->count = 0;
  task->found = malloc(sizeof(int) * task->partition_size);

  for (i = task->lower_limit; i < task->upper_limit; i++)
    if (is_prime(i))
      task->found[task->count++] = i;

  return NULL;
}

void print_arr(int *arr, int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
