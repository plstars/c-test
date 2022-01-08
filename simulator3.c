#include <semaphore.h>
#include "coursework.c"
#include "linkedlist.c"

sem_t s; 

void * processGenerator(LinkedList * Ready) { 

    int PID;
    srand ( time(NULL) );

    for (PID = 0; PID < NUMBER_OF_PROCESSES; ++PID){
        Process * pProcess;
        pProcess = generateProcess(PID);
        addLast(pProcess, Ready); 
        printf("ADMITTED: [PID = %d, Hash = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
        pProcess->iPID, pProcess->iHash, pProcess->iBurstTime, pProcess->iRemainingBurstTime, 
        pProcess->iLocality, pProcess->iWidth); 
    }

}

void processSimulator(LinkedList * Ready, LinkedList * Terminated){ 

    int timeRunning, timeStart;

    do { 

        Element * head;
        Process * process;
        head = getHead(*Ready); 
        process = head->pData; 
        removeFirst(Ready);
        runPreemptiveProcess(process, 0); 

        if (process->iRemainingBurstTime == 0){
            addLast(process, Terminated); 
            timeStart = getDifferenceInMilliSeconds(process->oTimeCreated, process->oFirstTimeRunning);
            timeRunning = getDifferenceInMilliSeconds(process->oFirstTimeRunning, process->oLastTimeRunning);
            printf("TERMINATED: [PID = %d, ResponseTime = %d, TurnAroundTime = %d]\n", process->iPID, timeStart, timeRunning);
        }

        else {
            printf("READY: [PID = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
            process->iPID,  process->iBurstTime, process->iRemainingBurstTime, process->iLocality, process->iWidth); 

            addLast(process, Ready);
        }

    } while (getHead(*Ready) != NULL);
}

void terminationDaemon(LinkedList * Terminated){
    do { 
        removeFirst(Terminated);
    } while (getHead(*Terminated) != NULL);
}



int main() { 

    int PID, timeRunning, timeStart;

    LinkedList Ready = LINKED_LIST_INITIALIZER;
    LinkedList Terminated = LINKED_LIST_INITIALIZER;

    pthread_t pGen, pSim, tDae; 

    sem_init(&s, 0, 1);

    pthread_create(&pGen, NULL, processGenerator, (void *) &Ready); 
    //pthread_create(&pSim, NULL, processSimulator, (void *) &Ready ); 
    //pthread_create(&tDae, NULL, terminationDaemon, (void *) &Terminated); 

    pthread_join(pGen, NULL);
    //pthread_join(pSim, NULL);
    //pthread_join(tDae, NULL);


    //processGenerator(&Ready);
    //processSimulator(&Ready, &Terminated);
    //terminationDaemon(&Terminated);

}
 
// process generator goes to sleep when there are max concurrent processes
// wakes up process simulator when new processes are added to ready queue 
// runs preeptive process them (round robin)
// add to terminated is used when the process is done
// add to the end of the ready queue when not done
// termination deamon is woken when processes are added to the terminated queue
// termination deamon removes from the queue, clears resources associated with them 
// checks if there are any more processes and wakes up process generator if there is 