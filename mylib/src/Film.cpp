#include "Film.h"
#include <sstream>

Film::Film(const std::string& title, const std::string& format, int ageLimit)
    : Media(title), format(format), ageLimit(ageLimit) {}

std::string Film::getType() const {
    return "Film";
}

std::string Film::getInfo() const {
    std::ostringstream oss;
    oss << "Type: Film, Title: " << title << ", Format: " << format
        << ", Age Limit: " << ageLimit
        << ", Borrowed: " << (isBorrowed ? "Yes" : "No");
    return oss.str();
}

int Film::getAgeLimit() const {
    return ageLimit;
}
