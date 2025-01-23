#include "Media.h"
#include <stdexcept>

Media::Media(const std::string& title, MediaState state)
    : title(title), state(state) {}

const std::string& Media::getTitle() const {
    return title;
}

bool Media::getBorrowedStatus() const {
    return isBorrowed;
}

void Media::borrow() {
    if (isBorrowed) {
        throw std::runtime_error("The media is already borrowed.");
    }
    isBorrowed = true;
}

void Media::returnMedia() {
    if (!isBorrowed) {
        throw std::runtime_error("The media is not currently borrowed.");
    }
    isBorrowed = false;
}

MediaState Media::getState() const {
    return state;
}
