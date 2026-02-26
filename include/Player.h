#ifndef CACL_PLAYER_H
#define CACL_PLAYER_H

#include <string>
using namespace std;


class Player {
    char symbol;
    string name;

public:
    Player(char symbol, string name);

    char getSymbol() const;

    string getName() const;
};


#endif //CACL_PLAYER_H