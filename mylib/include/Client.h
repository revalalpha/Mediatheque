#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <functional>

class Client {
public:
    Client(const std::string& name, const std::string& firstName, int age, const std::string& address,
        const std::string& phoneNumber, const std::string& mail);

    // GETTERS
    std::string getName() const;
    std::string getFirstName() const;
    std::string getMail() const;
    int getAge() const;
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;

    bool operator==(const Client& other) const;

private:
    std::string name ;
    std::string firstName;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string mail;
};

struct ClientHash {
    size_t operator()(const Client& client) const {
        size_t hName  = std::hash<std::string>()(client.getName());
        size_t hFName = std::hash<std::string>()(client.getFirstName());
        size_t hAge   = std::hash<int>()(client.getAge());
        size_t hMail  = std::hash<std::string>()(client.getMail());
        // Combination of the hashes
        return hName ^ (hFName << 1) ^ (hAge << 2) ^ (hMail << 3);
    }
};

#endif