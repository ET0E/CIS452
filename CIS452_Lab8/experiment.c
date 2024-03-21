#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

#define NLOOPS 500000000

int main() {

    //define variables to use during the program
    int status;
    struct sched_param param;
    int joinedCPU = 0;
    cpu_set_t set;
    pid_t pid1;
    pid_t pid2;

    //give the program a CPU set
    CPU_SET(joinedCPU, &set);

    //fork the first child process
    pid1 = fork();

    //set the scheduler to IDLE and give the child process an affinity
    if(pid1 == 0){
        param.sched_priority = 0;
        if (sched_setscheduler(getpid(), SCHED_IDLE, &param) == -1) {
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        if (sched_setaffinity(0, sizeof(set), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        long sum = 0;
        for (long j = 0; j < NLOOPS; j++) {
            sum += j;  // meaningless work to keep the CPU busy
        }

        printf("SCHED_IDLE\n");

        return 0;
    }

    pid2 = fork();

    if(pid2 == 0){
        param.sched_priority = 0;
        if (sched_setscheduler(getpid(), SCHED_OTHER, &param) == -1) {
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        if (sched_setaffinity(0, sizeof(set), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        long sum = 0;
        for (long j = 0; j < NLOOPS; j++) {
            sum += j;  // meaningless work to keep the CPU busy
        }

        printf("SCHED_OTHER\n");

        return 0;
    }

    else{
        waitpid(pid1, &status);
        waitpid(pid2, &status);
    }

    return 0;
}