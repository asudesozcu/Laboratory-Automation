#include <iostream>
#include <cstdlib>
#include <cstring>
#include "labworker.h"
#include "users.h"
#include "device.h"

vector<LabWorker> LabWorker::labWorkers;
int LabWorker::labWorkerCount = 0;
int LabWorker::labWorkerCapacity = 10; 
#define INITIAL_CAPACITY 10

LabWorker::LabWorker() : User()
{
}

LabWorker::LabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone, bool isadmin)
    : User(username, name, surname, password, phone, id, isadmin, AccountType::LABMAN)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (LabWorker::labWorkers[i].getUserInfo().getId() == id)
        {
            cout << "Error: This id is already in use." << endl;
            return;
        }
    }

    LabWorker *newLabworker = new LabWorker();
    newLabworker->userInfo.setId(id);
    newLabworker->userInfo.setName(name);
    newLabworker->userInfo.setSurname(surname);
    newLabworker->userInfo.setPassword(password);
    newLabworker->userInfo.setUsername(username);
    newLabworker->userInfo.setPhone(phone);
    newLabworker->userInfo.setAccountType(AccountType::LABMAN);
    newLabworker->userInfo.setIsAdmin(isadmin);

    LabWorker::addToWorkersList(newLabworker);
    LabWorker::addUserLabWorker(newLabworker);
}

void LabWorker::createLabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone, bool isAdmin)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (LabWorker::labWorkers[i].getUserInfo().getId() == id)
        {
            cout << "Error: This id is already in use." << endl;
            return;
        }
    }

    LabWorker *newLabworker = new LabWorker();
    newLabworker->userInfo.setId(id);
    newLabworker->userInfo.setName(name);
    newLabworker->userInfo.setSurname(surname);
    newLabworker->userInfo.setPassword(password);
    newLabworker->userInfo.setUsername(username);
    newLabworker->userInfo.setPhone(phone);
    newLabworker->userInfo.setAccountType(AccountType::LABMAN);
    newLabworker->userInfo.setIsAdmin(isAdmin);

    LabWorker::addToWorkersList(newLabworker);
    LabWorker::addUserLabWorker(newLabworker);
    cout<< "Worker Created!";
}
void LabWorker::addUserLabWorker(LabWorker *labWorker)
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
void LabWorker::addToWorkersList(LabWorker *existingWorker)
{
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

        labWorkers.resize(labWorkerCapacity); 
    }

    labWorkers.push_back(*existingWorker);
    labWorkerCount++;
}
int LabWorker::exists(const string &desiredUsername)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (LabWorker::labWorkers[i].getUserInfo().getUsername() == desiredUsername)
        {
            return 1; 
        }
    }

    return 0; 
}

LabWorker LabWorker::findLabWorker(int labWorkerId, const string &labWorkerPassword)
{
    LabWorker emptyLabWorker;

    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {

        if (LabWorker::labWorkers[i].getUserInfo().getId() == labWorkerId)
        {
            if (strcmp(LabWorker::labWorkers[i].getUserInfo().getPassword().c_str(), labWorkerPassword.c_str()) == 0)
            {
                return LabWorker::labWorkers[i]; 
            }
            else
            {
                // Password does not match
                break;
            }
        }
    }

    cout << "LabWorker not found or password is incorrect." << endl;
    return emptyLabWorker;
}

void changeDeviceStatus(const string &labWorkerPassword, int LabWorkerId, int DeviceID, const string &deviceName)
{
    LabWorker foundLabWorker = LabWorker::findLabWorker(LabWorkerId, labWorkerPassword);

    
    int deviceIndex = -1; 

    for (int i = 0; i < Device::devices.size(); ++i)
    {
        if (Device::devices[i].getId() == DeviceID && Device::devices[i].getName() == deviceName)
        {
            deviceIndex = i;
            break;
        }
    }

    if (deviceIndex != -1)
    {
        string status;

        cout << "Enter the new status for Device ID " << DeviceID << ": ";
        cin >> status;

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
            cout << "Unauthorized status. Allowed statuses: inUse, broken, usable." << endl;
        }
    }
    else
    {
        cout << "Device not found." << endl;
    }
}

void LabWorker::displayInfo() const
{
    cout << "ID: " << userInfo.getId() << endl;
    cout << "Name: " << userInfo.getName() << endl;
    cout << "Surname: " << userInfo.getSurname() << endl;
    cout << "Username: " << userInfo.getUsername() << endl;
    cout << "Password: " << userInfo.getPassword() << endl;
}

void LabWorker::removeLabWorker(int labWorkerId, int userId)
{
    for (size_t i = 0; i < User::numberOfUsers; ++i)
    {
        if (User::users[i].getId() == userId)
        {
            if (User::users[i].getIsAdmin())
            {
                for (auto it = LabWorker::labWorkers.begin(); it != LabWorker::labWorkers.end(); ++it)
                {
                    if (it->getUserInfo().getId() == labWorkerId)
                    {
                        it = LabWorker::labWorkers.erase(it);

                        --labWorkerCount;

                        // Clear the last element in the Users array
                        memset(&User::users[User::numberOfUsers - 1], 0, sizeof(User));

                        cout << "LabWorker with ID " << labWorkerId << " removed." << endl;
                        return;
                    }
                }

                cout << "LabWorker with ID " << labWorkerId << " not found." << endl;
            }
            else
            {
                cout << "Permission denied. User with ID " << userId << " is not an admin." << endl;
            }
            return; 
        }
    }

    cout << "User with ID " << userId << " not found." << endl;
}
LabWorker *LabWorker::verifyLabWorker(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < LabWorker::labWorkers.size(); ++i)
    {
        if (inputUsername == LabWorker::labWorkers[i].getUserInfo().getUsername() &&
            inputPassword == LabWorker::labWorkers[i].getUserInfo().getPassword())
        {
            return &LabWorker::labWorkers[i]; 
        }
    }

    return nullptr; 
}

void LabWorker::setLabWorkerAdminStatus(LabWorker *labworker, int userID)
{
    for (size_t i = 0; i < User::numberOfUsers; ++i)
    {
        if (User::users[i].getId() == userID)
        {
            if (User::users[i].getIsAdmin())
            {
                labworker->userInfo.setIsAdmin(true);
            }
            else
            {
                cout << "Permission denied. User with ID " << userID << " is not an admin." << endl;
            }
            return; 
        }
    }

    cout << "User with ID " << userID << " not found." << endl;
}




//  case 6:
//                     int analysisidforcase6;
//                     cout << "Enter Analysis ID: ";
//                     cin >> analysisidforcase6;

//                     int patientidforcase6;
//                     cout << "Enter Patient ID: ";
//                     cin >> patientidforcase6;

//                     // Find the analysis with the provided ID
//                     for (size_t i = 0; i < Analysis::numAnalyses; i++)
//                     {
//                         if (Analysis::allAnalysis[i]->getID() == analysisidforcase6)
//                         {
//                             // Find the patient with the provided ID
//                             for (size_t j = 0; j < Patient::patientCount; j++)
//                             {
//                                 if (Patient::patients[j].getUserInfo().getId() == patientidforcase6)
//                                 {
//                                     // Add the analysis to the patient
//                                     Patient::addAnalysisToPatient(&Patient::patients[j], Analysis::allAnalysis[i]);
//                                     cout << "Add Analysis To Patient Successful" << endl;
//                                     return -1; // Exit function after adding analysis to patient
//                                 }
//                             }

//                             // Patient with the provided ID not found
//                             cout << "Error: Patient with ID " << patientidforcase6 << " not found." << endl;
//                             return -1;
//                         }
//                     }

//                     break;

//                 case 7:
//                     int deviceidforcase7;
//                     cout << "Enter Device ID: ";
//                     cin >> deviceidforcase7;
//                     for (size_t i = 0; i < Device::devices.size(); i++)
//                     {
//                         if (Device::devices[i].getId() == deviceidforcase7)
//                         {
//                             Device::addDevice(Device::devices[i]);
//                             cout << "Add Device Successful" << endl;
//                         }
//                     }
//                     break;