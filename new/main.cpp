#include <iostream>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"

using namespace std;

void displayMenuforDoctor()
{
    cout << "1. Request Blood Analysis\n";
    cout << "2. Request Urine Analysis\n";
    cout << "3. Create Patient\n";
    cout << "4. Add Patient\n";
    cout << "5. Print Analysis\n";
    cout << "6. See Your Info\n";
    cout << "7. See Patient Info\n";
    cout << "8. See your all patients\n";
    cout << "9. Change your Information\n"; // setname, surname vs.
    cout << "10. Change Account\n";
    cout << "0. Exit\n";
}

void displayMenuforAdmin()
{
    cout << "1. Create Doctor\n";
    cout << "2. Create Lab Worker\n";
    cout << "3. Add Device\n";
    cout << "4. Remove Doctor\n";
    cout << "5. Remove Lab Worker\n";
    cout << "6. Remove Device\n";
    cout << "7. Add New Doctor\n"; // addDoctorToArray
    cout << "8. Set Admin\n";      // setadminlabworker
    cout << "9. Remove Patient\n"; // from the list
    cout << "10. Write Devices to File\n";
    cout << "11. Change your Information\n"; // setname, surname vs.
    cout << "12. Change Account\n";
    cout << "0. Exit\n";
}

void displayMenuforLabWorker()
{
    cout << "1. Create Device\n";
    cout << "2. Update Device Status\n";
    cout << "3. Update Device Status on the document\n";
    cout << "4. Write devices on the document\n";
    cout << "5. Set Analysis Status\n";
    cout << "6. Add Analysis To Patient\n";
    cout << "7. Add New Device\n";          // addDoctorToArray
    cout << "8. Change your Information\n"; // setname, surname vs.
    cout << "9. Change Account\n";
    cout << "0. Exit\n";
}

void displayMenuforPatient()
{
    cout << "1. See Analysis\n";
    cout << "2. See your information\n";
    cout << "3. Choose Doctor\n";
    cout << "4. Change your Information\n"; // set name, surname, etc.
    cout << "5. Change Account\n";
    cout << "0. Exit\n";
}

void displayChangeInfo()
{
    cout << "1. Set Name\n";
    cout << "2. Set Surname\n";
    cout << "3. Set Password\n";
    cout << "4. Set phone\n";
    cout << "0. Exit\n";
}

int main()
{
    Patient::createPatient("jane_smith", 5, "pass987", "Jane", "Smith", "555-5678");

    Patient::createPatient("p1", 12, "p", "Asude", "Sozcu", "551-5678");

    LabWorker::createLabWorker("lw", 3, "p", "Alice", "Johnson", "555-9876");
    LabWorker::createLabWorker("lab_worker1", 123, "lab_worker_password", "Lab", "Worker", "555-1111");

    // Create two doctors
    Doctor::createDoctor("Dr.", 1, "John", "Doe", "p", "d", "555-1234");
    Doctor::createDoctor("Dr.", 2, "Jane", "Smith", "pass4 56", "dr_smith", "555-5678");

    Analysis *newAnalysis = new Analysis;
    ExaminationList *newList = new ExaminationList;
    newList->examinations = &Analysis::bloodExaminations[3];
    newList->count = 1;
    newAnalysis->id = 121;
    newAnalysis->resultvalue = 0.5;
    newAnalysis->type = Analysis::BLOOD;
    newAnalysis->result = Analysis::NORMAL;
    newAnalysis->status = Analysis::INPROGRESS;
    newAnalysis->examinationlist = newList;

    Analysis::addAnalysisToList(newAnalysis);
    Device::createDevice(1, "dev1", Device::DeviceStatus::usable);
    Device::createDevice(2, "dev2", Device::DeviceStatus::inUse);
    Device::createDevice(3, "dev3", Device::DeviceStatus::broken);

changeAccount:
    string inputtedUserName;
    string inputtedPassword;

    printf("To Start Automation Please Enter username: ");
    scanf("%s", inputtedUserName);

    printf("Enter password: ");
    scanf("%s", inputtedPassword);

    User *authenticatedUser = User::verifyUser(inputtedUserName, inputtedPassword);
    if (authenticatedUser != NULL)
    {
        if (authenticatedUser->getAccountType() == AccountType::LABMAN)
        {
            for (int i = 0; i < LabWorker::labWorkerCount; ++i)
            {
                if (inputtedUserName == LabWorker::labWorkers[i].getUserInfo().getUsername() &&
                    inputtedPassword == LabWorker::labWorkers[i].getUserInfo().getPassword())
                {
                    LabWorker *authenticatedLabWorker = &LabWorker::labWorkers[i];
                }
            }
            int isAdminAsLabWorker;
            printf("Do you want to continue as admin? (0 for No, 1 for Yes): ");
            scanf("%d", &isAdminAsLabWorker);
            if (isAdminAsLabWorker == 1)
            {
                //   goto jump;
            }
            while (1)
            {
                displayMenuforLabWorker();
                int choice;
                cout << "Enter your choice: ";
                cin >> choice;
                int deviceid;
                string devicename;
                int tempStatus;

                switch (choice)
                {
                case 1:
                    cout << "Enter Device ID: ";
                    cin >> deviceid;
                    cout << "Enter Device Name: ";
                    cin >> devicename;
                    cout << "Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ";
                    cin >> tempStatus;
                    Device::DeviceStatus inputStatus;
                    switch (tempStatus)
                    {
                    case 0:
                        inputStatus = Device::DeviceStatus::inUse;
                        break;
                    case 1:
                        inputStatus = Device::DeviceStatus::broken;
                        break;
                    case 2:
                        inputStatus = Device::DeviceStatus::usable;
                        break;
                    default:
                        cout << "Please enter a valid value." << endl;
                        break;
                    }
                    Device::createDevice(deviceid, devicename, inputStatus);
                    cout << "Create Device Succesful" << endl;
                    break;
                case 2:
                    int deviceidforcase2;
                    cout << "Enter Device ID: ";
                    cin >> deviceidforcase2;

                    int tempStatusfor2;
                    cout << "Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ";
                    cin >> tempStatusfor2;
                    Device::DeviceStatus inputStatusfor2;

                    switch (tempStatusfor2)
                    {
                    case 0:
                        inputStatusfor2 = Device::DeviceStatus::inUse;
                        break;
                    case 1:
                        inputStatusfor2 = Device::DeviceStatus::broken;
                        break;
                    case 2:
                        inputStatusfor2 = Device::DeviceStatus::usable;
                        break;
                    default:
                        cout << "Please write a valid value" << endl;
                        break;
                    }
                    Device::setDeviceStatus(deviceidforcase2, inputStatusfor2);
                    cout << "Set Device Status Successful" << endl;
                    break;

                case 3:
                    int deviceidforcase3;
                    cout << "Enter Device ID: ";
                    cin >> deviceidforcase3;

                    int tempStatusfor3;
                    cout << "Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ";
                    cin >> tempStatusfor3;
                    Device::DeviceStatus inputStatusfor3;

                    switch (tempStatusfor3)
                    {
                    case 0:
                        inputStatusfor3 = Device::DeviceStatus::inUse;
                        break;
                    case 1:
                        inputStatusfor3 = Device::DeviceStatus::broken;
                        break;
                    case 2:
                        inputStatusfor3 = Device::DeviceStatus::usable;
                        break;
                    default:
                        cout << "Please write a valid value" << endl;
                        break;
                    }

                    Device::updateDeviceStatus(authenticatedUser->getId(), deviceidforcase3, inputStatusfor3);
                    cout << "Update Device Status Successful" << endl;
                    break;
                case 4:
                    Device::writeDevicesToFile(Device::devices);
                    cout << "Write Devices To File Successful" << endl;
                    break;
                case 5:
                    int analysisidforcase5;
                    cout << "Enter Analysis ID: ";
                    cin >> analysisidforcase5;
                    Analysis::setAnalysisStatus(analysisidforcase5);
                    cout << "Set Analysis Status Successful" << endl;
                    break;
                case 6:
                    int analysisidforcase6;
                    cout << "Enter Analysis ID: ";
                    cin >> analysisidforcase6;

                    int patientidforcase6;
                    cout << "Enter Patient ID: ";
                    cin >> patientidforcase6;

                    // Find the analysis with the provided ID
                    for (size_t i = 0; i < Analysis::numAnalyses; i++)
                    {
                        if (Analysis::allAnalysis[i]->getID() == analysisidforcase6)
                        {
                            // Find the patient with the provided ID
                            for (size_t j = 0; j < Patient::patientCount; j++)
                            {
                                if (Patient::patients[j].getUserInfo().getId() == patientidforcase6)
                                {
                                    // Add the analysis to the patient
                                    Patient::addAnalysisToPatient(&Patient::patients[j], Analysis::allAnalysis[i]);
                                    cout << "Add Analysis To Patient Successful" << endl;
                                    return -1; // Exit function after adding analysis to patient
                                }
                            }

                            // Patient with the provided ID not found
                            cout << "Error: Patient with ID " << patientidforcase6 << " not found." << endl;
                            return -1;
                        }
                    }

                    break;

                case 7:
                    int deviceidforcase7;
                    cout << "Enter Device ID: ";
                    cin >> deviceidforcase7;
                    for (size_t i = 0; i < Device::devices.size(); i++)
                    {
                        if (Device::devices[i].getId() == deviceidforcase7)
                        {
                            Device::addDevice(Device::devices[i]);
                            cout << "Add Device Successful" << endl;
                        }
                    }
                    break;

                case 8:
                {
                    int labWorkerPropertyChoice;
                    displayChangeInfo();
                    cin >> labWorkerPropertyChoice;
                    string newName8;
                    string newSurname;
                    string newUsername;
                    string newPassword;

                    switch (labWorkerPropertyChoice)
                    {
                    case 1:
                        // Set Lab Worker Name
                        cout << "Enter new name: ";
                        cin >> newName8;
                        LabWorker::setLabWorkerName(authenticatedUser, newName8);
                        cout << "Lab Worker's name updated successfully." << endl;
                        break;

                    case 2:
                        // Set Lab Worker Surname
                        cout << "Enter new surname: ";
                        cin >> newSurname;
                        LabWorker::setLabWorkerSurname(authenticatedUser, newSurname);
                        cout << "Lab Worker's surname updated successfully." << endl;
                        break;

                    case 3:
                        // Set Lab Worker Username
                        cout << "Enter new username: ";
                        cin >> newUsername;
                        LabWorker::setLabWorkerUsername(authenticatedUser, newUsername);
                        cout << "Lab Worker's username updated successfully." << endl;
                        break;

                    case 4:
                        // Set Lab Worker Password
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        LabWorker::setLabWorkerPassword(authenticatedUser, newPassword);
                        cout << "Lab Worker's password updated successfully." << endl;
                        break;

                    default:
                        cout << "Invalid choice for Lab Worker property." << endl;
                        break;
                    }
                }
                break;
                case 9:
                    cout << "Changing account..." << endl;
                    goto changeAccount;
                    break;

                case 0:
                    cout << "Exiting the program." << endl;
                    return -1; // Exit the function
                    break;

                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
                }
            }
        }

        else if (authenticatedUser->getAccountType() == AccountType::PATIENT)
        {
            Patient *authenticatedPatient = nullptr;
            for (int i = 0; i < Patient::patientCount; ++i)
            {
                if (inputtedUserName == Patient::patients[i].getUserInfo().getUsername() &&
                    inputtedPassword == Patient::patients[i].getUserInfo().getPassword())
                {
                    authenticatedPatient = &Patient::patients[i];
                }
            }

            while (1)
            {
                displayMenuforPatient();
                int choice;
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice)
                {
                    int analysisID;
                    int analysisIDforcase2_2;

                case 1:
                {
                    std::cout << "Enter your analysis id: ";
                    std::cin >> analysisID;

                    for (size_t i = 0; i < Analysis::numAnalyses; i++)
                    {

                        if (Analysis::allAnalysis[i]->getID() == analysisID)
                        {
                            std::vector<Analysis *> analysisVector;
                            analysisVector.push_back(Analysis::allAnalysis[i]);
                            Analysis::printAnalyses(analysisVector);
                        }
                    }
                }
                break;

                case 2:
                    Patient::getPatientInfo(authenticatedUser->getId());
                    break;
                case 3:
                {
                    std::string nameforcase4, surnameforcase4;
                    std::cout << "Write doctor name and surname: ";
                    std::cin >> nameforcase4 >> surnameforcase4;
                    for (size_t i = 0; i < Doctor::doctors.size(); i++)
                    {
                        if (Doctor::doctors[i].userInfo.getName() == nameforcase4 && Doctor::doctors[i].userInfo.getSurname() == surnameforcase4)
                        {
                            Patient::setPatientDoctor(authenticatedUser, &Doctor::doctors[i]);
                        }
                    }
                }
                break;
                case 4:
                {
                    std::string newNameforpatient;
                    std::string newSurnameforpatient;
                    std::string newUsernameforpatient;
                    std::string newPasswordforpatient;

                    int PatientPropertyChoice;
                    displayChangeInfo();
                    std::cin >> PatientPropertyChoice;

                    switch (PatientPropertyChoice)
                    {
                    case 1:
                        std::cout << "Enter new name: ";
                        std::cin >> newNameforpatient;
                        authenticatedUser->setName(newNameforpatient);
                        std::cout << "Your name updated successfully." << std::endl;
                        break;
                    case 2:
                        std::cout << "Enter new surname: ";
                        std::cin >> newSurnameforpatient;
                        authenticatedUser->setSurname(newSurnameforpatient);
                        std::cout << "Your surname updated successfully." << std::endl;
                        break;
                    case 3:
                        std::cout << "Enter new username: ";
                        std::cin >> newUsernameforpatient;
                        authenticatedUser->setUsername(newUsernameforpatient);
                        std::cout << "Your username updated successfully." << std::endl;
                        break;
                    case 4:
                        std::cout << "Enter new password: ";
                        std::cin >> newPasswordforpatient;
                        authenticatedUser->setPassword(newPasswordforpatient);
                        std::cout << "Your password updated successfully." << std::endl;
                        break;
                    case 5:
                        std::cout << "Changing account..." << std::endl;
                        goto changeAccount;
                        break;
                    case 0:
                        std::cout << "Exiting the program." << std::endl;
                        return -1; // Exit the function
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                        break;
                    }
                }
                break;
                }
            }
        }
    }

    else if (authenticatedUser->getAccountType() == AccountType::DOCTOR)
    {
        Doctor *authenticatedDoctor = nullptr;
        for (int i = 0; i < Doctor::doctors.size(); ++i)
        {
            if (inputtedUserName == Doctor::doctors[i].getUserInfo().getUsername() && inputtedPassword == Doctor::doctors[i].getUserInfo().getPassword())
            {
                authenticatedDoctor = &Doctor::doctors[i];
                break;
            }
        }

        while (true)
        {
            displayMenuforDoctor();
            int DoctorPropertyChoice;
            string newNamefordoctor;
            int idforcase7;
            string newSuramefordoctor;
            string newUseramefordoctor;
            string newPasswordfordoctor;
            int idforcase4;
            string usernameforcase3;
            int idforcase3;
            string passwordforcase3;
            string nameforcase3;
            string surnameforcase3;
            string phoneforcase3;
            int patientidcase2;
            int patientidcase1;
            int choicefordoctor;
            int idforcase5;

            cout << "Enter your choice: ";
            cin >> choicefordoctor;

            switch (choicefordoctor)
            {
            case 1:
                cout << "Enter patient ID: ";
                cin >> patientidcase1;
                Doctor::requestBloodAnalysis(authenticatedUser->getId(), patientidcase1);
                break;
            case 2:
                cout << "Enter patient ID: ";
                cin >> patientidcase2;
                Doctor::requestUrineAnalysis(authenticatedUser->getId(), patientidcase2);
                break;
            case 3:
                cout << "Enter username: ";
                cin >> usernameforcase3;

                cout << "Enter ID: ";
                cin >> idforcase3;

                cout << "Enter password: ";
                cin >> passwordforcase3;

                cout << "Enter name: ";
                cin >> nameforcase3;

                cout << "Enter surname: ";
                cin >> surnameforcase3;

                cout << "Enter phone: ";
                cin >> phoneforcase3;
                Patient::createPatient(usernameforcase3, idforcase3, passwordforcase3, nameforcase3, surnameforcase3, phoneforcase3);
                break;
            case 4:
                cout << "Enter patient ID: ";
                cin >> idforcase4;
                for (size_t i = 0; i < Patient::patientCount; i++)
                {
                    if (Patient::patients[i].getUserInfo().getId() == idforcase4)
                    {
                        Doctor::addPatient(&Patient::patients[i], authenticatedDoctor);
                    }
                }
                break;
            case 5:
                cout << "Enter Analysis ID: ";
                cin >> idforcase5;
                for (size_t i = 0; i < Analysis::numAnalyses; i++)
                {
                    if (Analysis::allAnalysis[i]->getID() == idforcase5)
                    {
                        std::vector<Analysis *> analysisVector;
                        analysisVector.push_back(Analysis::allAnalysis[i]);
                        Analysis::printAnalyses(analysisVector);
                        break;
                    }
                }
                break;
            case 6:
                Doctor::DoctorInfo(authenticatedDoctor);
                break;
            case 7:
                cout << "Enter Patient ID: ";
                cin >> idforcase7;
                for (size_t i = 0; i < Patient::patientCount; i++)
                {
                    if (Patient::patients[i].getUserInfo().getId() == idforcase7)
                    {
                        Patient::getPatientInfo(Patient::patients[i].getUserInfo().getId());
                    }
                }
                break;
            case 8:
                Doctor::printDoctorPatients(authenticatedDoctor);
                break;
            case 9:
                displayChangeInfo();
                cin >> DoctorPropertyChoice;

                switch (DoctorPropertyChoice)
                {
                case 1:
                    cout << "Enter new name: ";
                    cin >> newNamefordoctor;
                    LabWorker::setLabWorkerName(authenticatedUser, newNamefordoctor);

                    cout << "Your name updated successfully.\n";
                    break;
                case 2:
                    cout << "Enter new surname: ";
                    cin >> newSuramefordoctor;
                    LabWorker::setLabWorkerSurname(authenticatedUser, newSuramefordoctor);
                    cout << "Your surname updated successfully.\n";
                    break;
                case 3:
                    cout << "Enter new username: ";
                    cin >> newUseramefordoctor;
                    LabWorker::setLabWorkerUsername(authenticatedUser, newUseramefordoctor);
                    cout << "Your username updated successfully.\n";
                    break;
                case 4:
                    cout << "Enter new password: ";
                    cin >> newPasswordfordoctor;
                    LabWorker::setLabWorkerPassword(authenticatedUser, newPasswordfordoctor);
                    cout << "Your password updated successfully.\n";
                    break;
                default:
                    cout << "Invalid choice for Doctor property.\n";
                    break;
                }
                break;
            case 10:
                cout << "Changing account...\n";
                goto changeAccount;
                break;
            case 0:
                cout << "Exiting the program.\n";
                return 0;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
            }
        }
    }
jump:
    if (authenticatedUser && authenticatedUser->getIsAdmin())
    {
        while (true)
        {
            displayMenuforAdmin();
            int choiceforadmin;

            std::cout << "Enter your choice: ";
            std::cin >> choiceforadmin;

            switch (choiceforadmin)
            {
            case 1:
            {
                // Code for case 1
                std::string titleforcase1;
                int idforcase1;
                std::string nameforcase1;
                std::string surnameforcase1;
                std::string passwordforcase1;
                std::string usernameforcase1;
                std::string phoneforcase1;

                std::cout << "Title: ";
                std::cin >> titleforcase1;

                std::cout << "ID: ";
                std::cin >> idforcase1;

                std::cout << "Name: ";
                std::cin >> nameforcase1;

                std::cout << "Surname: ";
                std::cin >> surnameforcase1;

                std::cout << "Password: ";
                std::cin >> passwordforcase1;

                std::cout << "Username: ";
                std::cin >> usernameforcase1;

                std::cout << "Phone: ";
                std::cin >> phoneforcase1;

                Doctor::createDoctor(titleforcase1, idforcase1, nameforcase1, surnameforcase1, passwordforcase1, usernameforcase1, phoneforcase1);
                break;
            }
            case 2:
            {
                // Code for case 2
                std::string usernameforcase2;
                long idforcase2;
                std::string passwordforcase2;
                std::string nameforcase2;
                std::string surnameforcase2;
                std::string phoneforcase2;

                std::cout << "Username: ";
                std::cin >> usernameforcase2;

                std::cout << "ID: ";
                std::cin >> idforcase2;

                std::cout << "Password: ";
                std::cin >> passwordforcase2;

                std::cout << "Name: ";
                std::cin >> nameforcase2;

                std::cout << "Surname: ";
                std::cin >> surnameforcase2;

                std::cout << "Phone: ";
                std::cin >> phoneforcase2;

                LabWorker::createLabWorker(usernameforcase2, idforcase2, passwordforcase2, nameforcase2, surnameforcase2, phoneforcase2);
                break;
            }
            case 3:
            {
                // Code for case 3
                int deviceidtoadd;
                std::cout << "Device Id: ";
                std::cin >> deviceidtoadd;

                for (size_t i = 0; i < Device::devices.size(); i++)
                {
                    if (Device::devices[i].getId() == deviceidtoadd)
                    {
                        Device::addDevice(Device::devices[i]);
                    }
                }
                break;
            }

            case 4:
            {
                // Code for case 4
                int doctorIdcase4;
                std::cout << "Doctor Id: ";
                std::cin >> doctorIdcase4;

                Doctor::deleteDoctor(doctorIdcase4);
                break;
            }

            case 5:
            {
                // Code for case 5
                int labworkerIdcase5;
                std::cout << "Lab Worker Id: ";
                std::cin >> labworkerIdcase5;

                LabWorker::removeLabWorker(labworkerIdcase5, authenticatedUser->getId());
                break;
            }

            case 6:
            {
                // Code for case 6
                int deviceIdcase6;
                std::cout << "Device Id: ";
                std::cin >> deviceIdcase6;

                Device::removeDeviceByAdmin(deviceIdcase6, authenticatedUser->getId());
                break;
            }
            case 7:
            {
                // Code for case 7
                int DoctorIdcase7;
                std::cout << "Doctor Id: ";
                std::cin >> DoctorIdcase7;

                for (size_t i = 0; i < Doctor::doctors.size(); i++)
                {
                    if (Doctor::doctors[i].getUserInfo().getId() == DoctorIdcase7)
                    {
                        Doctor::addDoctortoDoctorsArray(&Doctor::doctors[i]);
                    }
                }
                break;
            }

            case 8:
            {
                // Code for case 8
                int LabworkerIdcase8;
                std::cout << "Lab Worker Id: ";
                std::cin >> LabworkerIdcase8;

                for (size_t i = 0; i < LabWorker::labWorkerCount; i++)
                {
                    if (LabWorker::labWorkers[i].getUserInfo().getId() == LabworkerIdcase8)
                    {
                        LabWorker::setLabWorkerAdminStatus(&LabWorker::labWorkers[i], authenticatedUser->getId());
                    }
                }
                break;
            }

            case 9:
            {
                // Code for case 9
                int PatientIdcase9;
                std::cout << "Patients Id: ";
                std::cin >> PatientIdcase9;

                for (size_t i = 0; i < Patient::patientCount; i++)
                {
                    if (Patient::patients[i].getUserInfo().getId() == PatientIdcase9)
                    {
                        Patient::removePatientFromList(&Patient::patients[i]);
                    }
                }
                break;
            }

            case 10:
            {
                // Code for case 10
                Device::writeDevicesToFile(Device::devices);
                break;
            }

            case 11:
            {
                // Code for case 11
                displayChangeInfo();
                int AdminPropertyChoice;
                std::cin >> AdminPropertyChoice;

                switch (AdminPropertyChoice)
                {
                case 1:
                {
                    // Code for case 11.1
                    std::cout << "Enter new name: ";
                    std::string newNameforadmin;
                    std::cin >> newNameforadmin;
                    LabWorker::setLabWorkerName(authenticatedUser, newNameforadmin);
                    std::cout << "Your name updated successfully." << std::endl;
                    break;
                }
                case 2:
                {
                    // Code for case 11.2
                    std::cout << "Enter new surname: ";
                    std::string newSurnameforadmin;
                    std::cin >> newSurnameforadmin;
                    LabWorker::setLabWorkerSurname(authenticatedUser, newSurnameforadmin);
                    std::cout << "Your surname updated successfully." << std::endl;
                    break;
                }
                case 3:
                {
                    // Code for case 11.3
                    std::cout << "Enter new username: ";
                    std::string newUsernameforadmin;
                    std::cin >> newUsernameforadmin;
                    LabWorker::setLabWorkerUsername(authenticatedUser, newUsernameforadmin);
                    std::cout << "Your username updated successfully." << std::endl;
                    break;
                }
                case 4:
                {
                    // Code for case 11.4
                    std::cout << "Enter new password: ";
                    std::string newPasswordforadmin;
                    std::cin >> newPasswordforadmin;
                    LabWorker::setLabWorkerPassword(authenticatedUser, newPasswordforadmin);
                    std::cout << "Your password updated successfully." << std::endl;
                    break;
                }
                default:
                {
                    std::cout << "Invalid choice." << std::endl;
                    break;
                }
                }
                break;
            }

            case 12:
            {
                // Code for case 12
                std::cout << "Changing account..." << std::endl;
                goto changeAccount;
                break;
            }

            case 0:
            {
                // Code for case 0
                std::cout << "Exiting the program." << std::endl;
                return 0;
                break;
            }

            default:
            {
                // Code for default case
                std::cout << "Invalid choice." << std::endl;
                break;
            }
                return 0;
            }
        }
    }//PARANETZ HATASI MUHTEMEL
