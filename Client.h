#ifndef TRYPROJECT_CLIENT_H
#define TRYPROJECT_CLIENT_H

#include <string>
#include <ctime>
#include <utility>


class Client {

private:
    std::string name;
    std::string phoneNumber;
    std::string description;

public:

    Client() = default;
    Client(std::string name,
           std::string phoneNumber,
           std::string description)
            : name(std::move(name)),
              phoneNumber(std::move(phoneNumber)),
              description(std::move(description)) {}

    const std::string &getName() const;
    void setName(const std::string &name);

    const std::string &getPhoneNumber() const;
    void setPhoneNumber(const std::string &phoneNumber);

    const std::string &getCity() const;
    void setCity(const std::string &city);

    const std::string &getDescription() const;
    void setDescription(const std::string &description);

    virtual void print() const = 0;

    virtual bool operator==(const Client &rhs) const;
    virtual bool operator!=(const Client &rhs) const;

};


#endif //TRYPROJECT_CLIENT_H
