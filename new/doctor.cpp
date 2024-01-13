#include <iostream>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include "doctor.h"
#include "users.h"
int doctorsCount = 0;
int doctorsCapacity = 0;
vector<Doctor> doctors;

Doctor::Doctor(const std::string &_title, int _id, const std::string &_name, const std::string &_surname,
               const std::string &_password, const std::string &_username, const std::string &_phone)
    : title(_title), patientCount(0), capacity(0)
{

    for (int i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getId() == _id)
        {
            std::cout << "Hata: This id is already in use." << std::endl;
            return;
        }
    }

    title = _title;
    userInfo.setId(_id);
    userInfo.setName(_name);
    userInfo.setSurname(_surname);
    userInfo.setPassword(_password);
    userInfo.setUsername(_username);
    userInfo.setPhone(_phone);
    userInfo.setAccountType(AccountType::DOCTOR);

    patients = nullptr;
    patientCount = 0;
    capacity = 0;
}

Doctor::~Doctor()
{
    // Bellek temizleme
    delete[] patients;
}

int Doctor::requestBloodAnalysis(int doctorID, int patientID)
{
    Analysis *newAnalysis = new Analysis();

    // Belirtilen doktor ID'sine sahip doktoru bul
    Doctor *doctor = nullptr;
    for (size_t i = 0; i < doctorsCount; ++i)
    {
        if (doctors[i].userInfo.getId() == doctorID)
        {
            doctor = &doctors[i];
            break;
        }
    }

    if (doctor == nullptr)
    {
        std::cout << "Doctor not found with ID " << doctorID << "." << std::endl;
        return 0;
    }

    // Dynamically allocate memory for the patient
    Patient *patient = nullptr;
    for (size_t i = 0; i < Patient::patientCount; ++i)
    {
        if (Patient::patients[i].userInfo.getId() == patientID)
        {
            patient = &Patient::patients[i];
            break;
        }
    }

    if (patient == nullptr)
    {
        std::cout << "Patient not found with ID " << patientID << "." << std::endl;
        return 0;
    }

    // Test adlarını yazdır
    std::cout << "Available blood tests:" << std::endl;
    ExaminationList bloodTests = Analysis::createExaminationList(Analysis::BLOOD);
    for (size_t i = 0; i < bloodTests.count; i++)
    {
        std::cout << i + 1 << ". " << bloodTests.examinations[i] << std::endl;
    }

    // Kullanıcıdan test seçmesini iste
    std::cout << "Select a blood test (1-" << bloodTests.count << "): ";
    size_t selectedTestIndex;
    std::cin >> selectedTestIndex;

    // Seçilen test adını yazdır
    std::cout << "Selected blood test: " << bloodTests.examinations[selectedTestIndex - 1] << std::endl;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Dynamically allocate memory for the date
    char *date = new char[21]; // YYYY-MM-DD HH:MM:SS formatında tarih için 20 karakterlik bir dizi
    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

    // Dynamically allocate memory for the analysis
    if (newAnalysis == nullptr)
    {
        std::cout << "Memory allocation failed" << std::endl;
        delete patient; // Free allocated memory before returning
        delete[] date;
        delete newAnalysis;
        return 0;
    }

    // Dynamically allocate memory for the examination
    newAnalysis->examinationlist = new ExaminationList();
    if (newAnalysis->examinationlist == nullptr)
    {
        std::cout << "Memory allocation failed" << std::endl;
        delete patient; // Free allocated memory before returning
        delete[] date;
        delete newAnalysis;
        return 0;
    }

    newAnalysis->doctor = doctor;
    newAnalysis->date = date;
    newAnalysis->patient = patient;
    newAnalysis->type = Analysis::BLOOD;
    newAnalysis->id = Analysis::numAnalyses + 1;
    std::cout << doctor->userInfo.getName() << " requests blood analysis for Patient ID " << patient->userInfo.getId() << std::endl;

    // Dynamically allocate memory for the examination name
    newAnalysis->examinationlist->examinations = new char *[1];
    newAnalysis->examinationlist->examinations[0] = new char(*(bloodTests.examinations[selectedTestIndex - 1]));

    Analysis::numAnalyses++;
    // Analizi array'e ekle
    Analysis::addAnalysisToList(newAnalysis);
    Patient::addAnalysisToPatient(patient, newAnalysis);
    return newAnalysis->id;
    // Analiz talebini oluştur
    std::cout << doctor->userInfo.getName() << " requests blood analysis for Patient ID " << patient->userInfo.getId() << std::endl;
}

int Doctor::requestUrineAnalysis(int doctorID, int patientID)
{

    Analysis *newAnalysis = new Analysis();

    // Belirtilen doktor ID'sine sahip doktoru bul
    Doctor *doctor = nullptr;
    for (size_t i = 0; i < doctorsCount; ++i)
    {
        if (Doctor::doctors[i].userInfo.getId() == doctorID)
        {
            doctor = &doctors[i];
            break;
        }
    }

    if (doctor == nullptr)
    {
        std::cout << "Doctor not found with ID " << doctorID << "." << std::endl;
        return 0;
    }

    // Dynamically allocate memory for the patient
    Patient *patient = nullptr;
    for (size_t i = 0; i < Patient::patientCount; ++i)
    {
        if (Patient::patients[i].userInfo.getId() == patientID)
        {
            patient = &Patient::patients[i];
            break;
        }
    }

    if (patient == nullptr)
    {
        std::cout << "Patient not found with ID " << patientID << "." << std::endl;
        return 0;
    }

    std::cout << "Available urine tests:" << std::endl;
    ExaminationList urineTests = Analysis::createExaminationList(Analysis::URINE);
    for (size_t i = 0; i < urineTests.count; ++i)
    {
        std::cout << i + 1 << ". " << *(urineTests.examinations[i]) << std::endl; // Dereference the std::string pointer
    }

    // Kullanıcıdan test seçmesini iste
    std::cout << "Select a urine test (1-" << urineTests.count << "): ";
    size_t selectedTestIndex;
    std::cin >> selectedTestIndex;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char date[20]; // YYYY-MM-DD HH:MM:SS formatında tarih için 20 karakterlik bir dizi
    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

    Analysis *newAnalysis = new Analysis();
    if (newAnalysis == nullptr)
    {
        std::cout << "Memory allocation failed" << std::endl;
        return;
    }

    // Convert date to std::string
    std::string dateString = date;

    newAnalysis->doctor = doctor;
    newAnalysis->date = strdup(dateString.c_str()); // Use strdup to convert std::string to char*

    newAnalysis->patient = nullptr;
    newAnalysis->type = Analysis::URINE;

    // Allocate memory for the examinationlist
    newAnalysis->examinationlist = new ExaminationList();
    if (newAnalysis->examinationlist == nullptr)
    {
        std::cout << "Memory allocation failed" << std::endl;
        delete newAnalysis;
        return;
    }

    // Allocate memory for the examinations array
    newAnalysis->examinationlist->examinations = new char *[1];
    newAnalysis->examinationlist->examinations[0] = new char(*(urineTests.examinations[selectedTestIndex - 1])); // Dereference the std::string pointer
    // Alternatively, you can use std::string directly:
    // newAnalysis->examinationlist->examinations[0] = new std::string(urineTests.examinations[selectedTestIndex - 1]);

    std::cout << doctor->getName() << " requests " << *(urineTests.examinations[selectedTestIndex - 1]) << " for Patient ID " << patientID << std::endl;

    // Assuming numAnalyses is a static member variable of the Analysis class
    Analysis::numAnalyses++;
    // Analizi array'e ekle
    Analysis::addAnalysisToList(newAnalysis);
    Patient::addAnalysisToPatient(patient, newAnalysis); // Bu satırı eklemeyi unutmuşsunuz, eklemelisiniz
}

void Doctor::addPatient(Patient *patient, Doctor *doctor)
{
    // Hasta ekleyerek başarılı bir şekilde eklediğimizi gösterir
    // Doktorun hastalar dizisini dinamik olarak genişlet
    if (Patient::patientCount >= Patient::capacity)
    {
        Patient::capacity += 10;
        Patient *newPatients = new Patient[Patient::capacity];
        for (int i = 0; i < Patient::patientCount; ++i)
        {
            Patient::patients[i] = newPatients[i];
        }
        delete[] newPatients;
        Patient::patients[Patient::patientCount++] = *patient;
    }

    // Hasta ekleyerek başarılı bir şekilde eklediğimizi gösterir
    Patient::patients[Patient::patientCount++] = *patient;
    std::cout << "Hasta eklenmiştir." << std::endl;
}
void Doctor::addDoctortoDoctorsArray(Doctor *existingDoctor)
{
    if (doctorsCount >= doctorsCapacity)
    {
        // Doctors vector needs to be resized
        if (doctorsCapacity == 0)
        {
            doctorsCapacity = INITIAL_CAPACITY;
        }
        else
        {
            doctorsCapacity += 2;
        }

        // Resize the doctors vector
        Doctor::doctors.resize(doctorsCapacity);

        // Check for memory allocation failure
        if (Doctor::doctors.data() == nullptr)
        {
            std::cerr << "Problem in memory allocation" << std::endl;
            return;
        }
    }

    // Successfully added the doctor
    Doctor::doctors[doctorsCount++] = *existingDoctor;
}
Doctor Doctor::createDoctor(const std::string &title, int id, const std::string &name, const std::string &surname,
                            const std::string &password, const std::string &username, const std::string &phone)
{
    for (int i = 0; i < User::numberOfUsers; i++)
    {
        if (User::users[i].getId() == id)
        {
            std::cout << "Error: This id is already in use." << std::endl;
            // Hata durumu için boş bir Doctor nesnesi döndür
            Doctor nullDoctor;
            return nullDoctor;
        }
    }

    // Yeni bir Doctor nesnesi oluştur
    Doctor *newDoctor = new Doctor();

    // Kullanıcı bilgilerini ayarla
    newDoctor->userInfo.setId(id);
    newDoctor->userInfo.setName(name);
    newDoctor->userInfo.setSurname(surname);
    newDoctor->userInfo.setPassword(password);
    newDoctor->userInfo.setUsername(username);
    newDoctor->userInfo.setPhone(phone);
    newDoctor->userInfo.setAccountType(AccountType::DOCTOR);
    newDoctor->title = title;

    newDoctor->patients = nullptr;
    newDoctor->patientCount = 0;

    // Yeni doktoru kullanıcı listesine ve doktorlar dizisine ekle
    User::addUserDoctor(newDoctor);
    addDoctortoDoctorsArray(newDoctor);

    return *newDoctor;
}

void Doctor::deletePatient(int patientID)
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (patients[i].userInfo.getId() == patientID)
        {
            // Hasta bulundu, sil
            for (int j = i; j < patientCount - 1; ++j)
            {
                patients[j] = patients[j + 1];
            }
            --patientCount;
            std::cout << "Patient with ID " << patientID << " has been deleted." << std::endl;
            return;
        }
    }

    // Hasta bulunamadı
    std::cout << "Patient with ID " << patientID << " not found." << std::endl;
}

void Doctor::DoctorInfo(const Doctor *doctor)
{
    std::cout << "Doktor Bilgileri:" << std::endl;
    std::cout << "Title: " << doctor->title << std::endl;
    std::cout << "Name: " << doctor->getUserInfo().getName() << std::endl;
    std::cout << "Surname: " << doctor->getUserInfo().getSurname() << std::endl;
    std::cout << "Password: " << doctor->getUserInfo().getPassword() << std::endl;
    std::cout << "Username: " << doctor->getUserInfo().getUsername() << std::endl;
    std::cout << "Phone: " << doctor->getUserInfo().getPhone() << std::endl;
}

void Doctor::printPatientInfo(const Patient *patient)
{
    std::cout << "Patient Information:\n";
    std::cout << "ID: " << patient->getUserInfo().getId() << "\n";
    std::cout << "Name: " << patient->getUserInfo().getName() << "\n";
    std::cout << "Surname: " << patient->getUserInfo().getSurname() << "\n";
    std::cout << "Password: " << patient->getUserInfo().getPassword() << "\n";
    std::cout << "Phone: " << patient->getUserInfo().getPhone() << "\n";
    std::cout << "Doctor: " << (patient->doctor ? patient->doctor->getUserInfo().getName() : "Not available") << "\n";
    std::cout << "\n";
}
void Doctor::printDoctorPatients(const Doctor *doctor)
{
    std::cout << "Doctor's Patients:\n";
    for (int i = 0; i < doctor->patientCount; ++i)
    {
        Doctor::printPatientInfo(&doctor->patients[i]);
    }
}

void Doctor::deleteDoctor(int doctorID) {
    auto it = std::remove_if(doctors.begin(), doctors.end(), [doctorID](const Doctor& doctor) {
        return doctor.getId() == doctorID;
    });

    if (it != doctors.end()) {
        doctors.erase(it, doctors.end());
    } else {
        std::cout << "Doctor with ID " << doctorID << " not found.\n";
    }
}
void Doctor::setDoctorPassword(User *user, const string &newPassword)
{
    // Eğer yeni bir şifre verildiyse, güncelle
    {
        user->setPassword(newPassword);
    }
}

void Doctor::setDoctorPhone(User *user, const string &newPhone)
{
    // Eğer yeni bir telefon numarası verildiyse, güncelle
    {
        user->setPhone(newPhone);
    }
}

void Doctor::setDoctorName(User *user, const string &newName)
{
    // Eğer yeni bir isim verildiyse, güncelle
    {
        user->setName(newName);
    }
}

void Doctor::setDoctorSurname(User *user, const string &newSurname)
{
    // Eğer yeni bir soyisim verildiyse, güncelle
    {
        user->setSurname(newSurname);
    }
}

void Doctor::setDoctorUsername(User *user, const string &_username)
{
    user->setUsername(_username);
}
