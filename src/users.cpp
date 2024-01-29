#include <iostream>
#include <cstring>
#include "device.h"

#include "users.h"

int User::numberOfUsers = 0;
int User::capacity = 0;
vector<User> User::users;
User::User(const string &name, const string &surname, const string &username,
           const string &password, const string &phone, int id, bool isAdmin, AccountType type)
    : name(name), surname(surname), username(username), password(password), phone(phone),
      id(id), isAdmin(isAdmin), type(type) {
    users.push_back(*this); 
    numberOfUsers++;
}

User::User() : name(""), surname(""), username(""), password(""), phone(""), id(0), isAdmin(false), type(AccountType::PATIENT) {
    users.push_back(*this); 
    numberOfUsers++;
}
const string User::accountTypeToString(AccountType type)
{
    switch (type)
    {
    case AccountType::PATIENT:
        return "PATIENT";
    case AccountType::DOCTOR:
        return "DOCTOR";
    case AccountType::LABMAN:
        return "LABMAN";
    default:
        return "PATIENT";
    }
}

User* User::verifyUser(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < users.size(); ++i)
    {

        if (users[i].getUsername() == inputUsername   &&  users[i].getPassword()==inputPassword )
        {
            // User found, return user information
            return &users[i];
            break;
        }
    }

    return nullptr;
}


const string &User::getName() const { return name; }
void User::setName(const string &newName) { name = newName; }

const string &User::getSurname() const { return surname; }
void User::setSurname(const string &newSurname) { surname = newSurname; }

const string &User::getUsername() const { return username; }
void User::setUsername(const string &newUsername) { username = newUsername; }

const string &User::getPassword() const { return password; }
void User::setPassword(const string &newPassword) { password = newPassword; }

const string &User::getPhone() const { return phone; }
void User::setPhone(const string &newPhone) { phone = newPhone; }

int User::getId() const { return id; }
void User::setId(int newId) { id = newId; }

bool User::getIsAdmin() const { return isAdmin; }
void User::setIsAdmin(bool newIsAdmin) { isAdmin = newIsAdmin; }

AccountType User::getAccountType() const { return type; }
void User::setAccountType(AccountType newType) { type = newType; }