//
// Created by Baldi on 2/26/26.
//

#include "TicTacToe.h"
#include "Player.h"

#include <iostream>
using namespace std;

TicTacToe::TicTacToe() : players{
                             Player('X', "Player 1"),
                             Player('O', "Player 2")
                         },
                         currentPlayerIdx(0) {
}

Player &TicTacToe::getCurrentPlayer() {
    return players[currentPlayerIdx];
}

void TicTacToe::switchTurn() {
    currentPlayerIdx = (currentPlayerIdx + 1) % 2;
}

void TicTacToe::play() {
    int row, col;
    cout << "Welcome !!! To the gaaameee of TIC TAC TOEEE" << endl;

    while (!board.isFull()) {
        board.draw();

        Player &currentPlayer = getCurrentPlayer();

        // Get valid input
        while (true) {
            cout << currentPlayer.getName() << " (" << currentPlayer.getSymbol() <<
                    "), enter row (1-3) and column (1-3): ";
            if (!(cin >> row >> col)) {
                cout << "Invalid input! Try again." << endl;
                cin.clear();
                cin.ignore();
            }
            row--;
            col--; // Convert to 0-indexed

            if (board.isValidMove(row, col)) {
                break;
            }
            cout << "Invalid move! Try again." << endl;
        }

        board.makeMove(row, col, currentPlayer.getSymbol());

        if (board.checkWin(currentPlayer.getSymbol())) {
            board.draw();
            cout << currentPlayer.getName() << " wins!" << endl;
            return;
        }

        // No win, so the game continues
        switchTurn();
    }

    // Game ended in a draw
    board.draw();
    cout << "It's a draw!" << endl;
}