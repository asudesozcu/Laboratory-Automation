#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"



Patient::Patient() : User(), myMedicalAnalysis(nullptr), doctor(nullptr), analysisCount(0) {}

Patient::Patient(const string &username, int id, const string &password,
                 const string &name, const string &surname, const string &phone)
     {
    
    for (int i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getId() == id)
        {
            cout << "Hata: This id is already in use." << endl;
            return;
        }
    }

    userInfo.setId(id);
    userInfo.setName(name);
    userInfo.setSurname(surname);
    userInfo.setPassword(password);
    userInfo.setUsername(username);
    userInfo.setPhone(phone);
    userInfo.setAccountType(AccountType::PATIENT);

    
    Patient::addUserPatient(this);
    addToPatientsList(this);

    cout << "Patient created!" << endl;
}

vector<Patient> Patient::patients;
int Patient::patientCount = 0;
int Patient::patientsCapacity = 10;
void Patient::addUserPatient(Patient *patient)
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
void Patient::displayInfo() const
{

    
            // Print patient information to the console
            cout << "Patient Information:" << endl;
            cout << "Username: " << userInfo.getUsername() << endl;
            cout << "Name: " << userInfo.getName() << endl;
            cout << "Surname: " << userInfo.getSurname() << endl;

            cout << "Password: " << userInfo.getPassword() << endl;
            cout << "Phone: " << userInfo.getPhone() << endl;
            cout << "Patient ID: " << userInfo.getId() << endl;
        }
    



void Patient::setPatientDoctor(Patient *patient, Doctor *doctor)
{

 patient->doctor = doctor;  
   Doctor::addPatient(patient, doctor);
           
}

void Patient::addToPatientsList(Patient *existingPatient)
{
    if (patientCount >= patientsCapacity)
    {
        if (patientsCapacity == 0)
        {
            patientsCapacity = INITIAL_CAPACITY;
        }
        else
        {
            patientsCapacity += 10;
        }

        patients.resize(patientsCapacity); 
    }

    Patient::patients.push_back(*existingPatient);
    Patient::patientCount++;
}
Patient *Patient::verifyPatient(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < Patient::patients.size(); ++i)
    {
        if (inputUsername == Patient::patients[i].getUserInfo().getUsername() &&
            inputPassword == Patient::patients[i].getUserInfo().getPassword())
        {
            return &Patient::patients[i]; 
        }
    }

    return nullptr; //not found için
}
Patient Patient::createPatient(const string &username, int id, const string &password, const string &name, const string &surname, const string &phone)
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (User::users[i].getId() == id)
        {
            cout << "This id is already taken." << endl;
            Patient nullp;
            return nullp; 
        }
    }

    Patient *newpatient = new Patient();
    newpatient->userInfo.setName(name);
    newpatient->userInfo.setId(id);
    newpatient->userInfo.setPassword(password);
    newpatient->userInfo.setSurname(surname);
    newpatient->userInfo.setPhone(phone);
    newpatient->userInfo.setAccountType(AccountType::PATIENT);
    newpatient->userInfo.setUsername(username);


    Patient::addUserPatient(newpatient);
    addToPatientsList(newpatient);

    cout << "Patient created!" << endl;
    return *newpatient;
}

void Patient::removePatientFromList(Patient *patientToRemove)
{
    for (size_t i = 0; i < patientCount; ++i)
    {
        if (&Patient::patients[i] == patientToRemove)
        {
            Patient::patients.erase(Patient::patients.begin() + i);
            --patientCount;
            return;
        }
    }

    for (size_t i = 0; i < User::numberOfUsers; ++i)
    {
        if (User::users[i].getId() == patientToRemove->userInfo.getId())
        {
            User::users.erase(User::users.begin() + i);
            User::numberOfUsers--;
            return;
        }
    }

    cout << "Patient or user not found." << endl;
}

void Patient::addAnalysisToPatient(Patient *patient, Analysis *newAnalysis)
{
   

    Analysis *temp = new Analysis[patient->analysisCount + 1];

    // aktar
    for (int i = 0; i < patient->analysisCount; ++i)
    {
        temp[i] = patient->myMedicalAnalysis[i];
    }

    temp[patient->analysisCount] = *newAnalysis;

    ++patient->analysisCount;

    // Deallocateion
    delete[] patient->myMedicalAnalysis;

    patient->myMedicalAnalysis = temp;

    cout << "Analysis added to the patient successfully." << endl;
}
const User &Patient::getUserInfo() const
{
    return userInfo;
}
