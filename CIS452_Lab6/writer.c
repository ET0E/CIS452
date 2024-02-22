#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


#define SHM_SIZE 1024

struct sharedData{
    int writeDone;
    int readDone;
    int close_write;
    char message[SHM_SIZE];
};

int main(){
    key_t mykey = ftok("/tmp", 0xa04f01);
    int shmId;
    char user_input[30];
    struct sharedData* sharedData;

    if ((shmId =
         shmget (mykey, sizeof(struct sharedData), IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    if ((sharedData = shmat (shmId, NULL, 0)) == (void *) -1) {
        perror ("can't attach\n");
        exit (1);
    }

    sharedData->readDone = 1;
    sharedData->close_write = 0;
    
    while(1){

        printf("User Input: ");
        fgets(user_input, sizeof(user_input), stdin);

        if(strcmp(user_input, "quit\n") == 0){
            sharedData->close_write = 1;
            break;
        }

        while(sharedData->readDone == 0){};

        strncpy(sharedData->message, user_input, SHM_SIZE);

        sharedData->writeDone = 1;
    }

    sharedData->writeDone = 1;

    if (shmdt (sharedData) < 0) {
        perror ("just can't let go\n");
        exit (1);
    }

    shmctl(shmId, IPC_RMID, 0);

    return 0;
}