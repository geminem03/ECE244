//
// ____2022-10-25 1:22PM____
//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;
int shapeCount = 0;
int max_shapes = 0;
bool live_database = false;

//constants
int num_keywords = 7;
int num_shapeTypes = 4;
string name, type;
int x_location, y_location, x_size, y_size, angle;
bool nameExists = true;


/* Commands
void database(Shape** database, stringstream &line);
void create(Shape** database, stringstream &line);
void move(Shape** database, stringstream &line);
void rotate(Shape** database, stringstream &line);
void draw(Shape** database, stringstream &line);
void deleteShape(Shape** database, stringstream &line); */

// call error functions to output error message
void invalidCommand () { cout << "Error: invalid command" << endl; }
void invalidArgument () { cout << "Error: invalid argument" << endl; }
void invalidShapeName () { cout << "Error: invalid shape name" << endl; }
void shapeNameExists (string name) { cout << "Error: shape " << name << " exists" << endl; }
void shapeNameNotFound (string name) { cout << "Error: shape " << name << " not found" << endl;}
void invalidShapeType () { cout << "Error: invalid shape type" << endl; }
void invalidValue () { cout << "Error: invalid value" << endl; }
void tooManyArguments () { cout << "Error: too many arguments" << endl; }
void tooFewArguments () { cout << "Error: too few arguments" << endl; }
void shapeArrayIsFull () { cout << "Error: shape array is full" << endl; }

// Helper functions
void drawAll();
void deleteAll(); 
void deleteOne(string name);
bool invalidType(string type);
bool restrictedWord(string name);
bool fewArgs(stringstream &line);
bool invalidArg(stringstream &line);
bool manyArgs(stringstream &line);

// can only have one database at a time 
// if a new one is called, delete all the shapes and delete the database
// eof command when deleteOne is called

int main(){

    string line;
    string command;
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input


    while ( !cin.eof () ) {

        stringstream lineStream (line);
        lineStream >> command;

            if(command == keyWordsList[1]){
                if (live_database == true){
                lineStream >> max_shapes;
                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr){
                        delete shapesArray[i];
                        shapesArray[i] = nullptr;
                        shapeCount --;
                    }
                }
                if(shapesArray != nullptr){
                    delete [] shapesArray;
                    shapesArray = nullptr;
                    shapeCount = 0;
                } 
                shapesArray = new Shape*[max_shapes];
                for(int i = 0; i < max_shapes; i++){
                    shapesArray[i] = nullptr; 
                }
                cout << "New database: max shapes is " << max_shapes << endl; 
                }
                else{
                    lineStream >> max_shapes;
                    shapesArray = new Shape*[max_shapes];
                    for(int i = 0; i < max_shapes; i++){
                        shapesArray[i] = nullptr;
                    }
                    cout << "New database: max shapes is " << max_shapes << endl; 
                    live_database = true; 
                }
            } 
            else if(command == keyWordsList[2]){
                lineStream >> name;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                if(fewArgs(lineStream)) break;
                // error check validity of name
                if(restrictedWord(name)) break;
                //name exists
                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                        shapeNameExists(name);
                        nameExists = true;
                        break;
                    }
                }
                
                lineStream >> type; 
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                // error check validity of type
                if(invalidType(type)) break;
                // error check too few arugments
                if(fewArgs(lineStream)) break;

                lineStream >> x_location;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                // error check x position
                if(x_location < 0){
                    invalidValue();
                    break;
                }
                if(fewArgs(lineStream)) break;

                lineStream >> y_location;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                // error check y location
                if(y_location < 0){
                    invalidValue();
                    break;
                }
                if(fewArgs(lineStream)) break;

                lineStream >> x_size;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                // error check x size
                if(x_size < 0){
                    invalidValue();
                    break;
                }
                if(fewArgs(lineStream)) break;

                lineStream >> y_size;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                // error check y size
                if(y_size < 0){
                    invalidValue();
                    break;
                }
                if(fewArgs(lineStream)) break;
                // check for leftover input args
                if(manyArgs(lineStream)) break;

                if(type == "circle" && x_size != y_size){
                    invalidValue();
                }

                // check that there is space in database
                if(shapeCount == max_shapes){
                    shapeArrayIsFull();
                    break;
                }

                if (shapesArray[shapeCount] == nullptr){
                    shapesArray[shapeCount] = new Shape(name, type, x_location, y_location, x_size, y_size);
                    shapeCount++;
                    cout << "Created " << name << ": " << type << " " << x_location;
                    cout << " " << y_location << " " << x_size << " " << y_size << endl;
                }
            }
            else if(command == keyWordsList[3]){
                lineStream >> name;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                if(fewArgs(lineStream)) break;
                // error check validity of name
                if(restrictedWord(name)) break;
                //name exists
                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                        nameExists = true;
                        break;
                    }
                }
                if(nameExists == false){
                    shapeNameNotFound(name);
                }

                lineStream >> x_location;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                if(fewArgs(lineStream)) break;
                // error check x position
                if(x_location < 0){
                    invalidValue();
                    break;
                }

                lineStream >> y_location;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                if(fewArgs(lineStream)) break;
                // error check y location
                if(y_location < 0){
                    invalidValue();
                    break;
                }
    
                // error check few arugments
                if(fewArgs(lineStream)) break;
                if(manyArgs(lineStream)) break;


                for(int j = 0; j < shapeCount; j++){
                    if ((shapesArray[j]->getName() == name) && (shapesArray[j] != NULL)){
                        shapesArray[j]->setXlocation(x_location);
                        shapesArray[j]->setYlocation(y_location);
                        cout << "Moved " << name << " to " << x_location << ' ' << y_location << endl;
                        break;
                    }
                }
                if(nameExists == false){
                    shapeNameNotFound(name);
                }
            }
            else if(command == keyWordsList[4]){
                lineStream >> name;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;
                if(fewArgs(lineStream)) break;
                // error check validity of name
                if(restrictedWord(name)) break;
                //name exists
                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                        nameExists = true;
                        break;
                    }
                }
                if(nameExists == false){
                    shapeNameNotFound(name);
                }

                lineStream >> angle;
                // error check validity of arugment
                if(invalidArg(lineStream)) break;;
                // valid roation value
                if(angle < 0 || angle > 360){
                    invalidValue();
                    break;
                }
                if(fewArgs(lineStream)) break;

                // valid num args total 
               if(manyArgs(lineStream)) break;

                for(int j = 0; j < shapeCount; j++){
                    if ((shapesArray[j]->getName() == name) && (shapesArray[j] != NULL)){
                        shapesArray[j]->setRotate(angle);
                        cout << "Rotated " << name << " by " << angle << " degrees" << endl;
                        break;
                    }
                }
                if(nameExists == false){
                    shapeNameNotFound(name);
                }
            }
            else if(command == keyWordsList[5]){
                if(name == keyWordsList[0]){
                    if(fewArgs(lineStream)) break;
                    if(manyArgs(lineStream)) break;
                    else{
                        cout << "Drew all shapes" << endl;
                        for(int i = 0; i < shapeCount; i++){
                            if(shapesArray[i] != nullptr){
                                shapesArray[i]->draw();
                            }
                        }
                    }
                    break;
                }
                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                        nameExists = true;
                        break;
                    }
                }
                if(nameExists == false){
                    if(fewArgs(lineStream)) break;
                    else{ 
                        shapeNameNotFound(name);
                        break;
                    }
                }
    
                for(int j = 0; j < shapeCount; j++){
                    if(fewArgs(lineStream)) break;
                    if(manyArgs(lineStream)) break;
                    else{ 
                        if (name == shapesArray[j]->getName() && shapesArray[j] != nullptr){
                            cout << "Drew ";
                            shapesArray[j]->draw();
                            break;
                        }
                    }
                }
            }
            else if(command == keyWordsList[6]){
                if (name == keyWordsList[0]){ // delete all
                    if(fewArgs(lineStream)) break;
                    if(manyArgs(lineStream)) break;
                    else{
                        cout << "Deleted: all shapes" << endl; 
                        for(int j = 0; j < shapeCount; j++){
                            if(shapesArray[j] != nullptr){
                                delete shapesArray[j];
                                shapesArray[j] = nullptr;
                            }
                        }
                    }
                    break;
                }
                for(int j = 0; j < shapeCount; j++){
                    if(fewArgs(lineStream)) break;
                    if(manyArgs(lineStream)) break;
                    else{ 
                        if (name == shapesArray[j]->getName() && shapesArray[j] != nullptr){
                            cout << "Drew ";
                            shapesArray[j]->draw();
                            break;
                        }
                    }
                }

                for(int i = 0; i < shapeCount; i++){
                    if(shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                        nameExists = true;
                        break;
                    }
                }
                if(nameExists == true){
                    if(fewArgs(lineStream)) break;
                    if(manyArgs(lineStream)) break;
                    else{
                        cout << "Deleted shape " << name << endl;
                        for (int j = 0; j < shapeCount; j++) {
                            if ((shapesArray[j]->getName() == name) && (shapesArray[j] != nullptr)) {
                                delete shapesArray[j];
                                shapesArray[j] = NULL;
                                break;
                            }
                        }
                    }
                }
            }
            else{
                invalidCommand();
            }
            cout << "> ";       
            getline(cin, line);
    }  // End input loop until EOF.

    // delete memory for the array  
    for(int i = 0; i < max_shapes; i++){
        delete shapesArray[i];
        shapesArray[i] = NULL;
    }
    delete [] shapesArray;
    shapesArray = NULL;
    
    return 0;

}

bool invalidType(string type){
    for(int i = 0; i < num_shapeTypes; i++){
        if(type == shapeTypesList[i]){
            return false;
        }
    }
    invalidShapeType();
    return true;
}

bool restrictedWord(string name){
    // checks if name is one of the shape types
    for(int i = 0; i < num_shapeTypes; i++){
        if(name == shapeTypesList[i]){
            invalidShapeName();
            return true;
        }
    }
    // checks if name is one of the restricted keywords
    for(int i = 0; i < num_keywords; i++){
        if(name == keyWordsList[i]){
            invalidShapeName();
            return true;
        }
    }
    return false;
}

bool fewArgs (stringstream &line){
    if (line.fail() && line.eof()){
        tooFewArguments();
        return true;
    }
    return false;
}
bool invalidArg (stringstream &line){
    if(line.fail() && !line.eof()){
        invalidArgument();
        return true;
    }
    return false;
}

bool manyArgs(stringstream &line){
    string extra;
    line >> extra;

    if(!line.fail()){
        tooManyArguments();
        return true;
    }
    return false;
}
