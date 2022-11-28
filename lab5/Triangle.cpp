//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Triangle here

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

    Triangle::Triangle(string n, float xcent, float ycent, float _x1, float _y1, float _x2, float _y2, float _x3, float _y3) : Shape(n, xcent, ycent){
        x1 = _x1;
        x2 = _x2;
        x3 = _x3;
        y1 = _y1;
        y2 = _y2;
        y3 = _y3;
    }
    Triangle::~Triangle(){
        //Do nothing
    }

    float Triangle::getX1() const { return x1; }
    float Triangle::getY1() const { return y1; }
    float Triangle::getX2() const { return x2; }
    float Triangle::getY2() const { return y2; }
    float Triangle::getX3() const { return x3; }
    float Triangle::getY3() const { return y3; }


    void Triangle::setX1(float _x1) { x1 = _x1; }
    void Triangle::setY1(float _y1) { y1 = _y1; }
    void Triangle::setX2(float _x2) { x1 = _x2; }
    void Triangle::setY2(float _y2) { y1 = _y2; }
    void Triangle::setX3(float _x3) { x1 = _x3; }
    void Triangle::setY3(float _y3) { y1 = _y3; }

    void Triangle::draw() const{
        //set precision of decimnals 
        cout << std::fixed;
        cout << std::setprecision(2);

        // Print the information
        cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " 
         << x2 << " " << y2 << " " 
         << x3 << " " << y3 << " "<< computeArea()
         << endl;
    }
    float Triangle::computeArea() const{
        return abs(0.5*(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)));
    }                    
    Shape* Triangle::clone() const{
        return (new Triangle(*this)); 
    }

