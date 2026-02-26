#ifndef CACL_PLAYER_H
#define CACL_PLAYER_H

#include <string>

class Player {
    char symbol;
    std::string name;

public:
    Player(char symbol, std::string name);

    char getSymbol() const;

    std::string getName() const;
};


#endif //CACL_PLAYER_H