#ifndef MEDIA_FACTORY_H
#define MEDIA_FACTORY_H

#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "Game.h"

class MediaFactory {
public:
    static std::shared_ptr<Media> createMedia(const std::string& type, const std::vector<std::string>& args);
};

#endif // MEDIA_FACTORY_H