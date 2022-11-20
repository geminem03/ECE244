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
        s->setNext(nullptr); // at end of list so points to null
    }        
    ShapeNode* ShapeList::remove(string name){
        ShapeNode *removeptr = head;
        ShapeNode *prev = nullptr;
        if(head == nullptr){ // empty list
            return nullptr;
        }
        if(removeptr != nullptr && removeptr->getShape()->getName() == name){
            head = removeptr->getNext();
            return removeptr;
        }
        else{
            while(removeptr != nullptr && removeptr->getShape()->getName() != name){
                prev = removeptr;
                removeptr = removeptr->getNext();
            }
            if(removeptr == nullptr){
                return nullptr;
            }
            prev->setNext(removeptr->getNext());
        }
        return removeptr;
    }     

    void ShapeList:: print() const{
        ShapeNode *p = head;
        while(p != nullptr){
            p->print();
            p = p->getNext();
        }
    }