
#include "simulator1.c"
#include "linkedlist.c"

int main() { 

    int PID, timeRunning, timeStart;
    LinkedList Ready, Terminated;

    for (PID = 0; PID < NUMBER_OF_PROCESSES; ++PID){
        Process * pProcess;
        pProcess = generateProcess(PID);
        addLast(pProcess, &Ready); 
        printf("ADMITTED: [PID = %d, Hash = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
        pProcess->iPID, pProcess->iHash, pProcess->iBurstTime, pProcess->iRemainingBurstTime, 
        pProcess->iLocality, pProcess->iWidth); 
    }

    do { 

        Element * head;
        Process * process;
        head = getHead(Ready); 
        process = head->pData; 
        removeFirst(&Ready);
        runPreemptiveProcess(process, 0); 

        if (process->iRemainingBurstTime == 0){
            addLast(process, &Terminated); 
            timeStart = getDifferenceInMilliSeconds(process->oTimeCreated, process->oFirstTimeRunning);
            timeRunning = getDifferenceInMilliSeconds(process->oFirstTimeRunning, process->oLastTimeRunning);
            printf("TERMINATED: [PID = %d, ResponseTime = %d, TurnAroundTime = %d]\n", process->iPID, timeStart, timeRunning);
        }

        else {
            printf("READY: [PID = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
            process->iPID,  process->iBurstTime, process->iRemainingBurstTime, process->iLocality, process->iWidth); 

            addLast(process, &Ready);
        }

    } while (getHead(Ready) != NULL);

    do { 
        removeFirst(&Terminated);
    } while (getHead(Terminated) != NULL);

}