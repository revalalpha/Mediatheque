#ifndef GAME_H
#define GAME_H

#include "Media.h"
#include <sstream>

class Game : public Media {
public:
    Game(const std::string& title, const std::string& studio, const std::string& genre, int pegi);
    std::string getType() const override;
    std::string getInfo() const override;
    int getPegi() const;

private:
    std::string m_studio;
    std::string m_genre;
    int m_pegi;
};

#endif