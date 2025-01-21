#ifndef MEDIA_H
#define MEDIA_H

#include <string>

class Media {
public:
    Media(const std::string& title);
    virtual ~Media() = default;

    virtual std::string getType() const = 0;
    const std::string& getTitle() const;
    bool getBorrowedStatus() const;
    void borrow();
    void returnMedia();

    virtual std::string getInfo() const = 0;

protected:
    std::string title;
    bool isBorrowed;

};

#endif 