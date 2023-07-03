#include "Shop.h"
#include "library.hpp"
#include <algorithm>

std::vector<Phone> Shop::getPhonesByBuyer(const Buyer &buyer) const {
    std::vector<Phone> result;
    for (const auto &sn : buyer.getSerialNumbers()) {
        result.push_back(this->phones[sn]);
    }
    return result;
}

std::vector<Phone> Shop::findPhones(const std::string &name) const {

    auto queryParts = split(name, ' ');
    std::vector<std::pair<int, Phone>> scores;
    for (const auto &phone : this->getPhones()) {
        scores.emplace_back(0, phone);
    }
    for (const auto &part : queryParts) {
        for (auto &score : scores) {
            bool brandMatch = score.second.getBrand().find(part) != std::string::npos;
            bool brandExactMatch = score.second.getBrand() == part;
            bool modelMatch = score.second.getModel().find(part) != std::string::npos;
            bool modelExactMatch = score.second.getModel() == part;
            bool serialNumberMatch = score.second.getSerialNumber().find(part) != std::string::npos;
            bool serialNumberExactMatch = score.second.getSerialNumber() == part;
            if (brandMatch) { score.first += 1<<0; }
            if (brandExactMatch) { score.first += 1<<3; }
            if (modelMatch) { score.first += 1<<1; }
            if (modelExactMatch) { score.first += 1<<4; }
            if (serialNumberMatch) { score.first += 1<<2; }
            if (serialNumberExactMatch) { score.first += 1<<5; }
        }
    }
    std::sort(scores.begin(),
              scores.end(),
              [](const auto &a, const auto &b) { return a.first > b.first; });
    std::vector<Phone> result;
    for (const auto &score : scores) {
        if (score.first > 0) {
            result.push_back(score.second);
        }
    }
    return result;
}

std::vector<Buyer> Shop::findBuyers(const std::string &query) const {

    auto queryParts = split(query, ' ');
    std::vector<std::pair<int, Buyer>> scores;
    for (const auto &buyer : this->getBuyers()) {
        scores.emplace_back(0, buyer);
    }
    for (const auto &part : queryParts) {
        for (auto &score : scores) {
            bool phoneMatch = score.second.getPhoneNumber().find(part) != std::string::npos;
            bool phoneExactMatch = score.second.getPhoneNumber() == part;
            bool nameMatch = score.second.getName().find(part) != std::string::npos;
            bool nameExactMatch = score.second.getName() == part;
            bool serialNumberMatch = false;
            bool serialNumberExactMatch = false;
            for (const auto &vin : score.second.getSerialNumbers()) {
                if (vin.find(part) != std::string::npos) { serialNumberMatch = true; }
                if (vin == part) { serialNumberExactMatch = true; }
                if (serialNumberMatch || serialNumberExactMatch) { break; }
            }
            if (phoneMatch) { score.first += 1 << 3; }
            if (phoneExactMatch) { score.first += 1 << 7; }
            if (nameMatch) { score.first += 1 << 1; }
            if (nameExactMatch) { score.first += 1 << 6; }
            if (serialNumberMatch) { score.first += 1 << 2; }
            if (serialNumberExactMatch) { score.first += 1 << 5; }
        }
    }
    std::sort(scores.begin(),
              scores.end(),
              [](const auto &a, const auto &b) { return a.first > b.first; });
    std::vector<Buyer> result;
    for (const auto &score : scores) {
        if (score.first > 0) {
            result.push_back(score.second);
        }
    }
    return result;
}


void Shop::toFile(std::ofstream &file) const {
    file << "Shop:\n";
    file << "\tName: " << this->getName() << "\n";
    file << "Buyers:\n";
    file << "\tCount: " << this->getBuyers().size() << "\n";
    for (int i = 0; i < this->getBuyers().size(); i++) {
        auto buyer = this->getBuyers().values()[i];
        file << "\tBuyer " << i + 1 << ":\n";
        file << "\t\tName: " << buyer.getName() << "\n";
        file << "\t\tPhoneNumber: " << buyer.getPhoneNumber() << "\n";
        file << "\t\tDescription: " << buyer.getDescription() << "\n";
        file << "\t\tSN_count: " << buyer.getSerialNumbers().size() << "\n";
        if (buyer.getSerialNumbers().empty()) { continue; }
        file << "\t\tSNs:\n";
        for (int j = 0; j < buyer.getSerialNumbers().size(); j++) {
            file << "\t\t\tSN " << j + 1 << ": " << buyer.getSerialNumber()[j] << "\n";
        }
    }
    file << "Phones:\n";
    file << "\tCount: " << this->getPhones().size() << "\n";
    for (int i = 0; i < this->getPhones().size(); i++) {
        auto phone = this->getPhones().values()[i];
        file << "\tPhone " << i + 1 << ":\n";
        file << "\t\tSN: " << phone.getSerialNumber() << "\n";
        file << "\t\tBrand: " << phone.getBrand() << "\n";
        file << "\t\tModel: " << phone.getModel() << "\n";
        file << "\t\tDescription: " << phone.getDescription() << "\n";
        file << "\t\tYear: " << phone.getYear() << "\n";
        file << "\t\tStorage: " << phone.getStorage() << "\n";
        file << "\t\tPrice: " << phone.getPrice() << "\n";
    }
}

bool Shop::fromFile(std::ifstream &file) {

    std::string line;
    std::string name;
    std::string phoneNumber;
    std::string description;
    std::string serialNumber;
    std::string brand;
    std::string model;
    unsigned int year;
    unsigned int storage;
    unsigned int price;

    while (std::getline(file, line)) {
        if (line == "Shop:") {
            std::getline(file, line);
            name = trim(split(line, ':')[1]);
            this->setName(name);
        }
        if (line == "Buyers:") {
            std::getline(file, line);
            int count = std::stoi(trim(split(line, ':')[1]));
            for (int i = 0; i < count; i++) {
                std::getline(file, line);
                std::getline(file, line);
                name = trim(split(line, ':')[1]);
                std::getline(file, line);
                phoneNumber = trim(split(line, ':')[1]);
                std::getline(file, line);
                description = trim(split(line, ':')[1]);
                std::getline(file, line);
                int snCount = std::stoi(trim(split(line, ':')[1]));
                std::vector<std::string> vins;
                if (snCount > 0) {
                    std::getline(file, line);
                    for (int j = 0; j < snCount; j++) {
                        std::getline(file, line);
                        vins.push_back(trim(split(line, ':')[1]));
                    }
                }
                this->addBuyer({name, phoneNumber,  description, vins});
            }
        }
        if (line == "Phones:") {
            std::getline(file, line);
            int count = std::stoi(trim(split(line, ':')[1]));
            for (int i = 0; i < count; i++) {
                std::getline(file, line);
                std::getline(file, line);
                serialNumber = trim(split(line, ':')[1]);
                std::getline(file, line);
                brand = trim(split(line, ':')[1]);
                std::getline(file, line);
                model = trim(split(line, ':')[1]);
                std::getline(file, line);
                description = trim(split(line, ':')[1]);
                std::getline(file, line);
                year = std::stoi(trim(split(line, ':')[1]));
                std::getline(file, line);
                storage = std::stoi(trim(split(line, ':')[1]));
                std::getline(file, line);
                price = std::stoi(trim(split(line, ':')[1]));
                this->addPhone({serialNumber, brand, model, description,  year, storage,
                              price});
            }
        }
    }
    return true;
}
