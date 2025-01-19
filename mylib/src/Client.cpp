#include "Client.h"

Client::Client(const std::string& name, const std::string& firstName, int age, const std::string& address,
    const std::string& phoneNumber, const std::string& mail)
    : name(name), firstName(firstName), age(age), address(address), phoneNumber(phoneNumber), mail(mail) {}

// GETTERS
std::string Client::getName() const {
    return name;
}

std::string Client::getFirstName() const {
    return firstName;
}

std::string Client::getMail() const {
    return mail;
}

