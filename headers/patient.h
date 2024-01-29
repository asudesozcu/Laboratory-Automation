#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include <iostream>
#include <vector>
#include "users.h"
#include "doctor.h"
#include "analysis.h"

using namespace std;
class Patient : public User
{

public:
  User userInfo;
  Analysis *myMedicalAnalysis;
  Doctor *doctor;
  int analysisCount;
  static vector<Patient> patients;

  // Constructors
  Patient();
  Patient(const std::string &username, int id, const std::string &password,
          const std::string &name, const std::string &surname, const std::string &phone);
  // Member functions
  static void getPatientInfo(int patientID);

  static Patient *verifyPatient(const string &inputUsername, const string &inputPassword);
  static void addUserPatient(Patient *patient);

  static void setPatientDoctor(Patient *patient, Doctor *doctor);
  static void addAnalysisToPatient(Patient *patient, Analysis *newAnalysis);

  // Getter ve Setter metotları
  const User &getUserInfo() const;
  void setUserInfo(const User &newUserInfo);

  // Static member functions

  static int patientCount;
  static int patientsCapacity;

  static void addToPatientsList(Patient *existingPatient);
  static Patient createPatient(const string &username, int id, const string &password, const string &name, const string &surname, const string &phone);
  static void removePatientFromList(Patient *patientToRemove);


    void displayInfo() const override; 

};

#endif
