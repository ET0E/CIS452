#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int policy;
    struct sched_param param;

    // Get the scheduling policy of the current process
    policy = sched_getscheduler(0);
    
    // Print the scheduling policy ID
    printf("Scheduling Policy ID: %d\n", policy);

    // Get and print the corresponding scheduling policy name
    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling Policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling Policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling Policy: SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("Scheduling Policy: SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("Scheduling Policy: SCHED_IDLE\n");
            break;
        case SCHED_DEADLINE:
            printf("Scheduling Policy: SCHED_DEADLINE\n");
            break;
        default:
            printf("Unknown Scheduling Policy\n");
            break;
    }

    return 0;
}
