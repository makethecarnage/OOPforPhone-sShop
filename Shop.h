#ifndef TRYPROJECT_SHOP_H
#define TRYPROJECT_SHOP_H

#include <string>
#include <vector>
#include <QMap>
#include <fstream>

#include "Buyer.h"
#include "Phone.h"


class Shop {

public:

    Shop() = default;

    Shop(std::string name) : name(std::move(name)) {}
    const std::string &getName() const { return name; }
    void setName(const std::string &name) { this->name = name; }

    const QMap<std::string, Buyer> &getBuyers() const { return buyers; }
    void addBuyer(const Buyer &buyer) { buyers.insert(buyer.getPhoneNumber(), buyer); }
    Buyer& getBuyer(const std::string &phone) { return buyers[phone]; }
    void removeBuyer(const std::string &phone) { buyers.remove(phone); }
    std::vector<Buyer> findBuyers(const std::string &query) const;

    const QMap<std::string, Phone> &getPhones() const { return phones; }
    void addPhone(const Phone &phone) { phones.insert(phone.getSerialNumber(), phone); }
    void removePhone(const std::string &vin) { phones.remove(vin); }
    Phone& getPhone(const std::string &vin) { return phones[vin]; }

    std::vector<Phone> getPhonesByBuyer(const Buyer &buyer) const;
    std::vector<Phone> findPhones(const std::string &name) const;

    void toFile(std::ofstream &file) const;
    bool fromFile(std::ifstream &file);

private:

    Qmap<std::string, Buyer> buyers;
    Qmap<std::string, Phone> phones;
    std::string name;
};
