//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname:Fatmagül İlker
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){  
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){ 
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    
    //TODO
    for(std::size_t i=0; i< sortedKey.length() ; i++)
    {
        char p=sortedKey[i]; //take the characters in sortedkey one by one
        int frequency=1;
        for(std::size_t j=i+1; j< sortedKey.length() ; j++){
            if(sortedKey[j]== p){ 
                frequency++; //when the same character found, increase frequency by 1.
                if (j==sortedKey.length()-1){
                    i=sortedKey.length(); //when reach the end of list, continue with last index
                }
            }
            else{
                if (j==sortedKey.length())
                {
                    i=sortedKey.length();
                }
                else
                {
                    i=j-1;  //continue with the next new character
                    j=sortedKey.length();  //to break the inside loop, and change the p value by next character
                }
            }
        }
        Node* tempnewnode= new Node();  //create a new node for every unique character in key
        tempnewnode->token.val=frequency;
        tempnewnode->token.symbol=p;
        queue.enque(tempnewnode); //add the new node to queue
    }
    

};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    //TODO
    findFrequency();
    while(queue.head->next!=NULL){
            Node* merged=huffmanTree.mergeNodes(queue.head, queue.head->next); //merge the first two nodes.
            queue.dequeue();
            queue.dequeue(); 
            queue.enque(merged);  
    //delete the first two nodes from queue and add the merged node of them.
    }
    huffmanTree.root=queue.head;

};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    //TODO
    while(traverse != NULL && traverse->right!=NULL && traverse->left!=NULL){
        //if the right child of traverse contains the tokenchar, move to the right and add 1 to tokenbinary value
        if(traverse->right->token.symbol.find(tokenChar)!=std::string::npos){ 
            tokenBinary= tokenBinary + '1'; 
            traverse=traverse ->right;
        }
        else if(traverse->left->token.symbol.find(tokenChar)!=std::string::npos){
        //if the left child of traverse contains the tokenchar, move to the left and add 0 to tokenbinary value
            tokenBinary= tokenBinary + '0';
            traverse= traverse->left;
        }
    }
    return tokenBinary;

};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //TODO
    encodedBinaryPassword="";
    for(std::size_t i=0; i!=password.length(); i++){
        char p= password[i];
        string token_binary="";
        token_binary= getTokenBinary(p,huffmanTree.root, token_binary); //find the binary value of all characters in the password one by one
        encodedBinaryPassword=encodedBinaryPassword + token_binary; //keep binary values of all characters in turn 
        encodedValPassword=encodedValPassword + to_string(token_binary.length()); //keep the length of binaryvalues of all characters in password in turn
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    decodedPassword="";
    std::size_t i=0;
    int j=0;
    while(i< encodedValPassword.length()){
        string p=encodedValPassword.substr(i,1); //take the size of binaryvalues of characters one by one
        int size = std::stoi(p); 
        string temp=encodedBinaryPassword.substr(j,size); //take the binaryvalue of chars according to sizes
        decodeToken(temp); //find the character of each binaryvalue
        j=j+size;        
        i++;
    } 
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //TODO  
    Node* temp=huffmanTree.root;
    for(std::size_t i=0; i< encodedToken.length(); i++){
        if(encodedToken[i]=='0' )
            temp=temp->left;
        else if (encodedToken[i]=='1')
            temp=temp->right;
    } //takes the bits in binaryvalue one by one, if the bit is 0 move to left, if 1 move to right in tree.
    decodedPassword= decodedPassword + temp->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};

