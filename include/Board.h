#ifndef CACL_BOARD_H
#define CACL_BOARD_H


class Board {
    char grid[3][3]{};
    int filledCells;

public:
    Board();

    void draw() const;

    bool isValidMove(int row, int col) const;

    void makeMove(int row, int col, char symbol);

    bool checkWin(char symbol) const;

    bool isFull() const;

    int getFilledCells() const;
};


#endif //CACL_BOARD_H