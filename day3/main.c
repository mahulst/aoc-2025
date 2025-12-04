#include "measure.h"
#include "part_1.c"
#include "part_2.c"
#include <sys/resource.h>
#include <sys/time.h>

int main() {
  struct timeval start, end;
  struct rusage usage;
  gettimeofday(&start, NULL);
  part_1();
  gettimeofday(&end, NULL);
  print_time(start, end);
  gettimeofday(&start, NULL);
  part_2();
  gettimeofday(&end, NULL);

  getrusage(RUSAGE_SELF, &usage);
  printf("Peak memory usage (RSS): %ld KB\n", (long)usage.ru_maxrss / 1024);

  print_time(start, end);
}

