#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Media.h"
#include "Client.h"
#include "MediaFactory.h"

#include <algorithm>
#include <sstream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <regex>

class LibrarySystem {
public:
    void addMedia(const std::string& mediaType, const std::vector<std::string>& args);
    void addBookMedia(const std::string& title, const std::string& ISBN);
    void addFilmMedia(const std::string& title, const std::string& support, int ageLimit);
    void addGameMedia(const std::string& title, const std::string& studio, const std::string& genre, int PEGI);
    void removeMedia(const std::string& mediaType, const std::string& title);

    std::string listMedia() const;
    std::string listMediaByState(const std::string& state) const;
    std::string getMediaState(const std::string& mediaType, const std::string& title) const;
    std::string getWhoBorrowedMedia(const std::string& mediaType, const std::string& title) const;

    void rentMedia(const std::string& clientName, const std::string& mediaType, const std::string& title);
    void returnMedia(const std::string& clientName, const std::string& mediaType, const std::string& title);

    std::string showMediaBorrowedByClientWithNameAndFirstName(const std::string& clientName, const std::string& ClientFirstName) const;
    std::string showMediaBorrowedByClientWithMail(const std::string& mail) const;

    void addClient(const std::string& name, const std::string& firstname, int age, const std::string& address
        , const std::string& phoneNumber, const std::string& mail);
    void removeClientByNameAndFirstName(const std::string& name, const std::string& firstName);
    void removeClientByName(const std::string& name);
    void  removeClientByMail(const std::string& mail);
    std::string listClients() const;
    void showMedia(const std::string& clientName);

    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidEmail(const std::string& email);

    std::string getMediaInfo(const std::string& type, const std::string& title)const ;

private:
    std::shared_ptr<Media> findMedia(const std::string& mediaType, const std::string& title) const;
    Client getClient(const std::string& clientName) const;

    std::vector<std::shared_ptr<Media>> mediaCollection; 
    std::unordered_map<Client, std::vector<std::shared_ptr<Media>>, ClientHash> clientMediaMap;
    std::vector<Client> clients;
};

#endif // LIBRARY_SYSTEM_H