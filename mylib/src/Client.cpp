#include "Client.h"
#include <stdexcept>

Client::Client(const std::string& name, const std::string& firstName, int age, const std::string& address,
    const std::string& phoneNumber, const std::string& mail)
    : name(name), firstName(firstName), age(age), address(address), phoneNumber(phoneNumber), mail(mail) 
{
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative.\n");
    }
}

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

int Client::getAge() const {
    return age;
}

bool Client::operator==(const Client& other) const {
    return name == other.name && firstName == other.firstName && age == other.age
        && address == other.address && phoneNumber == other.phoneNumber && mail == other.mail;
}



