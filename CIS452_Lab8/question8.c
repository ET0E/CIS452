#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

int main() {
    int policy;
    struct sched_param param;

    // Get the current scheduling policy of the process
    policy = sched_getscheduler(getpid());
    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    // Print the current scheduling policy ID
    printf("Current Scheduling Policy ID: %d\n", policy);

    // Set the scheduling policy to SCHED_RR
    param.sched_priority = sched_get_priority_max(SCHED_RR);  // Retain the current priority
    if (sched_setscheduler(getpid(), SCHED_RR, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    // Check if the scheduling policy was successfully changed
    policy = sched_getscheduler(getpid());
    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    // Print the new scheduling policy ID
    printf("New Scheduling Policy ID: %d\n", policy);

    return 0;
}
