#ifndef BOOK_H
#define BOOK_H

#include "Media.h"
#include <regex>

class Book : public Media {
public:
    Book(const std::string& title, const std::string& isbn);
    std::string getType() const override;
    std::string getInfo() const override;
    std::string getISBN() const;
    static bool isValidISBN(const std::string& isbn);

private:
    std::string m_isbn;
};

#endif // BOOK_H
