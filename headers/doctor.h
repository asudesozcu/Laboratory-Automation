#ifndef DOCTOR_H
#define DOCTOR_H
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <vector>

#include "users.h"
#include "patient.h"

#include "analysis.h"
using namespace std;
class Doctor : public User
{
public:
  string title;
  static vector<Doctor> doctors;
  vector<Patient *> patients;

  Doctor();
  Doctor(int _id, const string &_name, const string &_surname,
         const string &_password, const string &_username, const string &_phone);

  static void requestBloodAnalysis(int doctorID, int patientID);
  static void requestUrineAnalysis(int doctorID, int patientID);
  static Doctor *verifyDoctor(const string &inputUsername, const string &inputPassword);
  static void addUserDoctor(Doctor *doctor);

  // add a patient to the doctor's list
  static void addPatient(Patient *patient, Doctor *doctor);
  static Doctor createDoctor(int id, const string &name, const string &surname,
                             const string &password, const string &username, const string &phone);
  static void deleteDoctor(int doctorID);

  static void addDoctortoDoctorsArray(Doctor *existingDoctor);

  // Function to delete a patient from the doctor's list
  static void deletePatient(int patientID, Doctor *doctor);

  
  static void printDoctorPatients(Doctor *doctor);

  const User &getUserInfo() const { return userInfo; }

  User userInfo;
  int patientCount;
  static int doctorsCount;
  static int capacity;




    friend void printPatientInfoFromDoctor(const Patient& patient);

    void displayInfo() const override; 


};

#endif // DOCTOR_H
