#include "Client.h"

Client::Client(const std::string& name, const std::string& firstName, int age, const std::string& address,
    const std::string& phoneNumber, const std::string& mail)
    : m_name(name), m_firstName(firstName), m_age(age), m_address(address), m_phoneNumber(phoneNumber), m_mail(mail) 
{
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative.\n");
    }
}

// GETTERS
std::string Client::getName() const 
{
    return m_name;
}

std::string Client::getFirstName() const 
{
    return m_firstName;
}

std::string Client::getMail() const 
{
    return m_mail;
}

int Client::getAge() const 
{
    return m_age;
}

const std::string& Client::getAddress() const 
{
    return m_address; 
}

const std::string& Client::getPhoneNumber() const 
{ 
    return m_phoneNumber; 
}

bool Client::operator==(const Client& other) const
{
    return m_name == other.m_name && m_firstName == other.m_firstName && m_age == other.m_age
        && m_address == other.m_address && m_phoneNumber == other.m_phoneNumber && m_mail == other.m_mail;
}



