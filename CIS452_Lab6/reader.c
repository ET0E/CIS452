#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHM_SIZE 1024

int main(){
    key_t mykey = ftok("/tmp", 0xa04f01);
    int shmId;
    char* shmPtr;
    char* user_input;

    if ((shmId =
         shmget (mykey, SHM_SIZE, S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    if ((shmPtr = shmat (shmId, NULL, 0)) == (void *) -1) {
        perror ("can't attach\n");
        exit (1);
    }

    while(1){
        printf("User Input: ");
        scanf("%s\n", user_input);

        if(strcmp(user_input, "quit")){
            exit(1);
        }

        strncpy(shmPtr, user_input, SHM_SIZE);
    }

}