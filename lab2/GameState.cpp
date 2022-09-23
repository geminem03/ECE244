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

class GameState {
private:
    int selectedRow;    // Game board row coordinate selected (in the range 0..boardSize-1)
    int selectedColumn; // Game board column coordinate selected (in the range 0..boardSize-1)
    bool moveValid;     // Is the grid location selected by the above coordinates a valid move?
    bool gameOver;      // Is the game over as a result of the selected row and column?
    int winCode;        // If the game is over, this is the win code (see lab handout)
    bool turn;          // Whose turn is it?
    int gameBoard[boardSize][boardSize]; // The game board
    
public:
    // The constructor. It initializes:
    //     selectedRow to 0
    //     selectedColum to 0
    //     moveValid to true
    //     gameOver to false
    //     winCode to 0
    //     turn to true
    //     gameBoard locations to Empty (see globals.h)
    GameState(){
        selectedRow = 0;
        selectedColumn = 0;
        moveValid = true;
        gameOver = false;
        winCode = 0;
        turn = true;
        gameBoard[boardSize][boardSize] = 0;
    }

    // Return the selected row (in the range 0..boardSize-1)
    int get_selectedRow(int selectedRow){ // check range in set_selectRow
        return selectedRow;
    }     

    // Return the selected column (in the range 0..boardSize-1)
    int get_selectedColumn(int selectedColumn){ // check range in set_selectedCol
        return selectedColumn;
    }  
    
    // Set the selected row to value in the range (in the range 0..boardSize-1)
    // An out of range value is ignored and the function just returns
    void set_selectedRow(int value){
        if((selectedRow >= 0) && (selectedRow < boardSize -1)){
            selectedRow = value;
        }
    }    

    // Set the selected column in the range (in the range 0..boardSize-1)
    // An out of range value is ignored and the function just returns
    void set_selectedColumn(int value){
        if((selectedColumn >= 0) && (selectedColumn < boardSize -1)){
            selectedColumn = value;
        }
    }  
    
    // Get the moveValid value
    bool get_moveValid(){
        return moveValid;
    }

    // Set the moveValid variable to value
    void set_moveValid(bool value){
        moveValid = value;
    }

    // Get the gameOver value
    bool get_gameOver(){
        return gameOver;
    }

    // Set the gameOver variable to value
    void set_gameOver(bool value){
        gameOver = value;
    }

    // Get the winCode [0..8]
    int get_winCode(){
        return winCode;
    }
    
    // Set the winCode to value in the range (0..8)
    // An out of range value is ignored and the function just returns
    void set_winCode(int value){
        if(value >= 0 && value <= 8){
            winCode = value;
        }
    }
    
    // Get the value of turn
    bool get_turn(){
        return turn;
    }

    // Set the value of turn
    void set_turn(bool value){
        turn = value;
    }
    
    // Get the game board value at the board location at row and col
    // This method checks that row, col and value are in range/valid
    // and if not it returns Empty
    int get_gameBoard(int row, int col){
        if((row >= 0) && (row <= boardSize - 1) &&(col >= 0) && (col <= boardSize - 1)){
            return gameBoard[row][col];
        }
    } 

    // Set the game board value at the board location at row and col to value
    // This method checks that row, col and value are in range/valid and if not it
    // just returns
    void set_gameBoard(int row, int col, int value){
        if((row >= 0) && (row <= boardSize - 1) &&(col >= 0) && (col <= boardSize - 1)){
            if(value == 1 || value == -1 || value == 0){
                gameBoard[row][col] = value;
            }
        }
    }
};