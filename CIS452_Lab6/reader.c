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

int main(int argc, char* argv[]){
    key_t mykey = ftok("/tmp", 0xa04f01);
    int shmId;
    struct sharedData* sharedData;

    int reader = atoi(argv[1]);

    if ((shmId =
         shmget (mykey, SHM_SIZE, S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }

    if ((sharedData = shmat (shmId, NULL, 0)) == (void *) -1) {
        perror ("can't attach\n");
        exit (1);
    }

    printf("Reader Process Ready \n");
    sharedData->close_write = 0;

    while(1){
        
        while(sharedData->writeDone == 0){};

        if(sharedData->close_write == 1){
            break;
        }

        printf("Message from Writer to reader %d: %s", reader, sharedData->message);

        sharedData->readDone = 1;
        sharedData->writeDone = 0;
    }

    if (shmdt (sharedData) < 0) {
        perror ("just can't let go\n");
        exit (1);
    }

    return 0;
}