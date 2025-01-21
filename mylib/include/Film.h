#ifndef FILM_H
#define FILM_H

#include "Media.h"

class Film : public Media {
public:
    Film(const std::string& title, const std::string& format, int ageLimit);
    std::string getType() const override;
    std::string getInfo() const override;
    int getAgeLimit() const;

private:
    std::string format;
    int ageLimit;

};

#endif
