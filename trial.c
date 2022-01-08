
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>  // To catch the signal for ctrl + c
#include <stdlib.h>  // Needed for signal handler
#include <unistd.h>  // To define sleep

sem_t *sema;
char *name = "named_semaphore";
int VALUE = 0;
int SLEEP_TIME = 2;

void int_handler(int s)
{
    sem_close(sema);
    sem_unlink(name);
    printf("\n\n\nCaught signal %d\n\n\n", s);
    exit(1);
}

void *firstThread(void *arg)
{
    
    printf("\n Entered firstThread..\n");
    sem_wait(sema);
    printf("\n firstThread Reduced Semaphore by 1a..\n");
    sem_wait(sema);
    printf("\n firstThread Reduced Semaphore by 1b..\n");
    sem_wait(sema);
    printf("\n firstThread Just Exiting...\n");
    return 0;
}

void *secondThread(void *arg)
{

    printf("\n Entered secondThread..\n");
    sem_wait(sema);
    printf("\n secondThread Reduced Semaphore by 1a..\n");
    sem_wait(sema);
    printf("\n secondThread Reduced Semaphore by 1b..\n");
    sem_wait(sema);
    printf("\n secondThread Just Exiting...\n");
    return 0;
}

int main()
{
    int testInteger;

    signal(SIGINT, int_handler);
    
    printf("Open or Create a named semaphore, %s, its value is %d\n", name, VALUE);
    sema = sem_open(name, O_CREAT, 0666, VALUE);
 
    pthread_t t1, t2;

    printf("Enter number of threads (1 or 2): ");
    scanf("%d", &testInteger);
    printf("Number = %d\n", testInteger);

    if (testInteger == 1) {
        pthread_create(&t1, NULL, firstThread, NULL);
    }
    else if (testInteger == 2) {
        pthread_create(&t1, NULL, firstThread, NULL);
        pthread_create(&t2, NULL, secondThread, NULL);
    } 
    else {
        printf("Number not 1 or 2 - exiting...");
        sem_close(sema);
        sem_unlink(name);
        exit(0);
    }

    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1a..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1b..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1c..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1d..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1e..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1f..\n");
    sem_post(sema);
    sleep(SLEEP_TIME);
    printf("\nAdded to Semaphore by 1g..\n");
    sem_post(sema);

    // pthread_join(t1, NULL);             // waits for the thread t1 to terminate
    // pthread_join(t2, NULL);
    // pthread_join(t3, NULL);
    sleep(SLEEP_TIME);
    printf("\nWrapping main function..\n");
    sem_close(sema);
    sem_unlink(name);
    return 0;
}
