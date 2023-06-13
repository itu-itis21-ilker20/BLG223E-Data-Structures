//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname:Fatmagül İlker
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    this->head=NULL;  //create empty queue
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    if(this->head==NULL){
        this->head=newnode;   //if the queue is null, make the newnode head.
    }
    else{
        if((newnode->token.val) < (head->token.val) ){
            newnode->next=head;   //if the newnode has lower value than head, update the head 
            head=newnode;
        }
        else{                    
        Node* temp=this->head;
        bool finish=false;  
        while(temp!=NULL && finish==false){  
            if(temp->next==NULL){
                temp->next=newnode; //if temp reaches the end of the queue, add newnode to the end.
                finish=true;
            }
            else if(temp->next->token.val > newnode->token.val){
                newnode->next=temp->next;  //if value of next node bigger than the new one, add newnode before the next
                temp->next=newnode;
                finish=true;
            }
            else{
                temp=temp->next;
            }
        }
        }
        
    }
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //delete and return the head
    Node* temp=head;
    head=head->next;
    temp->next=NULL;
    return temp;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    root=NULL; 
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    if(root!=NULL){
        deleteTree(root);
    }
    root=NULL;
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    if(node!=NULL){
        this->deleteTree(node->left);
        this->deleteTree(node->right);
        delete node;
    }
    return;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
   Node* mergednode= new Node();
   mergednode->token.val= temp1->token.val + temp2->token.val; //value of merged node is the sum of the values of nodes.
   if(temp1->token.val <= temp2->token.val){ //if value of the first node smaller, it will be on the left
    mergednode->token.symbol= temp1->token.symbol + temp2->token.symbol;
    mergednode->left=temp1;
    mergednode->right=temp2;
   }
   else{
    mergednode->token.symbol= temp2->token.symbol + temp1->token.symbol; //if value of the first node bigger, it will be on the right.
    mergednode->left=temp2;
    mergednode->right=temp1;
   }
   return mergednode;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};