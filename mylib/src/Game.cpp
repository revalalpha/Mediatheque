#include "Game.h"

Game::Game(const std::string& title, const std::string& studio, const std::string& genre, int pegi)
    : Media(title, MediaState::Available), m_studio(studio), m_genre(genre), m_pegi(pegi) {}

std::string Game::getType() const {
    return "Game";
}

std::string Game::getInfo() const {
    std::ostringstream oss;
    oss << "\nType: Game"
        << "\nTitle: " << m_title
        << "\nStudio : " << m_studio
        << "\nGenre: " << m_genre << ", PEGI: " << m_pegi
        << "\nBorrowed: " << (m_isBorrowed ? "Yes" : "No")
        << "\n";
    return oss.str();
}

int Game::getPegi() const {
    return m_pegi;
}