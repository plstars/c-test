#include <stdlib.h>
#include <sys/time.h>
#include "coursework.c"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void simulator1() { 

    int PID = 1;
    int i, Hash, BurstTime, RemainingBurstTime, Locality, Width;
    Process * pProcess; 
    srand ( time(NULL) );
    pProcess = generateProcess(PID); 

    printf("ADMITTED: [PID = %d, Hash = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
            pProcess->iPID, pProcess->iHash, pProcess->iBurstTime, pProcess->iRemainingBurstTime, 
            pProcess->iLocality, pProcess->iWidth); 

    for (i = 0; i < 6; ++i){
        runPreemptiveProcess(pProcess, 0);

        BurstTime = pProcess->iBurstTime;
        RemainingBurstTime = pProcess->iRemainingBurstTime;
        Locality = pProcess->iLocality;
        Width = pProcess->iWidth;

        printf("READY: [PID = %d, BurstTime = %d, RemainingBurstTime = %d, Locality = %d, Width = %d]\n", 
            PID,  BurstTime, RemainingBurstTime, Locality, Width); 

    }

    printf("TERMINATED: [PID = %d, ResponseTime = %d, TurnAroundTime = %d]\n", 
            pProcess->iPID, 0, pProcess->iBurstTime);

}