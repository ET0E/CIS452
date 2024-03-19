#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main(){
    int foo = sched_getscheduler(getpid());
    printf("%d\n", foo);
    return 0;
}