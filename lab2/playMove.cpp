//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file


#include "globals.h"
#include "GameState.h"
#include <cstdio>
#include <fstream>

// declare function for values of winCode
//int value_winCode(GameState /*what else goes here?*/);

int value_winCode(GameState); //declaration of value_winCode function


void playMove(GameState &game_state) {

    int rowMove = game_state.get_selectedRow();
    int colMove = game_state.get_selectedColumn();

    if(game_state.get_gameBoard(rowMove, colMove) == 0){ // determine if spot is empty

        game_state.set_moveValid(true); //sets moveValid to true if conditions met 

        //update gameboard at the appropriate location for either X or O depending on value of get_turn()
        game_state.set_gameBoard(rowMove, colMove, game_state.get_turn() ? 1 : -1 ); // get_turn = 1 if true and -1 if false
        game_state.set_turn(!game_state.get_turn()); // switches the value of turn to the opposite of what was just played

        // get value of wincode to determine if game over
        int winCode = value_winCode(game_state);
        if(winCode != 0){
            game_state.set_winCode(winCode);
            game_state.set_gameOver(true);
        }
        //set conditions for cats game
    }
    
}

int value_winCode(GameState game_state){
    // variables for top row
    int r0_c0 = game_state.get_gameBoard(0,0);
    int r0_c1 = game_state.get_gameBoard(0, 1);
    int r0_c2 = game_state.get_gameBoard(0,2);

    //variables for middle row
    int r1_c0 = game_state.get_gameBoard(1, 0);
    int r1_c1 = game_state.get_gameBoard(1, 1);
    int r1_c2 = game_state.get_gameBoard(1, 2);

    // variables for bottom row
    int r2_c0 = game_state.get_gameBoard(2, 0);
    int r2_c1 = game_state.get_gameBoard(2, 1);
    int r2_c2 = game_state.get_gameBoard(2, 2);

    // conditions for winCode 1:
    if((r0_c0 != 0) && (r0_c0 == r0_c1) && (r0_c0 == r0_c2)){
        return 1;
    }
    // conditions for winCode 2:
    else if((r1_c0 != 0) && (r1_c0 == r1_c1) && (r1_c0 == r1_c2)){
        return 2;
    }
    // conditions for winCode 3:
    else if((r2_c0 != 0) && (r2_c0 == r2_c1) && (r2_c0 == r2_c2)){
        return 3;
    }
    // conditions for winCode 4:
    else if((r0_c0 != 0) && (r0_c0 == r1_c0) && (r0_c0 == r2_c0)){
        return 4;
    }
    // conditions for winCode 5:
    else if((r0_c1 != 0) && (r0_c1 == r1_c1) && (r0_c1 == r2_c1)){
        return 5;
    }
    // conditions for winCode 6:
    else if((r0_c2 != 0) && (r0_c2 == r1_c2) && (r0_c2 == r2_c2)){
        return 6;
    }
    // conditions for winCode 7:
    else if((r0_c0 != 0) && (r0_c0 == r1_c1) && (r0_c0 == r2_c2)){
        return 7;
    }
    // conditions for winCode 8:
    else if((r2_c0 != 0) && (r2_c0 == r1_c1) && (r2_c0 == r0_c2)){
        return 8;
    }
    // if none of the conditions met, game still going so winCode = 0
    else{
        return 0;
    }
}
