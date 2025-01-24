#include "Media.h"

Media::Media(const std::string& title, MediaState state)
    : m_title(title), m_state(state)
{
}

const std::string& Media::getTitle() const {
    return m_title;
}

bool Media::getBorrowedStatus() const {
    return m_isBorrowed;
}

void Media::borrow() {
    if (m_isBorrowed) {
        throw std::runtime_error("The media is already borrowed.");
    }
    m_isBorrowed = true;
}

void Media::returnMedia() {
    if (!m_isBorrowed) {
        throw std::runtime_error("The media is not currently borrowed.");
    }
    m_isBorrowed = false;
}

MediaState Media::getState() const {
    return m_state;
}
