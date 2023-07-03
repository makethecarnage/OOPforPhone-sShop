#include "Client.h"

const std::string &Client::getName() const {
    return name;
}

void Client::setName(const std::string &name) {
    Client::name = name;
}

const std::string &Client::getPhoneNumber() const {
    return phoneNumber;
}

void Client::setPhoneNumber(const std::string &phone) {
    Client::phoneNumber = phoneNumber;
}

const std::string &Client::getDescription() const {
    return description;
}

void Client::setDescription(const std::string &description) {
    Client::description = description;
}

bool Client::operator==(const Client &rhs) const {
    return name == rhs.name &&
           phoneNumber == rhs.phoneNumber &&
           description == rhs.description;
}
