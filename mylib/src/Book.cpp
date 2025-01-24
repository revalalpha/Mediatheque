#include "Book.h"
#include <sstream>

Book::Book(const std::string& title, const std::string& isbn)
    : Media(title, MediaState::Available), m_isbn(isbn) {}

std::string Book::getType() const {
    return "Book";
}

std::string Book::getISBN() const
{
    return m_isbn;
}

bool Book::isValidISBN(const std::string& isbn) {
    return std::regex_match(isbn, std::regex("\\d+"));
}

std::string Book::getInfo() const {
    std::ostringstream oss;
    oss << "\nType : Book"
        << "\nTitle : " << m_title
        << "\nISBN : " << m_isbn
        << "\nBorrowed : " << (m_isBorrowed ? "Yes" : "No")
        << "\n";
    return oss.str();
}
