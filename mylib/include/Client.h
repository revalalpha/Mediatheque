#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include <ostream>

class Client {
public:
    Client(const std::string& name, const std::string& firstName, int age, const std::string& address, const std::string& phoneNumber, const std::string& mail);

    // GETTERS
    std::string getName() const;
    std::string getFirstName() const;
    std::string getMail() const;

    friend std::ostream& operator<<(std::ostream& os, const Client& client);

private:
    std::string name;
    std::string firstName;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string mail;

};

#endif