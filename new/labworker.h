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
    LabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone);

    // Member functions
    void changeDeviceStatus(int deviceID, const string &deviceName);
static void getInfo(const LabWorker *labWorker);

    // Getter ve Setter metotları
    const User &getUserInfo() const { return userInfo; }
static void setLabWorkerAdminStatus(LabWorker *labworker, int userID);

    void setUserInfo(const User &newUserInfo) { userInfo = newUserInfo; }

    // Static member functions
    static int labWorkerCount;
    static int labWorkerCapacity;
    static void createLabWorker(const string &username, long id, const string &password, const string &name, const string &surname, const string &phone);
static void addToWorkersList(const LabWorker *existingWorker);
    static int exists(const string &desiredUsername);
    static LabWorker findLabWorker(int labWorkerId, const string &labWorkerPassword);
    static void removeLabWorker(int labWorkerId, int userId);

    static void setLabWorkerPassword(User *user, const string &password);
    static void setLabWorkerName(User *user, const string &name);
    static void setLabWorkerSurname(User *user, const string &surname);
    static void setLabWorkerUsername(User *user, const string &username);
};

#endif
