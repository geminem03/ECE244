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


void playMove(GameState& game_state) {

    int rowMove = game_state.get_selectedRow;
    int colMove = game_state.get_selectedColumn;

    if(get_turn() == 1){
        
    }

    if(game_state.get_gameBoard(rowMove(), colMove()) == 0){ // determine if spot is empty

        game_state.set_moveValid = true; //sets moveValid to true

        //update gameboard at the appropriate location for either X or O depending on value of get_turn()
        game_state.set_gameBoard(rowMove, colMove, game_state.get_turn() /* compare value og get_turn(1 or -1) */);
        game_state.set_turn(/*switch value of turn */);
        // need to print the newly updated gameboard
        
        // output value of validMove
        get_moveValid();

        /* get value of wincode to determine if game over
            wincode if nowhere to move or three in a row*/
        int winCode = game_state.get_winCode
        if(winCode != 0){
            game_state.set_winCode(winCode);
            game_state.set_gameOver(true);
            cout << "winCode: "<< get_winCode() << endl;
        }

        /* output value of gameOver- if winCode is not equal to zero
           end game if gameOver is true*/
        
    }

    // set amd output values for winCode
    
}
