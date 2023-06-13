/* @Author
Student Name: Fatmagül İlker
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    this->mpRunningProcess=NULL;
    FIFORep* fifo_0= new FIFORep();
    FIFORep* fifo_1= new FIFORep();
    FIFORep* fifo_2= new FIFORep();
    this->mpProcessFIFO[0]=fifo_0;
    this->mpProcessFIFO[1]=fifo_1;
    this->mpProcessFIFO[2]=fifo_2;
    CPURep* cpu=new CPURep();
    this->pCpuObj=cpu;
    this->timeSliceCount=0;
    this->totalTime=0;
}
SchedulerRep::~SchedulerRep()
{
    delete this->pCpuObj;
    delete this->mpProcessFIFO[0];
    delete this->mpProcessFIFO[1];
    delete this->mpProcessFIFO[2];
    delete this->mpRunningProcess;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return this->mpProcessFIFO[index];  
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index]=fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    this->mpRunningProcess=p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    int index=0;
    if(p->getProcessType()=="B")  
        index=1;
    if(p->getProcessType()=="C")
        index=2;
    this->getProcessFIFO(index)->queue(p); //place p to the appropriate fifo in scheduler.
}

ProcessRep* SchedulerRep::popProcess()
{
    if(this->getProcessFIFO(0)->getHead()!=NULL){    //if the fifo with 'A' type is not null, remove the head and return it.
        return this->getProcessFIFO(0)->dequeue();
    }
    else if(this->getProcessFIFO(1)->getHead()!=NULL){
        return this->getProcessFIFO(1)->dequeue(); //if the fifo A is null, B is not null, remove and return the head of it.
    }
    else if(this->getProcessFIFO(2)->getHead()!=NULL){
        return this->getProcessFIFO(2)->dequeue(); //if A and B fifos are null, C is not null, remove and return the head of it.
    }
    else{
        return NULL; //if all of them are null, return NULL
    }     
}

bool SchedulerRep::checkTimeSlice()
{   
    string typ=this->getRunningProcess()->getProcessType();
    int limit=0;
    if(typ=="A")
        limit=2;  //Quantum time of A=2
    else if(typ=="B")
        limit=4;  //Quantum time of B=4
    else if(typ=="C")
        limit=8;  //Quantum time of C=8
    if(limit==this->timeSliceCount) 
        return true;  //If timeslicecount reach the quantum time of the running process, return true; otherwise return false
    else
        return false;
}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){ 
    
    if(p->getProcessTime()==p->remainingTime)
    {  //if cpu utilizes that p for the first time, set starttime to totaltime.
        p->startTime=this->totalTime;
    }
    
    p=this->pCpuObj->runCPU(p,totalTime); //it returns null, if remaining time is 0.
    if(p!=NULL)
    {  
        totalTime++;
        timeSliceCount++;
        return p;
    }
    else
     {  //if remaining time is zero, make slicecount 0, update the running process.
        timeSliceCount=0;
        totalTime++; 
        this->setRunningProcess(this->popProcess());
        return NULL;
    } 
    
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.
    */
    bool is_quantum_zero=false;
    ProcessRep* p= new ProcessRep(type, id, arrivalTime, processTime); //Initiliaze new process
    this->pushProcess(p); //put new process to scheduler.

    if(this->getRunningProcess()==NULL) 
    { //if there is no running process at that time, send new process to cpu.
        this->setRunningProcess(this->popProcess());
        p=this->sendProcessToCPU(p);
    }
    else{ //if there is a running process
        is_quantum_zero=this->checkTimeSlice(); 
            if(is_quantum_zero==true){ //if timeslicecount reach the quantum limit. update the running process.
                timeSliceCount=0;
                this->pushProcess(this->getRunningProcess());
                this->setRunningProcess(this->popProcess());
                p=this->sendProcessToCPU(this->getRunningProcess()); 
            
            }
            else
            {
            string type_running=this->getRunningProcess()->getProcessType();
            string type_new=p->getProcessType();
            if((type_new=="A" && type_running!="A") || (type_new=="B" && type_running=="C"))
            {  //if the new coming process has a higher priority type than the running process, update the running process
            this->pushProcess(this->getRunningProcess()); 
            this->setRunningProcess(this->popProcess()); 
            timeSliceCount=0;  //new progres starts.
            p=this->sendProcessToCPU(p);
            }
            else{ 
                p=this->sendProcessToCPU(this->getRunningProcess()); 
            }
            }
        }
   
    

     
}
void SchedulerRep::schedule(ProcessRep* p)
{
   
    if(this->getRunningProcess()!=NULL && this->getProcessFIFO(0)!=NULL && this->getProcessFIFO(1)!=NULL  && this->getProcessFIFO(2)!=NULL)
    { 
        bool is_quantum_zero=false;
        is_quantum_zero=this->checkTimeSlice();
        if( is_quantum_zero==true)
        { //check quantum
            timeSliceCount=0;
            this->pushProcess(this->getRunningProcess());
            this->setRunningProcess(this->popProcess());
    }
    p=this->sendProcessToCPU(this->getRunningProcess());  //take one more step with the already running process
    }
    //if all the fifos and running process are empty, do nothing. 
}
