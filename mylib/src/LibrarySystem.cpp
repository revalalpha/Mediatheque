#include "LibrarySystem.h"

void LibrarySystem::addMedia(const std::string& mediaType, const std::vector<std::string>& args) {
    try {
        auto media = MediaFactory::createMedia(mediaType, args);
        mediaCollection.push_back(media);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to add media: " + std::string(e.what()));
    }
}

void LibrarySystem::addBookMedia(const std::string& title, const std::string& ISBN)
{
    addMedia("book", { title, ISBN });
}

void LibrarySystem::addFilmMedia(const std::string& title, const std::string& support, int ageLimit)
{
    addMedia("film", { title, support, std::to_string(ageLimit) });
}

void LibrarySystem::addGameMedia(const std::string& title, const std::string& studio, const std::string& genre, int PEGI)
{
    addMedia("game", { title, studio, genre, std::to_string(PEGI) });
}

void LibrarySystem::removeMedia(const std::string& mediaType, const std::string& title) {
    auto it = std::find_if(mediaCollection.begin(), mediaCollection.end(),
        [&mediaType, &title](const std::shared_ptr<Media>& media) {
            return media->getType() == mediaType && media->getTitle() == title;
        });

    if (it == mediaCollection.end())
        throw std::runtime_error("Media not found: " + title);

    if ((*it)->getBorrowedStatus())
        throw std::runtime_error("Cannot remove borrowed media: " + title);

    mediaCollection.erase(it);
}

std::string LibrarySystem::listMedia() const {
    if (mediaCollection.empty())
        return "No media available.\n";
    std::ostringstream oss;
    for (const auto& media : mediaCollection)
        oss << media->getInfo() << "\n";
    return oss.str();
}

std::string LibrarySystem::listMediaByState(const std::string& state) const {
    MediaState desiredState;
    if (state == "available")
        desiredState = MediaState::Available;
    else if (state == "borrowed")
        desiredState = MediaState::Borrowed;
    else
        throw std::invalid_argument("Invalid state. Use 'available' or 'borrowed'.");

    std::ostringstream oss;
    for (const auto& media : mediaCollection) {
        if (media->getState() == desiredState)
            oss << media->getTitle() << "\n";
    }
    return oss.str().empty() ? "No media found in the requested state." : oss.str();
}

std::string LibrarySystem::getMediaState(const std::string& mediaType, const std::string& title) const {
    auto media = findMedia(mediaType, title);
    return media->getBorrowedStatus() ? "Borrowed" : "Available";
}

std::string LibrarySystem::getWhoBorrowedMedia(const std::string& mediaType, const std::string& title) const {
    for (const auto& [client, borrowedMedias] : clientMediaMap) 
        for (const auto& media : borrowedMedias)
            if (media->getType() == mediaType && media->getTitle() == title)
                return client.getName();
    throw std::runtime_error("Media not borrowed: " + title);
}

void LibrarySystem::rentMedia(const std::string& clientName, const std::string& mediaType, const std::string& title) {
    auto clientIt = std::find_if(clients.begin(), clients.end(),
        [&clientName](const Client& client) { return client.getName() == clientName; });

    if (clientIt == clients.end())
        throw std::runtime_error("Client not found: " + clientName);
    Client& client = *clientIt;

    auto mediaIt = std::find_if(mediaCollection.begin(), mediaCollection.end(),
        [&mediaType, &title](const std::shared_ptr<Media>& media) {
            return media->getType() == mediaType && media->getTitle() == title;
        });

    if (mediaIt == mediaCollection.end())
        throw std::runtime_error("Media not found: " + title);
    std::shared_ptr<Media> media = *mediaIt;

    if (media->getBorrowedStatus())
        throw std::runtime_error("Media already borrowed: " + title);

    if (media->getType() == "film")
    {
        auto film = std::dynamic_pointer_cast<Film>(media);
        if (client.getAge() < film->getAgeLimit())
            throw std::runtime_error("Client does not meet age limit for this film.");
    }

    if (clientMediaMap[client].size() >= 5)
        throw std::runtime_error("Client has already borrowed the maximum number of items.");

    if (std::find(clientMediaMap[client].begin(), clientMediaMap[client].end(), media) != clientMediaMap[client].end())
        throw std::runtime_error("Client already borrowed this media: " + title);

    media->borrow();
    clientMediaMap[client].push_back(media);
}

void LibrarySystem::returnMedia(const std::string& clientName, const std::string& mediaType, const std::string& title) {
    auto client = getClient(clientName);
    auto it = std::find_if(clientMediaMap[client].begin(), clientMediaMap[client].end(),
        [&mediaType, &title](const std::shared_ptr<Media>& media) {
            return media->getType() == mediaType && media->getTitle() == title;
        });

    if (it == clientMediaMap[client].end()) {
        throw std::runtime_error("Media not borrowed by client: " + title);
    }

    (*it)->returnMedia();
    clientMediaMap[client].erase(it);
}

std::string LibrarySystem::showMediaBorrowedByClientWithNameAndFirstName(const std::string& clientName, const std::string& clientFirstName) const
{
    auto it = std::find_if(clients.begin(), clients.end(),
        [&clientName, &clientFirstName](const Client& client){
            return client.getName() == clientName && client.getFirstName() == clientFirstName;
        });

    if (it == clients.end())
        return "Client not found.";

    const Client& client = *it;
    std::string result;

    auto mediaIt = clientMediaMap.find(client);
    if (mediaIt != clientMediaMap.end())
        for (const auto& media : mediaIt->second)
            result += media->getTitle() + "\n";
    else
        result = "No media borrowed by this client.";

    return result;
}

std::string LibrarySystem::showMediaBorrowedByClientWithMail(const std::string& mail) const
{
    auto it = std::find_if(clients.begin(), clients.end(),
        [&mail](const Client& client){
            return client.getMail() == mail;
        });

    if (it == clients.end())
        return "Client not found.";
    const Client& client = *it;
    std::string result;

    auto mediaIt = clientMediaMap.find(client);
    if (mediaIt != clientMediaMap.end())
        for (const auto& media : mediaIt->second)
            result += media->getTitle() + "\n";
    else
        result = "No media borrowed by this client.";

    return result;
}

std::shared_ptr<Media> LibrarySystem::findMedia(const std::string& mediaType, const std::string& title) const {
    auto it = std::find_if(mediaCollection.begin(), mediaCollection.end(),
        [&mediaType, &title](const std::shared_ptr<Media>& media) {
            return media->getType() == mediaType && media->getTitle() == title;
        });

    if (it == mediaCollection.end())
        throw std::runtime_error("Media not found: " + title);

    return *it;
}

Client LibrarySystem::getClient(const std::string& clientName) const
{
    for (const auto& client : clients)
    {
        if (client.getName() == clientName)
            return client; 
    }
    throw std::runtime_error("Client not found.");
}

void LibrarySystem::addClient(const std::string& name, const std::string& firstname, int age, const std::string& address
    , const std::string& phoneNumber, const std::string& mail)
{
    auto it = std::find_if(clients.begin(), clients.end(),
        [&name, &firstname, age, &address, &phoneNumber, &mail](const Client& client) {
            return client.getName() == name && client.getFirstName() == firstname && client.getAge() == age
                && client.getAddress() == address && client.getPhoneNumber() == phoneNumber && client.getMail() == mail;
        });

    if (it != clients.end())
        throw std::runtime_error("Client is already registered.");
    if (!isValidPhoneNumber(phoneNumber))
        throw std::runtime_error("Error: Invalid phone number. It should contain only digits.");
    if (mail.empty())
        throw std::runtime_error("Error: Email cannot be empty.");
    if (!isValidEmail(mail))
        throw std::runtime_error("Error: Invalid email address. It should contain an '@' and a '.'.");
    clients.emplace_back(name, firstname, age, address, phoneNumber, mail);
}

void LibrarySystem::removeClientByName(const std::string& name)
{
    auto it = std::remove_if(clients.begin(), clients.end(),
        [&name](const Client& client){
            return client.getName() == name;
        });

    if (it != clients.end())
        clients.erase(it, clients.end());
    else
        throw std::runtime_error("Client not found.");
}


void LibrarySystem::removeClientByNameAndFirstName(const std::string& name, const std::string& firstName)
{
    auto it = std::find_if(clients.begin(), clients.end(),
        [&name, &firstName](const Client& client){
            return client.getName() == name && client.getFirstName() == firstName;
        });

    if (it == clients.end())
        throw std::runtime_error("Client not found with the name: " + name + " and first name: " + firstName);
    clientMediaMap.erase(*it);
    clients.erase(it);
}

void LibrarySystem::removeClientByMail(const std::string& mail)
{
    auto it = std::remove_if(clients.begin(), clients.end(),
        [&mail](const Client& client){
            return client.getMail() == mail;
        });

    if (it != clients.end())
        clients.erase(it, clients.end());
    else
        throw std::runtime_error("Client not found with the email: " + mail);
}


std::string LibrarySystem::listClients() const
{
    if (clients.empty())
        return "No client registered.\n";
    std::ostringstream oss;
    for (const auto& client : clients)
    {
        oss << "Name : " << client.getName() << "\n"
            << "FirstName : " << client.getFirstName() << "\n"
            << "Age  : " << client.getAge() << "\n"
            << "Address : " << client.getAddress() << "\n"
            << "Phone Number  : " << client.getPhoneNumber() << "\n"
            << "Mail : " << client.getMail() << "\n\n";
    }
    return oss.str();
}

void LibrarySystem::showMedia(const std::string& clientName) {
    auto client = getClient(clientName);
    std::ostringstream oss;

    if (clientMediaMap[client].empty())
        throw("No media borrowed by client: " + clientName);

    oss << "Media borrowed by " << clientName << ":\n";
    for (const auto& media : clientMediaMap[client]) {
        oss << " - " << media->getTitle() << " (" << media->getType() << ")\n";
    }
}

std::string LibrarySystem::getMediaInfo(const std::string& type, const std::string& title) const
{
    for (const auto& media : mediaCollection)
    {
        if (media->getType() == type && media->getTitle() == title)
        {
            return media->getInfo();
        }
    }

    throw std::runtime_error("Media not found: " + title);
}


bool LibrarySystem::isValidPhoneNumber(const std::string& phoneNumber)
{
    // validation if the phone number is valid with 0-9
    std::regex phonePattern("^[0-9]+$");
    return std::regex_match(phoneNumber, phonePattern);
}

bool LibrarySystem::isValidEmail(const std::string& email)
{
    // validation if the email is valid with ...@...'.'... (found the regex on internet)
    std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, emailPattern);
}