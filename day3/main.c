#include <sys/time.h>
#include "part_1.c"
#include "part_2.c"
#include "measure.h"

int main(){
  struct timeval start, end;
  gettimeofday(&start, NULL);
  part_1();
  gettimeofday(&end, NULL);
  print_time(start,end);
  gettimeofday(&start, NULL);
  part_2();
  gettimeofday(&end, NULL);
  print_time(start,end);
}

