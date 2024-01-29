#include <iostream>
#include <string>
#include <vector>
#include "users.cpp"
#include "doctor.cpp"
#include "labworker.cpp"

#include "patient.cpp"
#include "analysis.cpp"

#include "device.cpp"

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
    cout << "11. write analiz to file.\n";
}

void displayMenuforAdmin()
{
    cout << "1. Create Doctor\n";
    cout << "2. Create Lab Worker\n";
    cout << "3. Remove Doctor\n";
    cout << "4. Remove Lab Worker\n";
    cout << "5. Remove Device\n";
    cout << "6. Add New Doctor\n"; // addDoctorToArray
    cout << "7. Set Admin\n";      // setadminlabworker
    cout << "8. Remove Patient\n"; // from the list
    cout << "9. Write Devices to File\n";
    cout << "10. Change your Information\n"; // setname, surname vs.
    cout << "11. Change Account\n";
    cout << "0. Exit\n";
}

void displayMenuforLabWorker()
{
    cout << "1. Create Device\n";
    cout << "2. Update Device Status\n";
    cout << "3. Update Device Status on the document\n";
    cout << "4. Write devices on the document\n";
    cout << "5. Set Analysis Status\n";
cout << "6. Change your Information\n"; // setname, surname vs.
    cout << "7. Change Account\n";
    cout << "0. Exit\n";
}

void displayMenuforPatient()
{
    cout << "1. See Analysis\n";
    cout << "2. See your information\n";
    cout << "3. Choose Doctor\n";
    cout << "4. Write Analysis to File\n";
    cout << "5. Change your Information\n"; // set name, surname, etc.
    cout << "6. Change Account\n";
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
    Patient *p1 = new Patient("a", 32, "b", "asude", "sözcü", "555-1276");

    LabWorker::createLabWorker("lw", 3, "p", "Alice", "Johnson", "555-9876", true);

    LabWorker::createLabWorker("lab_worker1", 123, "lab_worker_password", "Lab", "Worker", "555-1111", false);

    Doctor *d1 = new Doctor(1221, "Ahmet", "Ak", "p", "d", "555-1234");

    Doctor::createDoctor(2, "Jane", "Smith", "pass456", "dr_smith", "555-5678");

    d1->requestBloodAnalysis(1221, 12);

    Device::createDevice(1, "dev1", Device::DeviceStatus::usable);
    Device::createDevice(2, "dev2", Device::DeviceStatus::inUse);
    Device::createDevice(3, "dev3", Device::DeviceStatus::broken);

changeAccount:
    string inputtedUserName;
    string inputtedPassword;
    cout << "To Start Automation Please Enter username: ";
    cin >> inputtedUserName;
    cout << "Enter password: ";
    cin >> inputtedPassword;

    User *authenticatedUser = User::verifyUser(inputtedUserName, inputtedPassword);
    if (authenticatedUser)
    {
        cout << "Account Type: " << static_cast<string>(User::accountTypeToString(authenticatedUser->getAccountType())) << endl;
    }
    else
    {
        cout << "Authentication failed." << endl;
    }
    LabWorker *authenticatedLabWorker;
    if (authenticatedUser != nullptr)
    {

        if (authenticatedUser->getAccountType() == AccountType::LABMAN)
        {
            cout << authenticatedUser->getIsAdmin();

            for (int i = 0; i < LabWorker::labWorkerCount; ++i)
            {
                if (inputtedUserName == LabWorker::labWorkers[i].getUserInfo().getUsername() &&
                    inputtedPassword == LabWorker::labWorkers[i].getUserInfo().getPassword())
                {
                    LabWorker *authenticatedLabWorker = &LabWorker::labWorkers[i];
                }
            }
            int isAdminAsLabWorker;
            cout << "Do you want to continue as admin? (0 for No, 1 for Yes): ";
            cin >> isAdminAsLabWorker;
            if (isAdminAsLabWorker == 1)
            {
                goto jump;
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
                int analysisidforcase5;
                double resultvalueforcase5;

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
                    cout << "Update Device Status Successful\n"
                         << endl;
                    break;
                case 4:
                    Device::writeDevicesToFile(Device::devices);
                    cout << "Write Devices To File Successful\n"
                         << endl;
                    break;
                case 5:

                    cout << "Enter Analysis ID: ";
                    cin >> analysisidforcase5;
                    cout << "Enter result  : ";
                    cin >> resultvalueforcase5;
                    Analysis::setAnalysisStatus(analysisidforcase5, resultvalueforcase5);
                    cout << "Set Analysis Status Successful\n"
                         << endl;
                    break;

                case 6:
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
                        authenticatedUser->setName(newName8);
                        authenticatedLabWorker->userInfo.setName(newName8);

                        cout << "Lab Worker's name updated successfully.\n"
                             << endl;
                        break;

                    case 2:
                        // Set Lab Worker Surname
                        cout << "Enter new surname: ";
                        cin >> newSurname;
                        authenticatedUser->setSurname(newSurname);
                        authenticatedLabWorker->userInfo.setSurname(newSurname);
                        cout << "Lab Worker's surname updated successfully.\n"
                             << endl;
                        break;

                    case 3:
                        // Set Lab Worker Username
                        cout << "Enter new username: ";
                        cin >> newUsername;
                        authenticatedUser->setUsername(newUsername);

                        authenticatedLabWorker->userInfo.setUsername(newUsername);
                        cout << "Lab Worker's username updated successfully.\n"
                             << endl;
                        break;

                    case 4:
                        // Set Lab Worker Password
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        authenticatedUser->setPassword(newPassword);
                        authenticatedLabWorker->userInfo.setPassword(newPassword);
                        cout << "Lab Worker's password updated successfully.\n"
                             << endl;
                        break;

                    default:
                        cout << "Invalid choice for Lab Worker property.\n"
                             << endl;
                        break;
                    }
                }
                break;
                case 7:
                    cout << "Changing account...\n"
                         << endl;
                    goto changeAccount;
                    break;

                case 0:
                    cout << "Exiting the program.\n"
                         << endl;
                    return -1; // Exit the function
                    break;

                default:
                    cout << "Invalid choice. Please enter a valid option.\n"
                         << endl;
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
                    // Dinamik bellekten alan tahsis et
                    authenticatedPatient = new Patient(Patient::patients[i]); // Veya sadece: authenticatedPatient = new Patient();
                                                                              // Değer ataması yapılır.

                    authenticatedPatient = &Patient::patients[i];

                    break; // İlk eşleşmeyi bulduktan sonra döngüyü sonlandırın.
                }
            }

            while (1)
            {
                string nameforcase4, surnameforcase4;
                int analysisID;
                int analysisid;
                displayMenuforPatient();
                int choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                    int analysisIDforcase2_2;

                case 1:
                    cout << "Enter your analysis id: ";
                    cin >> analysisID;

                    for (size_t i = 0; i < Analysis::numAnalyses; i++)
                    {
                        if (Analysis::allAnalysis[i]->getID() == analysisID)
                        {
                            Analysis::printAnalyses(Analysis::allAnalysis[i]);
                        }
                    }
                    break;

                case 2:

                    authenticatedPatient->displayInfo();
                    break;

                case 3:
                    cout << "Write doctor name: ";
                    cin >> nameforcase4;
                    cout << "Write doctor  surname: ";
                    cin >> surnameforcase4;
                    for (size_t i = 0; i < Doctor::doctors.size(); i++)
                    {

                        if (Doctor::doctors[i].userInfo.getName() == nameforcase4 && Doctor::doctors[i].userInfo.getSurname() == surnameforcase4)
                        {
                            Patient::setPatientDoctor(authenticatedPatient, &Doctor::doctors[i]);
                        }
                    }
                    cout<<"Doctor setted\n";
                    break;
                case 4:

                    cout << "Please write analysis id\n";
                    cin >> analysisid;

                    Analysis::writeAnalysisToFile(authenticatedPatient->userInfo.getId(), analysisid);
                    break;

                case 5:
                {
                    string newNameforpatient;
                    string newSurnameforpatient;
                    string newPhoneforpatient;
                    string newPasswordforpatient;

                    int PatientPropertyChoice;
                    displayChangeInfo();
                    cin >> PatientPropertyChoice;

                    switch (PatientPropertyChoice)
                    {
                    case 1:
                        cout << "Enter new name: ";
                        cin >> newNameforpatient;
                        authenticatedPatient->userInfo.setName(newNameforpatient);
                        authenticatedUser->setName(newNameforpatient);
                        cout << "Your name updated successfully." << endl;
                        break;

                    case 2:
                        cout << "Enter new surname: ";
                        cin >> newSurnameforpatient;
                        authenticatedPatient->userInfo.setSurname(newSurnameforpatient);
                        authenticatedUser->setSurname(newSurnameforpatient);

                        cout << "Your surname updated successfully." << endl;
                        break;

                    case 3:
                        cout << "Enter new password: ";
                        cin >> newPasswordforpatient;
                        authenticatedPatient->userInfo.setPassword(newPasswordforpatient);
                        authenticatedUser->setPassword(newPasswordforpatient);
                        cout << "Your password updated successfully." << endl;
                        break;

                    case 4:
                        cout << "Enter new phone: ";
                        cin >> newPhoneforpatient;
                        authenticatedPatient->userInfo.setPhone(newPhoneforpatient);

                        authenticatedUser->setPhone(newPhoneforpatient);

                        cout << "Your phone updated successfully." << endl;
                        break;

                    default:
                        cout << "Invalid choice. Please enter a valid option." << endl;
                        break;
                    }
                }
                break;

                case 6:
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

        else if (authenticatedUser->getAccountType() == AccountType::DOCTOR)
        {
            Doctor *authenticatedDoctor = nullptr;
            for (int i = 0; i < Doctor::doctors.size(); ++i)
            {
                if (inputtedUserName == Doctor::doctors[i].userInfo.getUsername() && inputtedPassword == Doctor::doctors[i].userInfo.getPassword())
                {
                    authenticatedDoctor = &Doctor::doctors[i];

                    // Kontrol et
                    if (authenticatedDoctor->patients.empty())
                    {
                        cout << "Authenticated doctor has no patients." << endl;
                    }
                    else
                    {
                        cout << "Number of patients: " << authenticatedDoctor->patients.size() << endl;
                    }

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
                int analysisid;

                cout << "Enter your choice: ";
                cin >> choicefordoctor;

                switch (choicefordoctor)
                {
                case 1:
                    cout << "Enter patient ID: ";
                    cin >> patientidcase1;
                    Doctor::requestBloodAnalysis(authenticatedUser->getId(), patientidcase1);
                    cout<<"Blood request succesful \n";
                    break;
                case 2:
                    cout << "Enter patient ID: ";
                    cin >> patientidcase2;
                    Doctor::requestUrineAnalysis(authenticatedUser->getId(), patientidcase2);
cout<< "Urine request succesful\n";

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
                   cout<<"Patient created\n";
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
                    cout<<"Patient added\n";
                    break;
                case 5:
                    cout << "Enter Analysis ID: ";
                    cin >> idforcase5;
                    for (size_t i = 0; i < Analysis::numAnalyses; i++)
                    {
                        if (Analysis::allAnalysis[i]->getID() == idforcase5)
                        {

                            Analysis::printAnalyses(Analysis::allAnalysis[i]);
                            break;
                        }
                    }
                    break;
                case 6:
                    authenticatedDoctor->displayInfo();
                    break;
                case 7:
                    cout << "Enter Patient ID: ";
                    cin >> idforcase7;
                    for (size_t i = 0; i < Patient::patientCount; i++)
                    {
                        if (Patient::patients[i].getUserInfo().getId() == idforcase7)
                        {
                            Patient::patients[i].displayInfo();
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
                        authenticatedDoctor->userInfo.setName(newNamefordoctor);
                        authenticatedUser->setName(newNamefordoctor);

                        cout << "Your name updated successfully.\n";
                        break;
                    case 2:
                        cout << "Enter new surname: ";
                        cin >> newSuramefordoctor;
                        authenticatedDoctor->userInfo.setSurname(newSuramefordoctor);
                        authenticatedUser->setSurname(newSuramefordoctor);
                        cout << "Your surname updated successfully.\n";
                        break;
                    case 3:
                        cout << "Enter new username: ";
                        cin >> newUseramefordoctor;
                        authenticatedDoctor->userInfo.setUsername(newUseramefordoctor);
                        authenticatedUser->setUsername(newUseramefordoctor);
                        cout << "Your username updated successfully.\n";
                        break;
                    case 4:
                        cout << "Enter new password: ";
                        cin >> newPasswordfordoctor;
                        authenticatedDoctor->userInfo.setPassword(newPasswordfordoctor);
                        authenticatedUser->setPassword(newPasswordfordoctor);
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
                case 11:
                    cout << "Please write analysis id\n";
                    cin >> analysisid;
                    Analysis::writeAnalysisToFile(authenticatedDoctor->userInfo.getId(), analysisid);
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
        if (authenticatedUser->getIsAdmin())
        {
            while (1)
            {
                displayMenuforAdmin();
                int choiceforadmin;

                cout << "Enter your choice: ";
                cin >> choiceforadmin;
                string nameforcase1;
                int idforcase1;
                string surnameforcase1;
                string passwordforcase1;
                string usernameforcase1;
                string phoneforcase1;
                string usernameforcase2;
                long idforcase2;
                string passwordforcase2;
                string nameforcase2;
                string surnameforcase2;
                string phoneforcase2;
                int DoctorIdcase7;
                int deviceIdcase6;
                int labworkerIdcase5;
                int deviceidtoadd;

                int doctorIdcase4;
                int LabworkerIdcase8;
                int PatientIdcase9;
                int AdminPropertyChoice;
                string newNameforadmin;
                string newSurnameforadmin;
                string newUsernameforadmin;
                string newPasswordforadmin;
                bool isadmin;
                int isadminInput;

                switch (choiceforadmin)
                {
                case 1:

                    // Code for case 1

                    cout << "ID: ";
                    cin >> idforcase1;

                    cout << "Name: ";
                    cin >> nameforcase1;

                    cout << "Surname: ";
                    cin >> surnameforcase1;

                    cout << "Password: ";
                    cin >> passwordforcase1;

                    cout << "Username: ";
                    cin >> usernameforcase1;

                    cout << "Phone: ";
                    cin >> phoneforcase1;

                    Doctor::createDoctor(idforcase1, nameforcase1, surnameforcase1, passwordforcase1, usernameforcase1, phoneforcase1);
                cout<<"Doctor created! \n";

                    break;

                case 2:

                    // Code for case 2

                    cout << "Username: ";
                    cin >> usernameforcase2;

                    cout << "ID: ";
                    cin >> idforcase2;

                    cout << "Password: ";
                    cin >> passwordforcase2;

                    cout << "Name: ";
                    cin >> nameforcase2;

                    cout << "Surname: ";
                    cin >> surnameforcase2;

                    cout << "Phone: ";
                    cin >> phoneforcase2;

                    cout << "Is Admin (1 for true, 0 for false): ";
                    cin >> isadminInput;

                    // Convert the user input to a boolean value
                    isadmin = (isadminInput == 1);

                    LabWorker::createLabWorker(usernameforcase2, idforcase2, passwordforcase2, nameforcase2, surnameforcase2, phoneforcase2, isadmin);
                    break;

                case 3:

                    // Code for case 4

                    cout << "Doctor Id: ";
                    cin >> doctorIdcase4;

                    Doctor::deleteDoctor(doctorIdcase4);
                    break;

                case 4:

                    // Code for case 5

                    cout << "Lab Worker Id: ";
                    cin >> labworkerIdcase5;

                    LabWorker::removeLabWorker(labworkerIdcase5, authenticatedUser->getId());
                   cout<<"Lab Worker Remove\n";
                    break;

                case 5:

                    cout << "Device Id: ";
                    cin >> deviceIdcase6;

                    Device::removeDeviceByAdmin(deviceIdcase6, authenticatedUser->getId());
                    cout<<"Device removed \n";
                    break;

                case 6:

                    cout << "Doctor Id: ";
                    cin >> DoctorIdcase7;

                    for (size_t i = 0; i < Doctor::doctors.size(); i++)
                    {
                        if (Doctor::doctors[i].getUserInfo().getId() == DoctorIdcase7)
                        {
                            Doctor::addDoctortoDoctorsArray(&Doctor::doctors[i]);
                            cout<<"Doctors added\n";
                        }
                    }
                    break;

                case 7:

                    // Code for case 8

                    cout << "Lab Worker Id: ";
                    cin >> LabworkerIdcase8;

                    for (size_t i = 0; i < LabWorker::labWorkerCount; i++)
                    {
                        if (LabWorker::labWorkers[i].getUserInfo().getId() == LabworkerIdcase8)
                        {
                            LabWorker::setLabWorkerAdminStatus(&LabWorker::labWorkers[i], authenticatedUser->getId());
cout<<"Admin status setted \n";                       
                        }
                    }
                    break;

                case 8:

                    // Code for case 9

                    cout << "Patients Id: ";
                    cin >> PatientIdcase9;

                    for (size_t i = 0; i < Patient::patientCount; i++)
                    {
                        if (Patient::patients[i].getUserInfo().getId() == PatientIdcase9)
                        {
                            Patient::removePatientFromList(&Patient::patients[i]);
                            cout<<"Patient removed \n";
                        }
                    }
                    break;

                case 9:

                    // Code for case 10
                    Device::writeDevicesToFile(Device::devices);
                    break;

                case 10:

                    // Code for case 11
                    displayChangeInfo();

                    cin >> AdminPropertyChoice;

                    switch (AdminPropertyChoice)
                    {
                    case 1:

                        // Code for case 11.1
                        cout << "Enter new name: ";
                        cin >> newNameforadmin;
                        authenticatedLabWorker->userInfo.setName(newNameforadmin);
                        authenticatedUser->setName(newNameforadmin);
                        cout << "Your name updated successfully." << endl;
                        break;

                    case 2:

                        // Code for case 11.2
                        cout << "Enter new surname: ";
                        cin >> newSurnameforadmin;
                        authenticatedLabWorker->userInfo.setSurname(newSurnameforadmin);

                        authenticatedUser->setSurname(newSurnameforadmin);
                        cout << "Your surname updated successfully." << endl;
                        break;

                    case 3:

                        // Code for case 11.3
                        cout << "Enter new username: ";
                        cin >> newUsernameforadmin;
                        authenticatedLabWorker->userInfo.setUsername(newUsernameforadmin);
                        authenticatedUser->setUsername(newUsernameforadmin);
                        cout << "Your username updated successfully." << endl;
                        break;

                    case 4:

                        // Code for case 11.4
                        cout << "Enter new password: ";
                        cin >> newPasswordforadmin;
                        authenticatedLabWorker->userInfo.setPassword(newPasswordforadmin);
                        authenticatedUser->setPassword(newPasswordforadmin);
                        cout << "Your password updated successfully." << endl;
                        break;

                    default:

                        cout << "Invalid choice." << endl;
                        break;
                    }
                    break;

                case 11:

                    // Code for case 12
                    cout << "Changing account..." << endl;
                    goto changeAccount;
                    break;

                case 0:

                    // Code for case 0
                    cout << "Exiting the program." << endl;
                    return 0;
                    break;

                default:

                    // Code for default case
                    cout << "Invalid choice." << endl;
                    break;
                }
            }
            printf("Not allowed to use as admin");
        }
    }
    else
    {
        printf("Invalid inputs. Please check your information.\n");
    }
    return 0;
}
