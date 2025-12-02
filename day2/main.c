#include <sys/time.h>
#include "part_1.c"
#include "part_2.c"

int main(){
  struct timeval start, end;
  long long elapsed_micros;
  gettimeofday(&start, NULL);
  part_1();
  gettimeofday(&end, NULL);
  elapsed_micros =
      (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
  printf("Elapsed time: %lld microseconds\n", elapsed_micros);

  gettimeofday(&start, NULL);
  part_2();
  gettimeofday(&end, NULL);
  elapsed_micros =
      (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);

  printf("Elapsed time: %lld microseconds\n", elapsed_micros);
}
