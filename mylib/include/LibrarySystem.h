#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "Game.h"
#include "Client.h"

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class LibrarySystem {
public:
    void addMedia(const std::string& mediaType, const std::vector<std::string>& args);

    void removeMedia(const std::string& mediaType, const std::string& title);

    std::string listMedia() const;

    std::string listMediaByState(bool isBorrowed) const;

    std::string getMediaState(const std::string& mediaType, const std::string& title) const;

    std::string getWhoBorrowedMedia(const std::string& mediaType, const std::string& title) const;

    void rentMedia(const std::string& clientName, const std::string& mediaType, const std::string& title);

    void returnMedia(const std::string& mediaType, const std::string& title);

    std::string showMediaBorrowedByClient(const std::string& clientName) const;

    void addClient(const std::string& name, int age);

    void removeClient(const std::string& name, int age);

    std::string listClients() const;

private:
    std::shared_ptr<Media> findMedia(const std::string& mediaType, const std::string& title) const;

    Client getClient(const std::string& clientName) const;

    std::vector<std::shared_ptr<Media>> mediaCollection; 
    std::unordered_map<Client, std::vector<std::shared_ptr<Media>>, ClientHash> clientMediaMap;
    std::vector<Client> clients;
};

#endif // LIBRARY_SYSTEM_H