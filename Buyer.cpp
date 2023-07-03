#include <iostream>

#include "Buyer.h"
#include "Phone.h"

const std::vector<std::string> &Buyer::getSerialNumbers() const {
    return serialNumbers;
}

bool Buyer::addSerialNumber(const std::string &sn) {
    if (std::find(serialNumbers.begin(), serialNumbers.end(), sn) != serialNumbers.end()) {
        return false;
    }
    serialNumbers.push_back(sn);
    return true;
}

bool Buyer::removeSerialNumber(const std::string &sn) {
    if (std::find(serialNumbers.begin(), serialNumbers.end(), sn) == serialNumbers.end()) { return false; }
    serialNumbers.erase(std::remove(serialNumbers.begin(), serialNumbers.end(), sn), serialNumbers.end());
    return true;
}

bool Buyer::operator+=(const Phone &phone) {
    for (const auto &sn : serialNumbers) {
        if (sn == phone.getSerialNumber()) { return false; }
    }
    addSerialNumber(phone.getSerialNumber());
    return true;
}

bool Buyer::operator-=(const Phone &phone) {
    for (const auto &sn : serialNumbers) {
        if (sn == phone.getSerialNumber()) {
            removeSerialNumber(phone.getSerialNumber());
            return true;
        }
    }
    return false;
}

bool Buyer::operator==(const Buyer &rhs) const {
    return Client::operator==(rhs) &&
           serialNumbers == rhs.serialNumbers;
}

bool Buyer::operator!=(const Buyer &rhs) const {
    return !(rhs == *this);
}

void Buyer::print() const {
    std::cout << "Client: " << std::endl;
    std::cout << "  Name: " << getName() << std::endl;
    std::cout << "  Phone: " << getPhoneNumber() << std::endl;
    std::cout << "  Description: " << getDescription() << std::endl;
    std::cout << "  Phone SerialNumbers: " << std::endl;
    for (const auto &sn : serialNumbers) {
        std::cout << "    " << sn << std::endl;
    }
    std::cout << std::endl;
}
