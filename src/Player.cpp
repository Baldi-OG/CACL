#include "Player.h"

#include <string>
#include <utility>

Player::Player(const char symbol, string name) : symbol(symbol), name(std::move(name)) {
}

char Player::getSymbol() const { return symbol; }
string Player::getName() const { return name; }