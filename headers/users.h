#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>


using namespace std;

enum class AccountType
{
    PATIENT,
    DOCTOR,
    LABMAN
};

class User
{
public:
    static vector<User> users;
    static int numberOfUsers;
    static int capacity;

    // Constructors
    User(const string &name, const string &surname, const string &username, const string &password, const string &phone, int id, bool isAdmin, AccountType type);
    User();
    // Getter and Setter methods
    static const string accountTypeToString(AccountType type);
    static User* verifyUser(const string &inputUsername, const string &inputPassword);

    // Getter and Setter methods
    const string &getName() const;
    void setName(const string &newName);

    const string &getSurname() const;
    void setSurname(const string &newSurname);

    const string &getUsername() const;
    void setUsername(const string &newUsername);

    const string &getPassword() const;
    void setPassword(const string &newPassword);

    const string &getPhone() const;
    void setPhone(const string &newPhone);

    int getId() const;
    void setId(int newId);

    bool getIsAdmin() const;
    void setIsAdmin(bool newIsAdmin);

    AccountType getAccountType() const;
    void setAccountType(AccountType newType);



    virtual void displayInfo() const {};
    virtual ~User() {}


private:
    string name;
    string surname;
    string username;
    string password;
    string phone;
    int id;
    bool isAdmin;
    
    AccountType type;
};

#endif
