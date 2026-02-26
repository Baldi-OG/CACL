#ifndef CACL_TICTACTOE_H
#define CACL_TICTACTOE_H

#include "Board.h"
#include "Player.h"


class TicTacToe {
    Board board;
    Player players[2];
    int currentPlayerIdx;

public:
    TicTacToe();

    Player &getCurrentPlayer();

    void switchTurn();

    void play();
};


#endif //CACL_TICTACTOE_H