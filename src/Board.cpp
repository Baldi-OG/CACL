#include "Board.h"
#include <iostream>
using namespace std;


Board::Board() : filledCells(0) {
    for (auto &i: grid) {
        for (char &j: i) {
            j = ' '; // Initialize all cells to empty
        }
    }
}

void Board::draw() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << grid[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

bool Board::isValidMove(const int row, const int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ';
}

void Board::makeMove(const int row, const int col, const char symbol) {
    if (isValidMove(row, col)) {
        grid[row][col] = symbol;
        filledCells++;
    }
}

bool Board::checkWin(const char symbol) const {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
            (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)) {
            return true;
        }
    }
    // Check diagonals
    return (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
           (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol);
}

bool Board::isFull() const {
    return filledCells == 9;
}

int Board::getFilledCells() const {
    return filledCells;
}