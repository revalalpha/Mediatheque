#include "Film.h"

Film::Film(const std::string& title, const std::string& format, int ageLimit)
    : Media(title, MediaState::Available), format(format), ageLimit(ageLimit) {}

std::string Film::getType() const {
    return "Film";
}

bool Film::isValidFormat(const std::string& format) {
    return format == "Bluray" || format == "bluray" || format == "DVD" || format == "dvd";
}

std::string Film::getInfo() const {
    std::ostringstream oss;
    oss << "\nType: Film"
        << "\nTitle: " << m_title << ", Format : " << format
        << "\nAge Limit: " << ageLimit
        << "\nBorrowed: " << (m_isBorrowed ? "Yes" : "No")
        << "\n";
    return oss.str();
}

int Film::getAgeLimit() const {
    return ageLimit;
}