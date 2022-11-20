//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

GroupList* gList;

// Error functions 
void invalidName () { cout << "Error: invalid name" << endl; }
void nameExists (string name) { cout << "Error: " << name << " exists" << endl; }
void shapeNameNotFound (string name) { cout << "Error: shape " << name << " not found" << endl;}
void groupNameNotFound (string name) { cout << "Error: group " << name << " not found" << endl;}

// Helper functions 
bool restrictedWord(string name);
bool shapeExists(string name);
bool groupExists(string name);
ShapeNode* findShape(string name);
GroupNode* findGroup(string name);
GroupNode* findShapeGroup(string name);
//implement trim function


// Global variables 
string name, type;
int xloc, yloc, xsize, ysize;
string shapeName, groupName;


int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";       
    getline(cin, line);   

    while ( !cin.eof () ) {
        stringstream lineStream (line);
        lineStream >> command;
        if(command == keyWordsList[0]) { //create shape
            lineStream >> name;
            if (restrictedWord(name)) goto jmp; // check if the name is one of the restricted words
            if(shapeExists(name) || groupExists(name)){ // check if it's already been used 
                nameExists(name);
                goto jmp;
            }
            lineStream >> type;
            lineStream >> xloc;
            lineStream >> yloc;
            lineStream >> xsize;
            lineStream >> ysize;
            // insert new shape into list 
            Shape* newShape =  new Shape(name, type, xloc, yloc, xsize, ysize);
            ShapeNode* shapePtr = new ShapeNode();
            shapePtr->setShape(newShape);
            shapePtr->getShape()->draw();
            poolGroup->getShapeList()->insert(shapePtr);
        }
        else if(command == keyWordsList[1]){ // create group
            lineStream >> name;
            if(groupExists(name)){ // check if it's already been used 
                nameExists(name);
                goto jmp;
            }
            GroupNode* newGroup = new GroupNode(name);
            gList->insert(newGroup);
            cout << name << ": " << "group" << endl;
        }
        else if(command == keyWordsList[2]){ // transfer to new group 
            lineStream >> shapeName;
            if(shapeName == "pool"){
                invalidName();
                goto jmp;
            }
            if(shapeExists(shapeName)){
                lineStream >> groupName;
                if(groupName == "pool"){
                    invalidName();
                    goto jmp;
                }
                if(groupExists(groupName)){
                    ShapeNode* srcShape = findShape(shapeName);
                    GroupNode* destGroup = findGroup(groupName);
                    GroupNode* srcGroup = findShapeGroup(shapeName);
                    srcGroup->getShapeList()->remove(shapeName);
                    destGroup->getShapeList()->insert(srcShape);


                    cout << "moved " << shapeName << " to " << groupName << endl;

                }
                else if(!groupExists(groupName)){
                    groupNameNotFound(groupName);
                    goto jmp;
                }
            }
            else if(!shapeExists(shapeName)){
                shapeNameNotFound(shapeName);
                goto jmp;
            }
        }
        else if(command == keyWordsList[3]){ // delete shape/group
            lineStream >> name;
            if(name == "pool"){
                invalidName();
                goto jmp;
            }
            if(shapeExists(name)){
                GroupNode* shapelist = findShapeGroup(name);
                ShapeNode* deleteShape = findShape(name);
                if(deleteShape != nullptr){
                    delete shapelist->getShapeList()->remove(name);
                    cout << "deleted: " << name << endl;
                }
                else if(!shapeExists(name)){ 
                    shapeNameNotFound(name);
                    goto jmp;
                }
            }
            else if(groupExists(name)){
                GroupNode* deleteGroup = findGroup(name);
                if(deleteGroup != nullptr){
                    delete gList->remove(name);
                    cout << "deleted: " << name << endl;

                }
                else if (!groupExists(name)){
                    groupNameNotFound(name);
                    goto jmp;
                }
            }
            else if(!shapeExists(name) && !groupExists(name)){
                shapeNameNotFound(name);
                goto jmp;
            }
        }
        else if(command == keyWordsList[4]){ // draw shape/group
            cout << "drawing: " << endl;
            gList->print();
        } 
        else {
            cout << "****** Error: invalid command ******" << endl;
            goto jmp;
        }
        
        // Once the command has been processed, prompt for the
        // next command
        jmp: cout << "> ";    
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    // apply destructors for all levels 
    return 0;
}


bool restrictedWord(string name) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (name == keyWordsList[i]) {
            invalidName();
            return true;
        }
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i]){
            invalidName();
            return true;
        }
    }
    return false;
}
bool shapeExists(string name){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        if(p->getShapeList()->find(name)) return true;
        p = p->getNext();
    }
    return false;
}
bool groupExists(string name){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        if(p->getName() == name) return true;
        p = p->getNext();
    }
    return false;
}
ShapeNode* findShape(string name){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        ShapeList* shapelist = p->getShapeList();
        if(!shapelist) continue;
        ShapeNode* find = shapelist->getHead();
        while(find != nullptr){
            if(find->getShape()->getName() == name) return find;
            find = find->getNext();
        }
    }
    return nullptr;
}
GroupNode* findGroup(string name){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        if(p->getName() == name) return p;
        p = p->getNext();
    }
    return nullptr;
}
GroupNode* findShapeGroup(string name){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        ShapeList* shapelist = p->getShapeList();
        ShapeNode* find = shapelist->getHead();
        while(find != nullptr){
            if(find->getShape()->getName() == name) return p;
            find = find->getNext();
        }
        p = p->getNext();
    }
    return nullptr;
}

/*void removeSource(ShapeNode* s){
    GroupNode* p = gList->getHead();
    while(p != nullptr){
        ShapeList* shapelist = p->getShapeList();
        if(!shapelist) continue;
        ShapeNode* removeSrc = shapelist->getHead();
        ShapeNode* prev = nullptr;
        while(removeSrc != nullptr){
            if(removeSrc->getShape()->getName() != name) {
                prev = removeSrc;
                removeSrc = removeSrc->getNext();
            }
            else if(removeSrc->getShape()->getName() == name){
                prev->setNext(removeSrc->getNext());
            }
        }
    }
}
*/
