#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NLOOPS 500000000
#define NUM_PROCS 8

int main(int argc, char *argv[])
{
    cpu_set_t set;
    int joinedCPU = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s {0|1}\n", argv[0]);
        exit(1);
    }

    CPU_SET(joinedCPU, &set);

    if (atoi(argv[1]) != 0) {
        // ADD LINE HERE TO SET AFFINITY
        if (sched_setaffinity(0, sizeof(set), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        printf("CPU affinity set successfully.\n");
    }

    pid_t pid;
    for (int i = 0; i < NUM_PROCS - 1; i++) {
        if ((pid = fork()) < 0) {
            perror("Problem forking");
            exit(1);
        } else if (!pid) {
            cpu_set_t child_set;
            if (sched_getaffinity(0, sizeof(set), &child_set) == -1) {
                perror("sched_getaffinity");
                exit(EXIT_FAILURE);
            }
            printf("Child process %d CPU affinity : ", getpid());
            for (int j = 0; j < CPU_SETSIZE; j++) {
                if (CPU_ISSET(j, &child_set)) {
                    printf("%d ", j);
                }
            }
            printf("\n");
            break;
        }
    }

    long sum = 0;
    for (long j = 0; j < NLOOPS; j++) {
        sum += j;  // meaningless work to keep the CPU busy
    }

    return 0;
}