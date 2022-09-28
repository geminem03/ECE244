//
//  GameState.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "globals.h"
#include "GameState.h"

// ECE244 Student: add you code below


// Return the selected row (in the range 0..boardSize-1)
    int get_selectedRow();     

    // Return the selected column (in the range 0..boardSize-1)
    int get_selectedColumn();  
    
    // Set the selected row to value in the range (in the range 0..boardSize-1)
    // An out of range value is ignored and the function just returns
    void set_selectedRow(int value);     

    // Set the selected column in the range (in the range 0..boardSize-1)
    // An out of range value is ignored and the function just returns
    void set_selectedColumn(int value);  
    
    // Get the moveValid value
    bool get_moveValid();

    // Set the moveValid variable to value
    void set_moveValid(bool value);

    // Get the gameOver value
    bool get_gameOver();

    // Set the gameOver variable to value
    void set_gameOver(bool value);

    // Get the winCode [0..8]
    int get_winCode();
    
    // Set the winCode to value in the range (0..8)
    // An out of range value is ignored and the function just returns
    void set_winCode(int value);
    
    // Get the value of turn
    bool get_turn();

    // Set the value of turn
    void set_turn(bool value);
    
    // Get the game board value at the board location at row and col
    // This method checks that row, col and value are in range/valid
    // and if not it returns Empty
    int get_gameBoard(int row, int col); 

    // Set the game board value at the board location at row and col to value
    // This method checks that row, col and value are in range/valid and if not it
    // just returns
    void set_gameBoard(int row, int col, int value);