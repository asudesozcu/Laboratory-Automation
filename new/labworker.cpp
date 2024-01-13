#include <iostream>
#include <cstdlib>
#include <cstring>
#include "labworker.h"
#include "users.h"
#include "device.h"

vector<LabWorker> LabWorker::labWorkers;
int LabWorker::labWorkerCount = 0;
int LabWorker::labWorkerCapacity = 10;  // You can adjust the capacity as needed

// Default constructor
LabWorker::LabWorker() : User() {
}

// Parameterized constructor
LabWorker::LabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone)
    : User(username, name, surname, password, phone, id, false, AccountType::LABMAN) {
}

void LabWorker::createLabWorker(const std::string &username, long id, const std::string &password, const std::string &name, const std::string &surname, const std::string &phone)
{
    LabWorker newLabworker(username, id, password, name, surname, phone);

    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (LabWorker::labWorkers[i].getUserInfo().getId() == id)
        {
            std::cout << "Error: This id is already in use." << std::endl;
            return;
        }
    }

    addToWorkersList(&newLabworker);

    User::addUserLabWorker(&newLabworker);
}

void LabWorker::addToWorkersList(const LabWorker *existingWorker)
{
    // If the capacity of the vector is insufficient, expand it
    if (labWorkerCount >= labWorkerCapacity)
    {
        if (labWorkerCapacity == 0)
        {
            labWorkerCapacity = INITIAL_CAPACITY;
        }
        else
        {
            labWorkerCapacity += 10;
        }

        LabWorker::labWorkers.resize(labWorkerCapacity);
    }

    // Add the existing LabWorker
    LabWorker::labWorkers[labWorkerCount] = *existingWorker;
    labWorkerCount++;
}

int LabWorker::exists(const std::string &desiredUsername)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (LabWorker::labWorkers[i].getUserInfo().getUsername() == desiredUsername)
        {
            return 1; // LabWorker found
        }
    }

    return 0; // LabWorker not found
}

LabWorker LabWorker::findLabWorker(int labWorkerId, const std::string &labWorkerPassword)
{
    LabWorker emptyLabWorker;

    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {

        if (LabWorker::labWorkers[i].getUserInfo().getId() == labWorkerId)
        {
            if (strcmp(LabWorker::labWorkers[i].getUserInfo().getPassword().c_str(), labWorkerPassword.c_str()) == 0)
            {
                return LabWorker::labWorkers[i]; // LabWorker found
            }
            else
            {
                // Password does not match
                break;
            }
        }
    }

    // Return an "empty" LabWorker if not found
    std::cout << "LabWorker not found or password is incorrect." << std::endl;
    return emptyLabWorker;
}

void changeDeviceStatus(const std::string &labWorkerPassword, int LabWorkerId, int DeviceID, const std::string &deviceName)
{
    // Find the LabWorker
    LabWorker foundLabWorker = LabWorker::findLabWorker(LabWorkerId, labWorkerPassword);

    // If the Device is not found
    int deviceIndex = -1; // Initial value to indicate not found

    for (int i = 0; i < Device::devices.size(); ++i)
    {
        if (Device::devices[i].getId() == DeviceID && Device::devices[i].getName() == deviceName)
        {
            // Save the index when the Device is found
            deviceIndex = i;
            break;
        }
    }

    if (deviceIndex != -1)
    {
        // Device found, update status based on the entered value
        std::string status;

        std::cout << "Enter the new status for Device ID " << DeviceID << ": ";
        std::cin >> status;

        if (status == "inUse")
        {
            Device::devices[deviceIndex].setDeviceStatus(Device::devices[deviceIndex].getId(), Device::DeviceStatus::inUse);
        }
        else if (status == "broken")
        {
            Device::devices[deviceIndex].setDeviceStatus(Device::devices[deviceIndex].getId(), Device::DeviceStatus::broken);
        }
        else if (status == "usable")
        {
            Device::devices[deviceIndex].setDeviceStatus(Device::devices[deviceIndex].getId(), Device::DeviceStatus::usable);
        }
        else
        {
            std::cout << "Unauthorized status. Allowed statuses: inUse, broken, usable." << std::endl;
        }
    }
    else
    {
        // If the Device is not found
        std::cout << "Device not found." << std::endl;
    }
}

void LabWorker::getInfo(const LabWorker *labWorker)
{
    const User &userInfo = labWorker->getUserInfo();

    std::cout << "ID: " << userInfo.getId() << std::endl;
    std::cout << "Name: " << userInfo.getName() << std::endl;
    std::cout << "Surname: " << userInfo.getSurname() << std::endl;
    std::cout << "Username: " << userInfo.getUsername() << std::endl;
    std::cout << "Password: " << userInfo.getPassword() << std::endl;
}

void LabWorker::removeLabWorker(int labWorkerId, int userId)
{
    // Check the user ID
    for (size_t i = 0; i < User::numberOfUsers; ++i)
    {
        if (User::users[i].getId() == userId)
        {
            // ID matched, check isAdmin
            if (User::users[i].getIsAdmin())
            {
                // Find the LabWorker in the labWorkers vector
                for (auto it = LabWorker::labWorkers.begin(); it != LabWorker::labWorkers.end(); ++it)
                {
                    if (it->getUserInfo().getId() == labWorkerId)
                    {
                        // Erase the LabWorker from the labWorkers vector
                        it = LabWorker::labWorkers.erase(it);

                        // Update the LabWorker count
                        --labWorkerCount;

                        // Clear the last element in the Users array
                        memset(&User::users[User::numberOfUsers - 1], 0, sizeof(User));

                        std::cout << "LabWorker with ID " << labWorkerId << " removed." << std::endl;
                        return;
                    }
                }

                // LabWorker not found
                std::cout << "LabWorker with ID " << labWorkerId << " not found." << std::endl;
            }
            else
            {
                // If isAdmin is false, permission error
                std::cout << "Permission denied. User with ID " << userId << " is not an admin." << std::endl;
            }
            return; // Exit the function after processing
        }
    }

    // User not found
    std::cout << "User with ID " << userId << " not found." << std::endl;
}

void LabWorker::setLabWorkerPassword(User *user, const std::string &password)
{
    user->setPassword(password);
}

void LabWorker::setLabWorkerName(User *user, const std::string &name)
{
    user->setName(name);
}

void LabWorker::setLabWorkerSurname(User *user, const std::string &surname)
{
    user->setSurname(surname);
}

void LabWorker::setLabWorkerUsername(User *user, const std::string &username)
{
    user->setUsername(username);
}

void LabWorker::setLabWorkerAdminStatus(LabWorker *labworker, int userID)
{
    for (size_t i = 0; i < User::numberOfUsers; ++i)
    {
        if (User::users[i].getId() == userID)
        {
            // ID matched, check if the user is an admin
            if (User::users[i].getIsAdmin())
            {
                // Set the isAdmin attribute using a boolean value
                labworker->userInfo.setIsAdmin(true);
            }
            else
            {
                // If isAdmin is false, permission error
                std::cout << "Permission denied. User with ID " << userID << " is not an admin." << std::endl;
            }
            return; // Exit the function after processing
        }
    }

    std::cout << "User with ID " << userID << " not found." << std::endl;
}
