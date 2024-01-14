#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include <iostream>
#include <vector>
#include "users.h" 
#include "doctor.h" 
#include "analysis.h" 

using namespace std;
class Patient : public User {

public:
    User userInfo;
    Analysis *myMedicalAnalysis; // MedicalAnalysis struct'ının bir pointer'ı
    Doctor *doctor;
    int analysisCount;
    static vector<Patient> patients;

    // Constructors
    Patient();
    Patient(const string &username, int id, const string &password, const string &name, const string &surname, const string &phone);

    // Member functions
    static void getPatientInfo(int patientID);
    static Patient *verifyPatient(const string &inputUsername, const string &inputPassword);
    static void addUserPatient(Patient *patient);

    static void setPatientPassword(User *user, const string &newPassword);
    static void setPatientPhone(User *user, const string &newPhone);
    static void setPatientName(User *user, const string &name);
static void setPatientSurname(User *user, const string &newSurname);
    static void setPatientDoctor(User *user, Doctor *doctor);
    static void addAnalysisToPatient(Patient *patient, Analysis *newAnalysis);

    // Getter ve Setter metotları
    const Patient &getUserInfo() const;
    void setUserInfo(const User &newUserInfo);

    // Static member functions

    static int patientCount;
    static int patientsCapacity;

    void addToPatientsList(Patient *existingPatient);
    static Patient createPatient(const string &username, int id, const string &password, const string &name, const string &surname, const string &phone);
    static void removePatientFromList(Patient *patientToRemove);
};

#endif
