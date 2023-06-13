/* @Author
Student Name: Fatmagül İlker
Date: 26.10.2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
   FIFORep* fifo_new=new FIFORep();
   this->mFinishedProcess=fifo_new;
   delete fifo_new;
}

CPURep::~CPURep()
{
    delete this->mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    if(p->remainingTime==1){ //if running process is done, set end time- remaining time and send the process to finishedprocess fifo.
        p->remainingTime=0;
        p->endTime=time+1;
        p->setNext(NULL);
        this->getFinishedProcess()->queue(p);
        return NULL;
    } 
    else{ //if process is not finished, continue.
        p->remainingTime=p->remainingTime-1;
        return p;
    }
 
}

FIFORep* CPURep::getFinishedProcess()
{
    if(this==NULL)
    {
        return NULL;
    }
    else
    {
        return this->mFinishedProcess;
    }
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    if(finishedProcess==NULL){
        this->mFinishedProcess=NULL;
    }
    this->mFinishedProcess=finishedProcess;
}