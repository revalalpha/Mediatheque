#include "Game.h"
#include <sstream>

Game::Game(const std::string& title, const std::string& studio, const std::string& genre, int pegi)
    : Media(title, MediaState::Available), studio(studio), genre(genre), pegi(pegi) {}

std::string Game::getType() const {
    return "Game";
}

std::string Game::getInfo() const {
    std::ostringstream oss;
    oss << "Type: Game, Title: " << title << ", Studio: " << studio
        << ", Genre: " << genre << ", PEGI: " << pegi
        << ", Borrowed: " << (isBorrowed ? "Yes" : "No");
    return oss.str();
}

int Game::getPegi() const {
    return pegi;
}
