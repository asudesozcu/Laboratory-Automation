#include <iostream>
#include <cstring>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"

int numberOfUsers=0;
     int capacity=0;
vector<User> User::users;
User::User(const string &name, const string &surname, const string &username, const string &password, const string &phone, int id, bool isAdmin, AccountType type)
    : name(name), surname(surname), username(username), password(password), phone(phone), id(id), isAdmin(isAdmin), type(type) {}

User::User() : id(0), isAdmin(false), type(AccountType::PATIENT) {}




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

User* User::verifyUser(const string &inputUsername, const string &inputPassword) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (inputUsername == users[i].getUsername() && inputPassword == users[i].getPassword()) {
            return &users[i]; // User found, return user information
        }
    }

    return nullptr; // User not found or password is incorrect
}

Patient *User::verifyPatient(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < Patient::patients.size(); ++i)
    {
        if (inputUsername == Patient::patients[i].getUserInfo().getUsername() &&
            inputPassword == Patient::patients[i].getUserInfo().getPassword())
        {
            return &Patient::patients[i]; // Patient found, return patient information
        }
    }

    return nullptr; // Patient not found or password is incorrect
}

Doctor *User::verifyDoctor(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < Doctor::doctors.size(); ++i)
    {
        if (inputUsername == Doctor::doctors[i].getUserInfo().getUsername() &&
            inputPassword == Doctor::doctors[i].getUserInfo().getPassword())
        {
            return &Doctor::doctors[i]; // Doctor found, return doctor information
        }
    }

    return nullptr; // Doctor not found or password is incorrect
}

LabWorker *User::verifyLabWorker(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (inputUsername == LabWorker::labWorkers[i].getUserInfo().getUsername() &&
            inputPassword == LabWorker::labWorkers[i].getUserInfo().getPassword())
        {
            return &LabWorker::labWorkers[i]; // LabWorker found, return LabWorker information
        }
    }

    return nullptr; // LabWorker not found or password is incorrect
}


void User::addUserLabWorker(LabWorker *labWorker)
{
    User newUser(labWorker->getUserInfo().getName(),
                 labWorker->getUserInfo().getSurname(),
                 labWorker->getUserInfo().getUsername(),
                 labWorker->getUserInfo().getPassword(),
                 labWorker->getUserInfo().getPhone(),
                 labWorker->getUserInfo().getId(),
                 labWorker->getUserInfo().getIsAdmin(),
                 AccountType::LABMAN);

    User::users.push_back(newUser);
}

// Function to add a patient
void User::addUserPatient(Patient *patient)
{
    User newUser(patient->getUserInfo().getName(),
                 patient->getUserInfo().getSurname(),
                 patient->getUserInfo().getUsername(),
                 patient->getUserInfo().getPassword(),
                 patient->getUserInfo().getPhone(),
                 patient->getUserInfo().getId(),
                 patient->getUserInfo().getIsAdmin(),
                 AccountType::PATIENT);

    User::users.push_back(newUser);
}

// Function to add a doctor
void User::addUserDoctor(Doctor *doctor)
{
    User newUser(doctor->getUserInfo().getName(),
                 doctor->getUserInfo().getSurname(),
                 doctor->getUserInfo().getUsername(),
                 doctor->getUserInfo().getPassword(),
                 doctor->getUserInfo().getPhone(),
                 doctor->getUserInfo().getId(),
                 doctor->getUserInfo().getIsAdmin(),
                 AccountType::DOCTOR);

    User::users.push_back(newUser);
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