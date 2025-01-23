#ifndef MEDIA_H
#define MEDIA_H

#include <string>

enum class MediaState {
    Available,
    Borrowed
};

class Media {
public:
    Media(const std::string& title, MediaState state);
    virtual ~Media() = default;

    virtual std::string getType() const = 0;
    const std::string& getTitle() const;
    bool getBorrowedStatus() const;
    void borrow();
    void returnMedia();
    MediaState getState() const;

    virtual std::string getInfo() const = 0;

protected:
    std::string title;
    MediaState state;
    bool isBorrowed;

};

#endif 