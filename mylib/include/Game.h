#ifndef GAME_H
#define GAME_H

#include "Media.h"

class Game : public Media {
public:
    Game(const std::string& title, const std::string& studio, const std::string& genre, int pegi);
    std::string getType() const override;
    std::string getInfo() const override;
    int getPegi() const;

private:
    std::string studio;
    std::string genre;
    int pegi;
};

#endif
