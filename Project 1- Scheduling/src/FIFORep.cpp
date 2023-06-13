/* @Author
Student Name: Fatmagül İlker
Date: 26.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
   this->mpHead=NULL;
   this->mpTail=NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
   this->mpHead=head;
   this->mpTail=head;
}


FIFORep::~FIFORep()
{
}

void FIFORep::setHead(ProcessRep* head)
{
   this->mpHead=head;
}

ProcessRep* FIFORep::getHead()
{
   return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
   this->mpTail=tail;
}

ProcessRep* FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the queue.
    */
    p->setNext(NULL);
    if(this->getHead()==NULL) //if there is no element in fifo, p will be the head.
    {
        this->setHead(p);
    }
    else if(this->getHead()->getNext()==NULL) //if there is one element in fifo, p will be the tail
    {
        this->getHead()->setNext(p);
        this->setTail(p);
    }
    else  //in all other cases
    {  
        this->getTail()->setNext(p);
        this->setTail(p);
        this->getTail()->setNext(NULL);
    }
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function remove a process from the head of the queue and returns it.
    */   

    if(this->getHead()==NULL) //if there is no element in fifo, return NULL
    {
        return NULL;
    }
   else{ //else remove the head, the second element will be the head.
        ProcessRep* temp=this->getHead();
        this->setHead(temp->getNext());
        return temp; 
   }
   
}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 

    if(this->getHead()==NULL) {return NULL; }
    else
    {
        ProcessRep* temp=this->getHead();
        while(temp!=NULL)
        {
        if(temp->getProcessID()==id)
            return temp;
        else
            temp=temp->getNext();
    }
    if(temp==NULL) return NULL;
    else return temp;
    }
  
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */

    if(this==NULL)
    {
        return;
    }
    else
    {
        ProcessRep* curr=this->getHead();
        while(curr!=NULL)
        {
            cout<<curr->getProcessType()<<curr->getProcessID()<<" "<< curr->startTime <<" "<< curr->endTime<<" ";
            curr=curr->getNext();
        }
    }
}