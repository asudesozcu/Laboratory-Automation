#include <iostream>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include "doctor.h"
#include "users.h"
#define INITIAL_CAPACITY 10

vector<Doctor> Doctor::doctors;
int Doctor::capacity = 10;
int Doctor::doctorsCount = 0;

Doctor::Doctor() {}
Doctor::Doctor(int _id, const string &_name, const string &_surname,
               const string &_password, const string &_username, const string &_phone)
    : title("Dr."), patientCount(0)
{

    for (int i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getId() == _id)
        {
            cout << "Hata: This id is already in use." << endl;
            return;
        }
    }

    userInfo.setId(_id);
    userInfo.setName(_name);
    userInfo.setSurname(_surname);
    userInfo.setPassword(_password);
    userInfo.setUsername(_username);
    userInfo.setPhone(_phone);
    userInfo.setAccountType(AccountType::DOCTOR);

    patientCount = 0;
    capacity = 0;

     Doctor::addUserDoctor(this);
    Doctor::addDoctortoDoctorsArray(this);
}



void Doctor::requestBloodAnalysis(int doctorID, int patientID)
{
    Analysis *newAnalysis = new Analysis();

    Doctor *doctor = nullptr;
    for (size_t i = 0; i < doctors.size(); ++i)
    {
        if (doctors[i].userInfo.getId() == doctorID)
        {
            doctor = &doctors[i];
            break;
        }
    }

    if (doctor == nullptr)
    {
        cout << "Doctor not found with ID " << doctorID << "." << endl;
        delete newAnalysis; // Free  memory before returning
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate 
    Patient *patient = nullptr;
    for (size_t i = 0; i < Patient::patientCount; ++i)
    {
        if (Patient::patients[i].getUserInfo().getId() == patientID)
        {
            patient = &Patient::patients[i];
            break;
        }
    }

    if (patient == nullptr)
    {
        cout << "Patient not found with ID " << patientID << "." << endl;
        delete newAnalysis; 
        exit(EXIT_FAILURE);
    }

    cout << "Available blood tests:" << endl;
    ExaminationList bloodTests = Analysis::createExaminationList(Analysis::BLOOD);
    for (size_t i = 0; i < bloodTests.count; i++)
    {
        cout << i + 1 << ". " << bloodTests.examinations[i] << endl;
    }

    cout << "Select a blood test (1-" << bloodTests.count << "): ";
    size_t selectedTestIndex;
    cin >> selectedTestIndex;

    cout << "Selected blood test: " << bloodTests.examinations[selectedTestIndex - 1] << endl;

    time_t t = time(nullptr);
    struct tm tm = *localtime(&t);

    // Dynamically allocate memory for the date
    char *date = new char[21]; 
    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

    if (newAnalysis == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient; 
        delete[] date;
        delete newAnalysis;
    }

    newAnalysis->examinationlist = new ExaminationList();

    if (newAnalysis->examinationlist == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient; 
        delete[] date;
        delete newAnalysis;
        exit(EXIT_FAILURE);
    }


    newAnalysis->examinationlist->examinations = new char *[1];
    newAnalysis->examinationlist->examinations[0] = strdup(Analysis::bloodExaminations[selectedTestIndex]);

    if (newAnalysis->examinationlist->examinations[0] == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient; 
        delete[] date;
        delete newAnalysis->examinationlist;
        delete newAnalysis;
    }

    if (newAnalysis->examinationlist->examinations[0] == nullptr)
    {
        cerr << "Memory allocation failed for examination name" << endl;
        perror("strdup");
        delete patient; 
        delete[] date;
        delete newAnalysis;
        exit(EXIT_FAILURE);
    }
    newAnalysis->doctor = doctor;
    newAnalysis->date = date;
    newAnalysis->patient = patient;
    newAnalysis->type = Analysis::BLOOD;
    newAnalysis->id = Analysis::numAnalyses + 1;
    newAnalysis->status= Analysis::AnalysisStatus::INPROGRESS;
    Analysis::numAnalyses++;


    Analysis::addAnalysisToList(newAnalysis);

    Patient::addAnalysisToPatient(patient, newAnalysis);

    cout << doctor->userInfo.getName() << " requests blood analysis  ID: " << newAnalysis->getID() << endl;
}
void Doctor::requestUrineAnalysis(int doctorID, int patientID)
{

    Analysis *newAnalysis = new Analysis();

    Doctor *doctor = nullptr;
    for (size_t i = 0; i < Doctor::doctors.size(); ++i)
    {
        if (Doctor::doctors[i].userInfo.getId() == doctorID)
        {
            doctor = &doctors[i];
            break;
        }
    }

    if (doctor == nullptr)
    {
        cout << "Doctor not found with ID " << doctorID << "." << endl;
        delete newAnalysis; 
        exit(EXIT_FAILURE);
    }

   
    Patient *patient = nullptr;
    for (size_t i = 0; i < Patient::patientCount; ++i)
    {
        if (Patient::patients[i].getUserInfo().getId() == patientID)
        {
            patient = &Patient::patients[i];
            break;
        }
    }
   if (patient == nullptr)
    {
        cout << "Patient not found with ID " << patientID << "." << endl;
        delete newAnalysis; 
        exit(EXIT_FAILURE);
    }

   cout << "Available urine tests:" << endl;
    ExaminationList urineTests = Analysis::createExaminationList(Analysis::URINE);
    for (size_t i = 0; i < urineTests.count; i++)
    {
        cout << i + 1 << ". " << urineTests.examinations[i] << endl;
    }

    cout << "Select a urine test (1-" << urineTests.count << "): ";
    size_t selectedTestIndex;
    cin >> selectedTestIndex;

    cout << "Selected urine test: " << urineTests.examinations[selectedTestIndex - 1] << endl;

     time_t t = time(nullptr);
    struct tm tm = *localtime(&t);

    char *date = new char[21]; 
    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

     if (newAnalysis == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient; 
                delete[] date;
        delete newAnalysis;
    }
newAnalysis->examinationlist = new ExaminationList();

    if (newAnalysis->examinationlist == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient; 
        delete[] date;
        delete newAnalysis;
        exit(EXIT_FAILURE);
    }
    newAnalysis->examinationlist->examinations = new char *[1];
    newAnalysis->examinationlist->examinations[0] = strdup(Analysis::bloodExaminations[selectedTestIndex]);

    if (newAnalysis->examinationlist->examinations[0] == nullptr)
    {
        cout << "Memory allocation failed" << endl;
        delete patient;
        delete[] date;
        delete newAnalysis->examinationlist;
        delete newAnalysis;
    }

    if (newAnalysis->examinationlist->examinations[0] == nullptr)
    {
        cerr << "Memory allocation failed for examination name" << endl;
        delete patient; 
        delete[] date;
        delete newAnalysis;
        exit(EXIT_FAILURE);
    }
    newAnalysis->doctor = doctor;
    newAnalysis->date = date;
    newAnalysis->patient = patient;
  newAnalysis->type = Analysis::URINE;
    newAnalysis->id = Analysis::numAnalyses + 1;
    newAnalysis->status= Analysis::AnalysisStatus::INPROGRESS;
  Analysis::numAnalyses++;
  Analysis::addAnalysisToList(newAnalysis);

    Patient::addAnalysisToPatient(patient, newAnalysis);
    cout << doctor->userInfo.getName() << " requests urine analysis  ID: " << newAnalysis->getID() << endl;

   
}

void Doctor::addPatient(Patient *patient, Doctor *doctor)
{

    if (doctor->patientCount < doctor->capacity)
    {
        
        doctor->patients.push_back(patient);
        doctor->patientCount++;
    cout << "Patient added." << endl;
    }

    else
    {
        cout << "Error: Patient capacity reached." << endl;
    }
}
void Doctor::deletePatient(int patientID, Doctor* doctor)
{
    for (auto it = doctor->patients.begin(); it != doctor->patients.end(); ++it)
    {
        if ((*it)->userInfo.getId() == patientID)
        {
            it = doctor->patients.erase(it);
            --Patient::patientCount;
            cout << "Patient with ID " << patientID << " has been deleted." << endl;
            return;
        }
    }

    cout << "Patient with ID " << patientID << " not found." << endl;
}
void Doctor::addDoctortoDoctorsArray(Doctor *existingDoctor)
{
    if (doctorsCount >= capacity)
    {
        if (capacity == 0)
        {
            capacity = INITIAL_CAPACITY;
        }
        else
        {
            capacity += 10;
        }
        doctors.resize(capacity);
    }

    doctors.push_back(*existingDoctor);
    doctorsCount++;
}

Doctor Doctor::createDoctor(int id, const string &name, const string &surname,
                            const string &password, const string &username, const string &phone)
{
    for (int i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getId() == id)
        {
            cout << "Error: This id is already in use." << endl;
            Doctor nullDoctor;
            return nullDoctor;
        }
    }

    Doctor *newDoctor = new Doctor();

    newDoctor->userInfo.setId(id);
    newDoctor->userInfo.setName(name);
    newDoctor->userInfo.setSurname(surname);
    newDoctor->userInfo.setPassword(password);
    newDoctor->userInfo.setUsername(username);
    newDoctor->userInfo.setPhone(phone);
    newDoctor->userInfo.setAccountType(AccountType::DOCTOR);
    newDoctor->title = "Dr.";

    newDoctor->patientCount = 0;

    Doctor::addUserDoctor(newDoctor);

    addDoctortoDoctorsArray(newDoctor);

    return *newDoctor;
}



void Doctor::displayInfo() const 
{
    cout << "Doktor Bilgileri:" << endl;
    cout << "Title: " << title << endl;
    cout << "Name: " << getUserInfo().getName() << endl;
    cout << "Surname: " << getUserInfo().getSurname() << endl;
    cout << "Password: " <<getUserInfo().getPassword() << endl;
    cout << "Username: " <<getUserInfo().getUsername() << endl;
    cout << "Phone: " << getUserInfo().getPhone() << endl;
}

void printPatientInfoFromDoctor(const Patient &patient) {
    cout << "  Patient Information:\n";
    cout << "ID: " << patient.getUserInfo().getId() << "\n";
    cout << "Name: " << patient.getUserInfo().getName() << "\n";
    cout << "Surname: " << patient.getUserInfo().getSurname() << "\n";
    cout << "Password: " << patient.getUserInfo().getPassword() << "\n";
    cout << "Phone: " << patient.getUserInfo().getPhone() << "\n";
    cout << "Doctor: " << (patient.doctor ? patient.doctor->getUserInfo().getName() : "Not available") << "\n";
    cout << "\n";
}
void Doctor::printDoctorPatients( Doctor *doctor)
{
                  

    cout << "Doctor's Patients:\n";
    

    for (int i = 0; i < doctor->patientCount; ++i)
    {              
        printPatientInfoFromDoctor(*(doctor->patients[i]));
    }
}

void Doctor::addUserDoctor(Doctor *doctor)
{

    User newUser(doctor->getUserInfo().getName(),
                 doctor->getUserInfo().getSurname(),
                 doctor->getUserInfo().getUsername(),
                 doctor->getUserInfo().getPassword(),
                 doctor->getUserInfo().getPhone(),
                 doctor->getUserInfo().getId(),
                 doctor->getUserInfo().getIsAdmin(),
                 AccountType::DOCTOR);

    User::users.push_back(newUser);
}

Doctor *Doctor::verifyDoctor(const string &inputUsername, const string &inputPassword)
{
    for (size_t i = 0; i < Doctor::doctors.size(); ++i)
    {
        if (inputUsername == Doctor::doctors[i].getUserInfo().getUsername() &&
            inputPassword == Doctor::doctors[i].getUserInfo().getPassword())
        {
            return &Doctor::doctors[i]; 
        }
    }

    return nullptr; 
}
void Doctor::deleteDoctor(int doctorID)
{
    auto it = remove_if(doctors.begin(), doctors.end(), [doctorID](const Doctor &doctor)
                             { return doctor.getId() == doctorID; });

    if (it != doctors.end())
    {
        doctors.erase(it, doctors.end());
    }
    else
    {
        cout << "Doctor with ID " << doctorID << " not found.\n";
    }
}