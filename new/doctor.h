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
class Doctor:public User
{
public:
    string title;
    static vector<Doctor> doctors;

    Doctor();
    Doctor(const string &_title, int _id, const string &_name, const string &_surname,
           const string &_password, const string &_username, const string &_phone);

    ~Doctor();

    static int requestBloodAnalysis(int doctorID, int patientID);
   static  int requestUrineAnalysis(int doctorID, int patientID);
    static Doctor *verifyDoctor(const string &inputUsername, const string &inputPassword);
    static void addUserDoctor(Doctor *doctor);

    // Function to add a patient to the doctor's list
    static void addPatient(Patient *patient, Doctor *doctor);
static void deleteDoctor(int doctorID) ;

    static Doctor createDoctor(const string &title, int id, const string &name, const string &surname,
                               const string &password, const string &username, const string &phone);

    static void addDoctortoDoctorsArray(Doctor *existingDoctor);

    // Function to delete a patient from the doctor's list
    void deletePatient(int patientID);

    static void DoctorInfo(const Doctor *doctor);
   static void printPatientInfo(const Patient *patient);
    static void printDoctorPatients(const Doctor *doctor);

    const User &getUserInfo() const { return userInfo; }

    // Function to set doctor's name
    static void setDoctorName(User *user,const string &_name);

    // Function to set doctor's surname
   static  void setDoctorSurname(User *user,const string &_surname);

    // Function to set doctor's password
  static  void setDoctorPassword(User *user,const string &_password);

    // Function to set doctor's username
   static void setDoctorUsername(User *user,const string &_username);

    // Function to set doctor's phone number
   static void setDoctorPhone(User *user,const string &_phone);

    // Doctor's information
    User userInfo;

    // Doctor's patients
    Patient *patients;

    // Number of patients
    int patientCount;

    // Capacity of the patients array
    int capacity;
};

#endif // DOCTOR_H
