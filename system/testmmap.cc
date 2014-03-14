#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h> 
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

struct PipeShm
{
    int init;
    sem_t sema;
};

PipeShm * sharedPipe = NULL;

void error_out(const char* errstr)
{
    if (errstr)
        printf("%s\n", errstr);

    exit(0);
}

void func1() 
{
    int myFd = shm_open ("/myregion", O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (myFd == -1)
        error_out ("shm_open");

    // allocate some memory in the region in the size of the struct
    int retAlloc = ftruncate (myFd, sizeof *sharedPipe);
    if (retAlloc < 0)  // check if allocation failed
        error_out("ftruncate");

    // map the region and shared in with all the processes
    sharedPipe = (PipeShm *)mmap (NULL, sizeof *sharedPipe, PROT_READ|PROT_WRITE, MAP_SHARED, myFd, 0);
    if (sharedPipe == MAP_FAILED)  // check if the allocation failed
        error_out("mmap");
}

void func2() 
{
    // put initial value
    int value = -10;
    // get the value of the semaphore
    sem_getvalue(&sharedPipe->sema, &value);
    printf("sem value=%d\n", value);
}

int main() 
{
    func1();
    fork();
    func2();
    return 0;
}

