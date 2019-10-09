#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t lock;

typedef struct workitem {
  void (*fn)(double *);
  int current;
  int len;
  double *data;
  int started;
} workitem;

static void* launchThread(void *in)
{
  int n;
  workitem *data = (workitem*) in;
  volatile int started = 0;
  while (!(started = data->started));
  while (1) {

    pthread_mutex_lock(&lock);
    n = data->current++;
    pthread_mutex_unlock(&lock);

    if (n >= data->len) break;
    data->fn(&data->data[n]);
  }
  return NULL;
}

void launchParallel(int numThreads, double *values, int len, void (*fn)(double *))
{
  workitem *data = calloc(1, sizeof(workitem));
  pthread_t th[numThreads];

  memset(th, 0, numThreads*sizeof(pthread_t));

  data->fn = fn;
  data->current = 0;
  data->len = len;
  data->data = values;
  data->started = 0;

  for (int i=0; i<numThreads; i++) {
    assert(0 == pthread_create(&th[i], NULL, launchThread, data));
  }
  data->started = 1;
  for (int i=0; i<numThreads; i++) {
    assert(th[i] && 0==pthread_join(th[i], NULL));
  }
  assert(data->current >= len);
  free(data);
}

void mul2(double *d)
{
  *d = *d * 2;
}

int main(int argc, char **argv)
{
  double vals[100];
  for (int i=0; i<100; i++) {
    vals[i] = i*1.5;
  }
  launchParallel(4 /* Increase this if no error occurs */, vals, 100, mul2);
  for (int i=0; i<100; i++) {
    if (vals[i] != 1.5*2*i) {
      fprintf(stderr, "Expected vals[%d] to have value %.1f, got value %.1f\n", i, (double)1.5*2*i, (double)vals[i]);
    }
  }
  return 0;
}

// Source
// https://www.thegeekstuff.com/2012/05/c-mutex-examples/

// Debug

// (gdb) run
// Starting program: /home/jarye821/Repositories/tdde45-lab5/debugging/workitems
// [Thread debugging using libthread_db enabled]
// Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
// [New Thread 0x7ffff77c4700 (LWP 23110)]
// [New Thread 0x7ffff6fc3700 (LWP 23111)]
// [New Thread 0x7ffff67c2700 (LWP 23112)]
// [New Thread 0x7ffff5fc1700 (LWP 23113)]
// [Thread 0x7ffff5fc1700 (LWP 23113) exited]
// Expected vals[4] to have value 12.0, got value 24.0
// [Thread 0x7ffff67c2700 (LWP 23112) exited]
// Expected vals[10] to have value 30.0, got value 60.0
// Expected vals[11] to have value 33.0, got value 66.0
// [Thread 0x7ffff6fc3700 (LWP 23111) exited]
// Expected vals[12] to have value 36.0, got value 72.0
// [Thread 0x7ffff77c4700 (LWP 23110) exited]
// Expected vals[13] to have value 39.0, got value 78.0
// Expected vals[14] to have value 42.0, got value 84.0
// Expected vals[15] to have value 45.0, got value 90.0
// Expected vals[16] to have value 48.0, got value 96.0
// Expected vals[17] to have value 51.0, got value 102.0
// Expected vals[18] to have value 54.0, got value 108.0
// Expected vals[19] to have value 57.0, got value 114.0
// Expected vals[20] to have value 60.0, got value 120.0
// Expected vals[21] to have value 63.0, got value 252.0
// Expected vals[22] to have value 66.0, got value 264.0
// ...
// (gdb) break 24
// Breakpoint 1 at 0x934: file workitems.c, line 24.
// (gdb) run
// Starting program: /home/jarye821/Repositories/tdde45-lab5/debugging/workitems
// [Thread debugging using libthread_db enabled]
// Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
// [New Thread 0x7ffff77c4700 (LWP 12217)]
// [New Thread 0x7ffff6fc3700 (LWP 12218)]
// [New Thread 0x7ffff67c2700 (LWP 12225)]
// [New Thread 0x7ffff5fc1700 (LWP 12226)]
// [Switching to Thread 0x7ffff67c2700 (LWP 12225)]

// Thread 4 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $1 = 0
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff6fc3700 (LWP 12218)]

// Thread 3 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $2 = 1
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff5fc1700 (LWP 12226)]

// Thread 5 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $3 = 0
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff77c4700 (LWP 12217)]

// Thread 2 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $4 = 0
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff67c2700 (LWP 12225)]

// Thread 4 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $5 = 2
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff6fc3700 (LWP 12218)]

// Thread 3 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $6 = 3
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff5fc1700 (LWP 12226)]

// Thread 5 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $7 = 4
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff77c4700 (LWP 12217)]

// Thread 2 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $8 = 5
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff67c2700 (LWP 12225)]

// Thread 4 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $9 = 6
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff6fc3700 (LWP 12218)]

// Thread 3 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);
// (gdb) print n
// $10 = 7
// (gdb) continue
// Continuing.
// [Switching to Thread 0x7ffff77c4700 (LWP 12217)]

// Thread 2 "workitems" hit Breakpoint 1, launchThread (in=0x555555757260) at workitems.c:24
// 24          data->fn(&data->data[n]);