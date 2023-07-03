#ifndef TRYPROJECT_BUYER_H
#define TRYPROJECT_BUYER_H

#include <string>
#include <vector>

#include "Client.h"

//#include "Phone.h"
class Phone;

class Buyer : public Client{

private:

    std::vector<std::string> serialNumbers;

public:

    Buyer() = default;
    Buyer(std::string name,
                std::string phoneNumber,
                std::string description,
                std::vector<std::string> serialNumbers)
        : Client(std::move(name),
            std::move(phoneNumber),
            std::move(description)),
            serialNumbers(std::move(serialNumbers)) {}

    const std::vector<std::string> &getSerialNumbers() const;
    bool addSerialNumber(const std::string &sn);
    bool removeSerialNumber(const std::string &sn);

    virtual bool operator==(const Buyer &rhs) const;
    virtual bool operator!=(const Buyer &rhs) const;

    bool operator+=(const Phone &phone);
    bool operator-=(const Phone &phone);

    virtual void print() const override;

};

#endif //TRYPROJECT_BUYER_H
