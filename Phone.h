#ifndef TRYPROJECT_PHONE_H
#define TRYPROJECT_PHONE_H

#include <string>

class Phone{

private:

    std::string serialNumber;
    std::string brand;
    std::string model;
    std::string description;
    unsigned int year{};
    unsigned int storage{};
    unsigned int price{};


public:

    Phone() = default;

    Phone(std::string serialNumber,
                std::string brand,
                std::string model,
                std::string description,
                unsigned int year,
                unsigned int storage,
                unsigned int price)
                : serialNumber(std::move(serialNumber)),
    brand(std::move(brand)),
    model(std::move(model)),
    description(std::move(description)),
    year(year),
    storage(storage),
    price(price) {}

    const std::string &getSerialNumber() const { return serialNumber; }
    void setSerialNumber(const std::string &serialNumber) { this->serialNumber = serialNumber; }

    const std::string &getBrand() const { return brand; }
    void setBrand(const std::string &brand) { this->brand = brand; }

    const std::string &getModel() const { return model; }
    void setModel(const std::string &model) { this->model = model; }

    const std::string &getDescription() const { return description; }
    void setDescription(const std::string &description) { this->description = description; }

    const unsigned int &getYear() const { return year; }
    void setYear(const unsigned int &year);

    const unsigned int &getStorage() const { return storage; }
    void setStorage(const unsigned int &storage);

    const unsigned int &getPrice() const { return price; }
    void setPrice(const unsigned int &price);


};


#endif //TRYPROJECT_PHONE_H
