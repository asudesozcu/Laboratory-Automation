#ifndef LABWORKER_H
#define LABWORKER_H
#include "users.h"

#include <vector>
#include <iostream>

using namespace std;

class LabWorker: public User
{
public:
    User userInfo;
    static vector<LabWorker> labWorkers;

    // Constructors
    LabWorker();
    LabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone, bool isadmin);

    // Member functions
    void changeDeviceStatus(int deviceID, const string &deviceName);
    static LabWorker *verifyLabWorker(const string &inputUsername, const string &inputPassword);
    static void addUserLabWorker(LabWorker *labWorker);

    // Getter ve Setter metotları
    const User &getUserInfo() const { return userInfo; }
static void setLabWorkerAdminStatus(LabWorker *labworker, int userID);

    void setUserInfo(const User &newUserInfo) { userInfo = newUserInfo; }

    // Static member functions
    static int labWorkerCount;
    static int labWorkerCapacity;
    static void createLabWorker(const std::string &username, long id, const std::string &password, const std::string &name, const std::string &surname, const std::string &phone, bool isAdmin);
static void addToWorkersList( LabWorker *existingWorker);
    static int exists(const string &desiredUsername);
    static LabWorker findLabWorker(int labWorkerId, const string &labWorkerPassword);
    static void removeLabWorker(int labWorkerId, int userId);


  void displayInfo() const override; 



};

#endif
