#ifndef BOOK_H
#define BOOK_H

#include "Media.h"

class Book : public Media {
public:
    Book(const std::string& title, const std::string& isbn);
    std::string getType() const override;
    std::string getInfo() const override;

private:
    std::string isbn;
};

#endif // BOOK_H
