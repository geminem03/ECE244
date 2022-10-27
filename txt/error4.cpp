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


// Commands
void create(Shape** shapesArray, stringstream &line);
void move(Shape** shapesArray, stringstream &line);
void rotate(Shape** shapesArray, stringstream &line);
void draw(Shape** shapesArray, stringstream &line);
void deleteShape(Shape** shapesArray, stringstream &line); 

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
int index(string name);
void drawAll();
void deleteAll(); 
void deleteOne(string name);
bool invalidType(string type);
bool nameExists(string name);
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
                if(live_database){
                    for(int i = 0; i < max_shapes; i++)
                    {
                        delete shapesArray[i];
                        shapesArray[i] = NULL;
                    }
                    delete [] shapesArray;
                    shapesArray = NULL;
                    shapeCount = 0;
                }
                //dynamically allocates array of pointers to Shapes
                lineStream >> max_shapes;
                shapesArray = new Shape*[max_shapes];
                for(int i = 0; i < max_shapes; i++){
                    shapesArray[i] = NULL;
                    live_database = true;
                }
                // prints out success message for new database
                cout << "New database: max shapes is " << max_shapes << endl;  
            } 
            else if(command == keyWordsList[2]){
                create(shapesArray, lineStream);
            }
            else if(command == keyWordsList[3]){
                move(shapesArray, lineStream);
            }
            else if(command == keyWordsList[4]){
                rotate(shapesArray, lineStream);
            }
            else if(command == keyWordsList[5]){
                draw(shapesArray, lineStream);
            }
            else if(command == keyWordsList[6]){
                deleteShape(shapesArray, lineStream);
            }
            else{
                invalidCommand();
            }

        cout << "> ";          // Prompt for next input
        getline(cin, line);
        
    }  // End input loop until EOF.

    // delete memory for the array  
    for(int i = 0; i < max_shapes; i++)
    {
        delete shapesArray[i];
        shapesArray[i] = NULL;
    }
    delete [] shapesArray;
    shapesArray = NULL;
    
    return 0;
}

void create(Shape** shapesArray, stringstream &line){
    // import member variables from Shape class
    string name, type;
    int x_location, y_location, x_size, y_size;

    line >> name;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check validity of name
    if(restrictedWord(name)) return;
    if(nameExists(name)){
        shapeNameExists(name);
        return;
    }
    // error check few arugments

    line >> type; 
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check validity of type
    if(invalidType(type)) return;
    // error check too few arugments
    // error check against invalid size for circle 

    line >> x_location;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check x position
    if(x_location < 0){
        invalidValue();
        return;
    }
    // error check few arugments

    line >> y_location;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check y location
    if(y_location < 0){
        invalidValue();
        return;
    }
    // error check validity few arugments

    line >> x_size;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check x size
    if(x_size < 0){
        invalidValue();
        return;
    }
    // error check few arugments

    line >> y_size;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check y size
    if(y_size < 0){
        invalidValue();
        return;
    }
    // check for leftover input args
    if(manyArgs(line)) return;

    if(type == "circle" && x_size != y_size){
        invalidValue();
        return;
    }


    // check that there is space in database
    if(shapeCount == max_shapes){
        shapeArrayIsFull();
        return;
    }

    for(int j = 0; j < max_shapes; j++){
        if (shapesArray[j] == NULL){
            shapesArray[j] = new Shape(name, type, x_location, y_location, x_size, y_size);
            shapeCount++;
            cout << "Created " << name << ": " << type << " " << x_location;
            cout << " " << y_location << " " << x_size << " " << y_size << endl;
            break;
        }
    }
}

void draw(Shape** shapesArray, stringstream &line){
    string shape_name;
    line >> shape_name; // check if draw command is for one shape or all

    if(shape_name == keyWordsList[0]){
        if(fewArgs(line)) return;
        if(manyArgs(line)) return;
        else{
            cout << "Drew all shapes" << endl;
            for(int i = 0; i < shapeCount; i++){
                if(shapesArray[i] != nullptr){
                    shapesArray[i]->draw();
                }
            }
        }
        return;
    }
    if(!nameExists(shape_name)){
        if(fewArgs(line)) return;
        else{ 
            shapeNameNotFound(shape_name);
            return;
        }
    }
    
    for(int j = 0; j < shapeCount; j++){
        if(fewArgs(line)) return;
        if(manyArgs(line)) return;
        else{ 
            if (shape_name == shapesArray[j]->getName() && shapesArray[j] != NULL){
                cout << "Drew ";
                shapesArray[j]->draw();
                break;
            }
        }
    }
}




void deleteShape(Shape** shapesArray, stringstream &line){
    string shape_name;
    line >> shape_name;

    if (shape_name == keyWordsList[0]){ // delete all
        if(fewArgs(line)) return;
        if(manyArgs(line)) return;
        else{
            cout << "Deleted: all shapes" << endl; 
            for(int j = 0; j < shapeCount; j++){
                if(shapesArray[j] != NULL){
                    delete shapesArray[j];
                    shapesArray[j] = NULL;
                }
            }
        // ---------delete entire database?-----------
        }
        return;
    }
    if(!nameExists(shape_name)){
        if(fewArgs(line)) return;
        else{
            shapeNameNotFound(shape_name);
            return;
        }
    }
    if(nameExists(shape_name)){
        if(fewArgs(line)) return;
        if(manyArgs(line)) return;
        else{
            cout << "Deleted shape " << shape_name << endl;
            for (int j = 0; j < shapeCount; j++) {
                if ((shapesArray[j]->getName() == shape_name) && (shapesArray[j] != NULL)) {
                    delete shapesArray[j];
                    shapesArray[j] = NULL;
                    return;
                }
            }
        }
    }
}

void move(Shape** shapesArray, stringstream &line){
    string name;
    int x_location, y_location;

    line >> name;
    // error check validity and number of arugments
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;
    // error check validity of name
    if(!nameExists(name)){
        shapeNameNotFound(name);
        return;
    }

    line >> x_location;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(x_location < 0){
        invalidValue();
        return;
    }
    // error check few arugments
    if(fewArgs(line)) return;

    line >> y_location;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(y_location < 0){
        invalidValue();
        return;
    }
    // error check few arugments
    if(fewArgs(line)) return;
    if(manyArgs(line)) return;


    for(int j = 0; j < shapeCount; j++)
    {
        if ((shapesArray[j]->getName() == name) && (shapesArray[j] != NULL))
        {
            shapesArray[j]->setXlocation(x_location);
            shapesArray[j]->setYlocation(y_location);
            cout << "Moved " << name << " to " << x_location << ' ' << y_location << endl;
            break;
        }
        if(!nameExists(name)){
            shapeNameNotFound(name);
            return;
        }
    }

}

void rotate(Shape** shapesArray, stringstream &line){
    string name;
    int angle;

    line >> name;
    // error check validity of arugment
    if(invalidArg(line)) return;
    if(fewArgs(line)) return;

    if(restrictedWord(name)) return;
    if(!nameExists(name)){
        shapeNameNotFound(name);
        return;
    }

    line >> angle;
     // error check validity of arugment
    if(invalidArg(line)) return;
    // valid roation value
    if(angle < 0 || angle > 360){
        invalidValue();
        return;
    }
    if(fewArgs(line)) return;

    // valid num args total 
    if(manyArgs(line)) return;

    for(int j = 0; j < shapeCount; j++)
    {
        if ((shapesArray[j]->getName() == name) && (shapesArray[j] != NULL))
        {
            shapesArray[j]->setRotate(angle);
            cout << "Rotated " << name << " by " << angle << " degrees" << endl;
            break;
        }
        if(!nameExists(name)){
            shapeNameNotFound(name);
            return;
        }
    }
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

bool nameExists(string name){
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i]->getName() == name){
            return true;
        }
    }
    return false;
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
