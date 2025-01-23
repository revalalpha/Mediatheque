#include "LibrarySystem.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

void LibrarySystem::addMedia(const std::string& mediaType, const std::vector<std::string>& args) {
    std::shared_ptr<Media> media;

    if (mediaType == "book") {
        if (args.size() != 2) {
            throw std::invalid_argument("Usage: addMedia book <title> <isbn>");
        }
        media = std::make_shared<Book>(args[0], args[1]);
    }
    else if (mediaType == "film") {
        if (args.size() != 3) {
            throw std::invalid_argument("Usage: addMedia film <title> <format> <ageLimit>");
        }
        int ageLimit = std::stoi(args[2]);
        media = std::make_shared<Film>(args[0], args[1], ageLimit);
    }
    else if (mediaType == "game") {
        if (args.size() != 4) {
            throw std::invalid_argument("Usage: addMedia game <title> <studio> <genre> <pegi>");
        }
        int pegi = std::stoi(args[3]);

        media = std::make_shared<Game>(args[0], args[1], args[2], pegi);
    }

    else {
        throw std::invalid_argument("Unsupported media type: " + mediaType);
    }

    mediaCollection.push_back(media);
}

void LibrarySystem::addBookMedia(const std::string& mediaType, const std::string& title, const std::string& ISBN)
{

}

void LibrarySystem::addFilmMedia(const std::string& mediaType, const std::string& title, const std::string& support, const int& ageLimit)
{

}

void LibrarySystem::addGameMedia(const std::string& mediaType, const std::string& title, const std::string& studio, const std::string& PEGI,
    const std::string& genre)
{

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

//std::string LibrarySystem::listMedia() const {
//    std::ostringstream oss;
//    for (const auto& media : mediaCollection) {
//        oss << media->getInfo() << "\n";
//    }
//    return oss.str();
//}

std::string LibrarySystem::listMedia() const {
    std::string result;
    for (const auto& media : mediaCollection) {
        result += media->getInfo() + "\n";
    }
    return result;
}

//std::string LibrarySystem::listMediaByState(bool isBorrowed) const {
//    std::string result;
//    for (const auto& media : mediaCollection) {
//        if (media->getBorrowedStatus() == isBorrowed) {
//            result += media->getTitle() + "\n";
//        }
//    }
//    return result;
//}

std::string LibrarySystem::listMediaByState(const std::string& state) const {
    std::string result;
    MediaState desiredState;

    if (state == "available") {
        desiredState = MediaState::Available;
    }
    else if (state == "borrowed") {
        desiredState = MediaState::Borrowed;
    }
    else {
        return "Invalid state. Please use 'available' or 'borrowed'.";
    }

    for (const auto& mediaPtr : mediaCollection) {
        if (mediaPtr->getState() == desiredState) {
            result += mediaPtr->getTitle() + "\n";
        }
    }

    if (result.empty()) {
        result = "No media found in the requested state.";
    }

    return result;
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

std::string LibrarySystem::showMediaBorrowedByClientWithNameAndFirstName(const std::string& clientName, const std::string& clientFirstName) const {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&clientName, &clientFirstName](const Client& client) {
            return client.getName() == clientName && client.getFirstName() == clientFirstName;
        });

    if (it == clients.end()) {
        return "Client not found.";
    }

    const Client& client = *it;
    std::string result;

    auto mediaIt = clientMediaMap.find(client);
    if (mediaIt != clientMediaMap.end()) {
        for (const auto& media : mediaIt->second) {
            result += media->getTitle() + "\n";
        }
    }
    else {
        result = "No media borrowed by this client.";
    }

    return result;
}

std::string LibrarySystem::showMediaBorrowedByClientWithMail(const std::string& mail) const {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&mail](const Client& client) {
            return client.getMail() == mail;
        });

    if (it == clients.end()) {
        return "Client not found.";
    }

    const Client& client = *it;
    std::string result;

    auto mediaIt = clientMediaMap.find(client);
    if (mediaIt != clientMediaMap.end()) {
        for (const auto& media : mediaIt->second) {
            result += media->getTitle() + "\n";
        }
    }
    else {
        result = "No media borrowed by this client.";
    }

    return result;
}

std::shared_ptr<Media> LibrarySystem::findMedia(const std::string& mediaType, const std::string& title) const {
    for (const auto& media : mediaCollection) {
        if (media->getTitle() == title && media->getType() == mediaType) {
            return media;
        }
    }
    throw std::runtime_error("Media not found.");
}

Client LibrarySystem::getClient(const std::string& clientName) const {
    for (const auto& client : clients) {
        if (client.getName() == clientName) {
            return client; 
        }
    }
    throw std::runtime_error("Client not found.");
}

void LibrarySystem::addClient(const std::string& name, const std::string& firstname, int age, const std::string& address
    , const std::string& phoneNumber, const std::string& mail) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&name, &firstname, age, &address, &phoneNumber, &mail](const Client& client) {
            return client.getName() == name && client.getFirstName() == firstname && client.getAge() == age
                && client.getAddress() == address && client.getPhoneNumber() == phoneNumber && client.getMail() == mail;
        });

    if (it != clients.end()) {
        throw std::runtime_error("Client is already registered.");
    }


    clients.emplace_back(name, firstname, age, address, phoneNumber, mail);
}


void LibrarySystem::removeClientByNameAndFirstName(const std::string& name, const std::string& firstName) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&name, &firstName](const Client& client) {
            return client.getName() == name && client.getFirstName() == firstName;
        });

    if (it == clients.end()) {
        throw std::runtime_error("Client not found.");
    }

    clientMediaMap.erase(*it);
    clients.erase(it);
}

void  LibrarySystem::removeClientByMail(const std::string& mail)
{
    auto it = std::find_if(clients.begin(), clients.end(),
        [&mail](const Client& client) {
            return client.getMail() == mail;
        });

    if (it == clients.end()) {
        throw std::runtime_error("Client not found.");
    }

    clientMediaMap.erase(*it);
    clients.erase(it);
}

std::string LibrarySystem::listClients() const {
    if (clients.empty()) {
        return "No client registered.\n";
    }

    std::ostringstream oss;
    for (const auto& client : clients) {
        oss << "Name : " << client.getName() << ", Age : " << client.getAge() << "\n";
    }
    return oss.str();
}