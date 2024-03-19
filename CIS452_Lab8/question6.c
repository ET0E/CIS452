#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main(){
    struct sched_param param;

    int foo = sched_getscheduler(getpid());
    printf("%d\n", foo);

    switch (foo) {
        case SCHED_OTHER:
            printf("Scheduling Policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling Policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling Policy: SCHED_RR\n");
            break;
        default:
            printf("Unknown Scheduling Policy\n");
            break;
    }

    return 0;
}