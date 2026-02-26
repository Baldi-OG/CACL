#include "Player.h"

#include <string>
#include <utility>

Player::Player(const char symbol, std::string name) : symbol(symbol), name(std::move(name)) {
}

char Player::getSymbol() const { return symbol; }
std::string Player::getName() const { return name; }