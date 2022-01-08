
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

void *calc(sem_t *sema)
{
    printf("Hello_calc\n");
    /*sem_wait(sema);
    printf("Hello\n");
    sem_wait(sema);
    printf("Hello\n");
    sem_wait(sema);
    printf("Hello\n");
    sem_wait(sema);
    printf("Hello\n");
    sem_wait(sema);*/
}

int main(int argc, char *argv[])
{
    char *name = "my2_semaphore";
    int VALUE = 0;
    int i;
    char ch;
    int iter = 20;
    int testInteger;
    int blob;

    sem_t *sema;
    //If semaphore with name does not exist, then create it with VALUE

    printf("Open or Create a named semaphore, %s, its value is %d\n", name, VALUE);
    sema = sem_open(name, O_CREAT, 0666, VALUE);
    printf("Add semaphore by 1\n");
    sem_post(sema);
    //wait on semaphore sema and decrease it by 1

    printf("Decrease semaphore by 1\n");
    sem_wait(sema);
    printf("Hello1\n");
    //sem_wait(sema);
    //printf("Hello2\n");

    //pthread_t tid;
    //pthread_create(&tid, NULL, calc, (void *) &sema);

    //sem_wait(sema);
    //printf("Hello3\n");

    //add semaphore sema by 1

    printf("Enter an integer: ");
    scanf("%d", &testInteger);
    printf("Number = %d\n", testInteger);

    printf("Add semaphore by 1\n");
    sem_post(sema);

    //Before exit, you need to close semaphore and unlink it, when all  processes have
    //finished using the semaphore, it can be removed from the system using sem_unlink
    sem_close(sema);
    sem_unlink(name);
    return 0;
}
