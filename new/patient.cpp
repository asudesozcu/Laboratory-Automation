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

Patient::Patient() : User(), myMedicalAnalysis(nullptr), doctor(nullptr), analysisCount(0) {
}

// Parameterized constructor
Patient::Patient(const string &username, int id, const string &password, const string &name, const string &surname, const string &phone)
    : User(username, name, surname, password, phone, id, false, AccountType::PATIENT),
      myMedicalAnalysis(nullptr), doctor(nullptr), analysisCount(0) {
}


vector<Patient> Patient::patients;
int Patient::patientCount = 0;
int Patient::patientsCapacity = 10;

void getPatientInfo(int patientID) {
    for (size_t i = 0; i < Patient::patientCount; i++) {
        if (Patient::patients[i].userInfo.getId() == patientID) {
            // Print patient information to the console
            std::cout << "Patient Information:" << std::endl;
            std::cout << "Username: " << Patient::patients[i].userInfo.getUsername() << std::endl;
            std::cout << "Password: " << Patient::patients[i].userInfo.getPassword() << std::endl;
            std::cout << "Phone: " << Patient::patients[i].userInfo.getPassword() << std::endl;
            std::cout << "Patient ID: " << Patient::patients[i].userInfo.getId() << std::endl;
        }
    }
}

void Patient::setPatientPassword(User *user, const string &newPassword)
{
    // Eğer yeni bir şifre verildiyse, güncelle
    {
        user->setPassword(newPassword);
    }
}

void Patient::setPatientPhone(User *user, const string &newPhone)
{
    // Eğer yeni bir telefon numarası verildiyse, güncelle
    {
        user->setPhone(newPhone);
    }
}

void Patient::setPatientName(User *user, const string &newName)
{
    // Eğer yeni bir isim verildiyse, güncelle
    {
        user->setName(newName);
    }
}

void Patient::setPatientSurname(User *user, const string &newSurname)
{
    // Eğer yeni bir soyisim verildiyse, güncelle
    {
        user->setSurname(newSurname);
    }
}


void setPatientDoctor(Patient *patient, Doctor *doctor)
{
    // Eğer yeni bir doktor bilgisi verildiyse, güncelle
    if (doctor != nullptr)
    {
        patient->doctor=doctor;
    }
    doctor->addPatient(patient, doctor);
}

void Patient::addToPatientsList(Patient* existingPatient) {
    // If the vector's capacity is insufficient, expand it
    if (patientCount >= patientsCapacity) {
        if (patientsCapacity == 0) {
            patientsCapacity = INITIAL_CAPACITY;
        }
        else {
            patientsCapacity += 10;
        }

        Patient::patients.push_back(*existingPatient);
        patientCount++;
    }
    // Add the existing patient
}

User *user,::createPatient(const std::string &username, int id, const std::string &password, const std::string &name, const std::string &surname, const std::string &phone) {
    // Check if the ID is already taken
    for (const User &user : User::users) {
        if (user.getId() == id) {
            std::cout << "This id is already taken." << std::endl;
            return Patient(); // Returning a default-constructed Patient since the creation failed
        }
    }

    // Create a new patient
    Patient newPatient(username, id, password, name, surname, phone);

    // Add the new patient to the patients list
    Patient::patients.push_back(newPatient); // Assuming 'patients' is a static member of the Patient class

    // Add the new patient to the users list
    User::addUserPatient(&newPatient);

    std::cout << "Patient created!" << std::endl;
    return newPatient;
}

void Patient::removePatientFromList(Patient* patientToRemove) {
    for (size_t i = 0; i < patientCount; ++i) {
        if (&Patient::patients[i] == patientToRemove) {
           Patient:: patients.erase(Patient::patients.begin() + i);
            --patientCount;
            return;
        }
    }

    for (size_t i = 0; i < User::numberOfUsers; ++i) {
        if (User::users[i].getId() == patientToRemove->userInfo.getId()) {
            User::users.erase(User::users.begin() + i);
            User::numberOfUsers--;
            return;
        }
    }

    std::cout << "Patient or user not found." << std::endl;
}

void Patient::addAnalysisToPatient(Patient* patient, Analysis* newAnalysis) {
    // NULL check
    if (patient == nullptr || newAnalysis == nullptr) {
        std::cout << "Invalid arguments for adding analysis to patient." << std::endl;
        return;
    }

    // Allocate memory for the new analysis
    Analysis* temp = new Analysis[patient->analysisCount + 1];

    // Copy existing analyses to the new array
    for (int i = 0; i < patient->analysisCount; ++i) {
        temp[i] = patient->myMedicalAnalysis[i];
    }

    // Add the new analysis
    temp[patient->analysisCount] = *newAnalysis;

    // Increment the analysis count
    ++patient->analysisCount;

    // Deallocate the old array
    delete[] patient->myMedicalAnalysis;

    // Point to the new array
    patient->myMedicalAnalysis = temp;

    std::cout << "Analysis added to the patient successfully." << std::endl;
}