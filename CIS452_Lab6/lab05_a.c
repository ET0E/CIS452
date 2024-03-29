#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define FOO 4096

int main () {
    int shmId;
    char *shmPtr;
    struct shmid_ds shmid_ds_info;

    if ((shmId =
         shmget (IPC_PRIVATE, FOO,
                 IPC_CREAT | S_IRUSR | S_IWUSR)) < 0) {
        perror ("i can't get no..\n");
        exit (1);
    }
    if ((shmPtr = shmat (shmId, NULL, 0)) == (void *) -1) {
        perror ("can't attach\n");
        exit (1);
    }
    printf ("value a: %lu\t value b: %lu\n", (unsigned long) shmPtr,
            (unsigned long) shmPtr + FOO);
    if (shmdt (shmPtr) < 0) {
        perror ("just can't let go\n");
        exit (1);
    }

    if (shmctl(shmId, IPC_STAT, &shmid_ds_info) < 0) {
        perror("shmctl IPC_STAT failed");
        exit(1);
    }
    printf("Size of shared memory segment %lu\n", shmid_ds_info.shm_segsz);

    if (shmctl (shmId, IPC_RMID, 0) < 0) {
        perror ("can't deallocate\n");
        exit (1);
    }

    return 0;
}