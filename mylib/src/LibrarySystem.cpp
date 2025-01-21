#include "LibrarySystem.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

void LibrarySystem::addMedia(const std::string& mediaType, const std::vector<std::string>& args) {
    if (mediaType == "book") {
        if (args.size() != 2) {
            throw std::invalid_argument("Usage: addMedia book <title> <isbn>");
        }
        mediaCollection.emplace_back(std::make_shared<Book>(args[0], args[1]));
    }
    else if (mediaType == "film") {
        if (args.size() != 3) {
            throw std::invalid_argument("Usage: addMedia film <title> <format> <ageLimit>");
        }
        mediaCollection.emplace_back(std::make_shared<Film>(args[0], args[1], std::stoi(args[2])));
    }
    else if (mediaType == "game") {
        if (args.size() != 4) {
            throw std::invalid_argument("Usage: addMedia game <title> <studio> <pegi> <genre>");
        }
        mediaCollection.emplace_back(std::make_shared<Game>(args[0], args[1], args[3], std::stoi(args[2])));
    }
    else {
        throw std::invalid_argument("Unsupported media type: " + mediaType);
    }
}

void LibrarySystem::removeMedia(const std::string& mediaType, const std::string& title) {
    auto it = std::remove_if(mediaCollection.begin(), mediaCollection.end(),
        [&mediaType, &title](const std::shared_ptr<Media>& media) {
            return media->getType() == mediaType && media->getTitle() == title;
        });
    if (it == mediaCollection.end()) {
        throw std::runtime_error("Media not found: " + title);
    }
    mediaCollection.erase(it, mediaCollection.end());
}

std::string LibrarySystem::listMedia() const {
    std::ostringstream oss;
    for (const auto& media : mediaCollection) {
        oss << media->getInfo() << "\n";
    }
    return oss.str();
}

std::string LibrarySystem::listMediaByState(bool isBorrowed) const {
    std::ostringstream oss;
    for (const auto& media : mediaCollection) {
        if (media->getBorrowedStatus() == isBorrowed) {
            oss << media->getInfo() << "\n";
        }
    }
    return oss.str();
}

std::string LibrarySystem::getMediaState(const std::string& mediaType, const std::string& title) const {
    for (const auto& media : mediaCollection) {
        if (media->getType() == mediaType && media->getTitle() == title) {
            return media->getBorrowedStatus() ? "Borrowed" : "Available";
        }
    }
    throw std::runtime_error("Media not found: " + title);
}

std::string LibrarySystem::getWhoBorrowedMedia(const std::string& mediaType, const std::string& title) const {
    for (const auto& [client, borrowedMedias] : clientMediaMap) {
        for (const auto& media : borrowedMedias) {
            if (media->getType() == mediaType && media->getTitle() == title) {
                return client.getName();
            }
        }
    }
    throw std::runtime_error("Media not borrowed: " + title);
}

void LibrarySystem::rentMedia(const std::string& clientName, const std::string& mediaType, const std::string& title) {
    auto client = getClient(clientName);
    auto media = findMedia(mediaType, title);

    if (media->getBorrowedStatus()) {
        throw std::runtime_error("Media already borrowed: " + title);
    }
    if (media->getType() == "film") {
        auto film = std::dynamic_pointer_cast<Film>(media);
        if (client.getAge() < film->getAgeLimit()) {
            throw std::runtime_error("Client does not meet age limit for this film.");
        }
    }
    if (clientMediaMap[client].size() >= 5) {
        throw std::runtime_error("Client has already borrowed the maximum number of items.");
    }

    media->borrow();
    clientMediaMap[client].push_back(media);
}

void LibrarySystem::returnMedia(const std::string& mediaType, const std::string& title) {
    for (auto& [client, borrowedMedias] : clientMediaMap) {
        auto it = std::find_if(borrowedMedias.begin(), borrowedMedias.end(),
            [&mediaType, &title](const std::shared_ptr<Media>& media) {
                return media->getType() == mediaType && media->getTitle() == title;
            });
        if (it != borrowedMedias.end()) {
            (*it)->returnMedia();
            borrowedMedias.erase(it);
            return;
        }
    }
    throw std::runtime_error("Media not borrowed: " + title);
}

std::string LibrarySystem::showMediaBorrowedByClient(const std::string& clientName) const {
    auto client = getClient(clientName);
    std::ostringstream oss;

    for (const auto& media : clientMediaMap.at(client)) {
        oss << media->getInfo() << "\n";
    }

    return oss.str();
}
