#include "Book.h"
#include <sstream>

Book::Book(const std::string& title, const std::string& isbn)
    : Media(title, MediaState::Available), isbn(isbn) {}

std::string Book::getType() const {
    return "Book";
}

std::string Book::getInfo() const {
    std::ostringstream oss;
    oss << "Type: Book, Title: " << title << ", ISBN: " << isbn
        << ", Borrowed: " << (isBorrowed ? "Yes" : "No");
    return oss.str();
}
