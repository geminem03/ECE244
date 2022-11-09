//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"
using namespace std;

    ShapeList::ShapeList() {head = nullptr;}

    ShapeList::~ShapeList() {
	    ShapeNode* p = head;
	    ShapeNode* prev = nullptr;
	    while (p != nullptr) {
		    prev = p->getNext();
		    delete p;
		    p = prev;
	    }
    }         
    
    ShapeNode* ShapeList::getHead() const {return head;}  
      
    void ShapeList::setHead(ShapeNode* ptr) {head = ptr;}
    
    ShapeNode* ShapeList::find(string name) const{
        for(ShapeNode *cur = head; cur != nullptr; cur = cur->getNext()){
            if(cur->getShape()->getName() == name){
                return cur; // if found return pointer to shape
            }
        }
        return nullptr; // if not found return nullptr
    }

    void ShapeList::insert(ShapeNode* s){
        s->setNext(nullptr); // at end of list so points to null
        ShapeNode *p = head;
        if(head == nullptr){
            head = s; // if empty list s is the head
        }
        else{
            while(p->getNext() != nullptr){
                p = p->getNext(); // iterate through list until you reach end
            }
            p->setNext(s); // the next value is now the shape that s points to 
        }
    }        
    ShapeNode* ShapeList::remove(string name){
        ShapeNode *p = head;
        ShapeNode *prev = nullptr;
        if(p == nullptr) return nullptr; // returns nullptr is a node with name does not exist
        if(p != nullptr && p->getShape()->getName() != name){
            prev = p;           // traverse through the list until reach end 
            p = p->getNext();   // or land of the pointer with the matching name 
        }
        if(p == head) {
            head = head->getNext();
            return p; // returns a pointer to the removed node
        }
        else{
            prev->setNext(p->getNext());
            return p; // returns a pointer to the removed node
        }
    }     

    void ShapeList:: print() const{
        ShapeNode *p = head;
        while(p != nullptr){
            p->print();
            p = p->getNext();
        }
    }