#ifndef measure_h_INCLUDED
#define measure_h_INCLUDED
#include <sys/time.h>
#include <stdio.h>

void print_time(struct timeval start, struct timeval end) {
    long long elapsed_micros = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
    double elapsed_ms = elapsed_micros / 1000.0;
    printf("Elapsed time: %.3f ms\n", elapsed_ms);
}

#endif 
