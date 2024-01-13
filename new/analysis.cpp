#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"

#define INITIAL_CAPACITY 10
using namespace std;

 Analysis::Analysis(){};
    Analysis::Analysis(AnalysisType type, ResultType result, AnalysisStatus status,
                       const string &date, Doctor *doctor, Patient *patient,
                       int id, double resultvalue)
        : type(type), result(result), status(status), date(date), doctor(doctor), patient(patient),
          id(id), resultvalue(resultvalue) {}



// Destructor
Analysis::~Analysis() {
    // Destructor implementation
}

int numAnalyses = 0;
int analysesCapacity = 0;

 const char *bloodExaminations[] = {"WBC", "NEU", "LYM", "MONO", "EOS",
                                   "BASO", "RBC", "HGB", "HCT", "MCV"};

const char *urineExaminations[] = {"Glucose", "Protein", "Bilirubin",
                                   "Urobilinogen", "pH", "Hemoglobin", "Ketone", "Nitrite", "Leukocyte Esterase", "Density"};

#define MIN_TEST_WBC 4.0
#define MAX_TEST_WBC 10.0

#define MIN_TEST_NEU 1.5
#define MAX_TEST_NEU 7.5

#define MIN_TEST_LYM 1.0
#define MAX_TEST_LYM 4.0

#define MIN_TEST_MONO 0.1
#define MAX_TEST_MONO 0.8

#define MIN_TEST_EOS 0.05
#define MAX_TEST_EOS 0.5

#define MIN_TEST_BASO 0.01
#define MAX_TEST_BASO 0.1

#define MIN_TEST_RBC 4.2
#define MAX_TEST_RBC 5.6

#define MIN_TEST_HGB 13.0
#define MAX_TEST_HGB 17.0

#define MIN_TEST_HCT 38.0
#define MAX_TEST_HCT 50.0

#define MIN_TEST_MCV 80.0
#define MAX_TEST_MCV 100.0

#define MIN_TEST_GLUCOSE 70.0
#define MAX_TEST_GLUCOSE 100.0

#define MIN_TEST_PROTEIN 6.0
#define MAX_TEST_PROTEIN 8.3

#define MIN_TEST_BILIRUBIN 0.1
#define MAX_TEST_BILIRUBIN 1.0

#define MIN_TEST_UROBILINOGEN 0.1
#define MAX_TEST_UROBILINOGEN 1.0

#define MIN_TEST_PH 4.5
#define MAX_TEST_PH 8.0

#define MIN_TEST_HEMOGLOBIN 12.0
#define MAX_TEST_HEMOGLOBIN 16.0

#define MIN_TEST_KETONE 0.0
#define MAX_TEST_KETONE 0.5

#define MIN_TEST_NITRITE 0.0
#define MAX_TEST_NITRITE 0.1

#define MIN_TEST_LEUKOCYTE_ESTERASE 0.0
#define MAX_TEST_LEUKOCYTE_ESTERASE 1.0

#define MIN_TEST_DENSITY 1.005
#define MAX_TEST_DENSITY 1.030

double Analysis::MIN_TEST(const std::string &test)
{
    if (test == "WBC")
    {
        return MIN_TEST_WBC;
    }
    else if (test == "NEU")
    {
        return MIN_TEST_NEU;
    }
    else if (test == "DENSITY")
    {
        return MIN_TEST_DENSITY;
    }
    else if (test == "LEUKOCYTE_ESTERASE")
    {
        return MIN_TEST_LEUKOCYTE_ESTERASE;
    }
    else if (test == "NITRITE")
    {
        return MIN_TEST_NITRITE;
    }
    else if (test == "KETONE")
    {
        return MIN_TEST_KETONE;
    }
    else if (test == "HEMOGLOBIN")
    {
        return MIN_TEST_HEMOGLOBIN;
    }
    else if (test == "PH")
    {
        return MIN_TEST_PH;
    }
    else if (test == "UROBILINOGEN")
    {
        return MIN_TEST_UROBILINOGEN;
    }
    else if (test == "BILIRUBIN")
    {
        return MIN_TEST_BILIRUBIN;
    }
    else if (test == "PROTEIN")
    {
        return MIN_TEST_PROTEIN;
    }
    else if (test == "GLUCOSE")
    {
        return MIN_TEST_GLUCOSE;
    }
    else if (test == "MVC")
    {
        return MIN_TEST_MCV;
    }
    else if (test == "LYM")
    {
        return MIN_TEST_LYM;
    }
    else if (test == "HCT")
    {
        return MIN_TEST_HCT;
    }
    else if (test == "HGB")
    {
        return MIN_TEST_HGB;
    }
    else if (test == "RBC")
    {
        return MIN_TEST_RBC;
    }
    else if (test == "BASO")
    {
        return MIN_TEST_BASO;
    }
    else if (test == "EOS")
    {
        return MIN_TEST_EOS;
    }
    else if (test == "MONO")
    {
        return MIN_TEST_MONO;
    }

    // Default case, return a suitable default value (you may want to customize this)
    return 0.0;
}

double Analysis::MAX_TEST(const std::string &test)
{
    if (test == "WBC")
    {
        return MAX_TEST_WBC;
    }
    else if (test == "NEU")
    {
        return MAX_TEST_NEU;
    }
    else if (test == "DENSITY")
    {
        return MAX_TEST_DENSITY;
    }
    else if (test == "LEUKOCYTE_ESTERASE")
    {
        return MAX_TEST_LEUKOCYTE_ESTERASE;
    }
    else if (test == "NITRITE")
    {
        return MAX_TEST_NITRITE;
    }
    else if (test == "KETONE")
    {
        return MAX_TEST_KETONE;
    }
    else if (test == "HEMOGLOBIN")
    {
        return MAX_TEST_HEMOGLOBIN;
    }
    else if (test == "PH")
    {
        return MAX_TEST_PH;
    }
    else if (test == "UROBILINOGEN")
    {
        return MAX_TEST_UROBILINOGEN;
    }
    else if (test == "BILIRUBIN")
    {
        return MAX_TEST_BILIRUBIN;
    }
    else if (test == "PROTEIN")
    {
        return MAX_TEST_PROTEIN;
    }
    else if (test == "GLUCOSE")
    {
        return MAX_TEST_GLUCOSE;
    }
    else if (test == "MVC")
    {
        return MAX_TEST_MCV;
    }
    else if (test == "LYM")
    {
        return MAX_TEST_LYM;
    }
    else if (test == "HCT")
    {
        return MAX_TEST_HCT;
    }
    else if (test == "HGB")
    {
        return MAX_TEST_HGB;
    }
    else if (test == "RBC")
    {
        return MAX_TEST_RBC;
    }
    else if (test == "BASO")
    {
        return MAX_TEST_BASO;
    }
    else if (test == "EOS")
    {
        return MAX_TEST_EOS;
    }
    else if (test == "MONO")
    {
        return MAX_TEST_MONO;
    }

    // Default case, return a suitable default value (you may want to customize this)
    return 0.0;
}
std::ostream &operator<<(std::ostream &os, const Analysis::AnalysisStatus &status)
{
    switch (status)
    {
    case Analysis::AnalysisStatus::INPROGRESS:
        os << "In Progress";
        break;
    case Analysis::AnalysisStatus::TESTCONCLUDED:
        os << "Test Concluded";
        break;
    default:
        os << "Unknown Status";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Analysis::ResultType &resultType)
{
    switch (resultType)
    {
    case Analysis::ResultType::LOW:
        os << "Low";
        break;
    case Analysis::ResultType::NORMAL:
        os << "Normal";
        break;
    case Analysis::ResultType::HIGH:
        os << "High";
        break;
    default:
        os << "Unknown Result Type";
        break;
    }
    return os;
}

void writeAnalysisToFile(int UserID, Analysis *analysize)
{
    if (analysize == nullptr)
    {
        std::cout << "Analysis not found." << std::endl;
        return;
    }

    if (UserID == analysize->doctor->userInfo.getId() || UserID == analysize->getPatient()->getUserInfo().getId())
    {
        if (analysize->getPatient()->getUserInfo().getId() == 0 ||analysize->doctor->userInfo.getId() == 0)
        {
            std::cout << "Patient or doctor has been deleted. Analysis with ID " << analysize->getID() << " cannot be written to file." << std::endl;
            return;
        }

        std::ofstream file("analyses.txt", std::ios::app); // std::ios::app for append mode
        if (!file.is_open())
        {
            std::cerr << "Error opening file" << std::endl;
            return;
        }

        file << "Analysis ID: " << analysize->getID() << "\n";
        file << "Doctor: " << analysize->doctor->userInfo.getName() << " " << analysize->doctor->userInfo.getSurname() << "\n";
        file << "Patient: " << analysize->getPatient()->getUserInfo().getName() << " " << analysize->getPatient()->getUserInfo().getSurname() << " " << analysize->getPatient()->getUserInfo().getId() << "\n";
        file << "Type: " << (analysize->getType() == Analysis::AnalysisType::BLOOD ? "Blood" : "Urine") << "\n";
        file << "Date: " << analysize->getDate() << "\n";
        file << "Result: " << analysize->getResult() << "\n";
        file << "Status: " << analysize->getStatus() << "\n";
        file << "\n";

        file.close();

        std::cout << "Analysis details written to file." << std::endl;
    }
    else
    {
        std::cout << "File is accessible only for doctor and patient." << std::endl;
    }
}
void Analysis::setAnalysisStatus(int analysisid)
{
    for (size_t i = 0; i < numAnalyses; i++)
    {
        if (Analysis::allAnalysis[i]->getID() == analysisid)
        {
            for (size_t k = 0; k < Analysis::allAnalysis[i]->getExaminationList()->getCount(); k++)
            {
                const std::string *currentTest = Analysis::allAnalysis[i]->getExaminationList()->getExaminations()[k];

                double minNormalValue = MIN_TEST(*currentTest); // Dereference the pointer
                double maxNormalValue = MAX_TEST(*currentTest);

                if (Analysis::allAnalysis[i]->getResultValue() < minNormalValue)
                {
                    Analysis::allAnalysis[i]->setResult(Analysis::ResultType::LOW);
                }
                else if (Analysis::allAnalysis[i]->getResultValue() > maxNormalValue)
                {
                    Analysis::allAnalysis[i]->setResult(Analysis::ResultType::HIGH);
                }
                else
                {
                    Analysis::allAnalysis[i]->setResult(Analysis::ResultType::NORMAL);
                }
            }
            std::cout << "Analysis Type for ID " << analysisid << " set successfully." << std::endl;
            return;
        }
    }
    std::cout << "Error: Analysis with ID " << analysisid << " not found." << std::endl;
}

ExaminationList Analysis::createExaminationList(Analysis::AnalysisType analysisType)
{
    ExaminationList list;

    switch (analysisType)
    {
    case Analysis::AnalysisType::BLOOD:
        list.count = 10;
        list.examinations = new const char *[list.count];
        for (size_t i = 0; i < list.count; ++i)
        {
            // const char* türünde dizi elemanı oluştur
            list.examinations[i] = strdup(bloodExaminations[i]);
        }
       
        break;
    case Analysis::AnalysisType::URINE:
        list.count = 10;
        list.examinations = new const char *[list.count];
        for (size_t i = 0; i < list.count; ++i)
        {
            list.examinations[i] = strdup(urineExaminations[i]);
        }
        break;
    default:
        list.examinations = nullptr;
        list.count = 0;
        break;
    }

    return list;
}


void Analysis::printAnalyses(const std::vector<Analysis *> &existingAnalysis)
{
    for (size_t i = 0; i < existingAnalysis.size(); ++i)
    {
        std::cout << "ID: " << existingAnalysis[i]->getID() << std::endl;
        std::cout << "Doctor: " << existingAnalysis[i]->doctor->userInfo.getName() << std::endl;
        std::cout << "Type: " << (existingAnalysis[i]->getType() == Analysis::AnalysisType::BLOOD ? "Blood" : "Urine") << std::endl;
        std::cout << "Date: " << existingAnalysis[i]->getDate() << std::endl;
        std::cout << "Result: " << existingAnalysis[i]->getResult() << std::endl;
        std::cout << "Status: " << existingAnalysis[i]->getStatus() << std::endl;
        std::cout << "Patient: " << existingAnalysis[i]->getPatient()->getUserInfo().getName() << std::endl;
        std::cout << std::endl;
    }
}

void Analysis::addAnalysisToList(Analysis *existingAnalysis)
{
    if (numAnalyses >= analysesCapacity)
    {
        if (analysesCapacity == 0)
        {
            analysesCapacity = INITIAL_CAPACITY;
        }
        else
        {
            analysesCapacity += 2;
        }

        Analysis **newAnalysis = new Analysis *[analysesCapacity];
        if (newAnalysis == nullptr)
        {
            std::cerr << "Memory allocation error" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numAnalyses; i++)
        {
            newAnalysis[i] = Analysis::allAnalysis[i];
        }

        delete[] Analysis::allAnalysis.data();  // Corrected line: use clear() instead of delete[]

        Analysis::allAnalysis.clear();  // Clear the vector before assigning newAnalysis

        Analysis::allAnalysis = std::vector<Analysis *>(newAnalysis, newAnalysis + analysesCapacity);
    }

    existingAnalysis->setID(numAnalyses + 1);
    Analysis::allAnalysis.push_back(existingAnalysis);
    numAnalyses++;

    std::cout << "Analysis has been added to the general list." << std::endl;
}

const std::string &Analysis::getDate() const
{
    return date;
}

void Analysis::setDate(const std::string &newDate)
{
    date = newDate;
}

int Analysis::getID() const
{
    return id;
}

void Analysis::setID(int newID)
{
    id = newID;
}

double Analysis::getResultValue() const
{
    return resultvalue;
}

void Analysis::setResultValue(double newValue)
{
    resultvalue = newValue;
}

ExaminationList *Analysis::getExaminationList() const
{
    return examinationlist;
}

void Analysis::setExaminationList(ExaminationList *newList)
{
    examinationlist = newList;
}

Analysis::AnalysisType Analysis::getType() const
{
    return type;
}

void Analysis::setAnalysisType(AnalysisType newType)
{
    type = newType;
}

Analysis::ResultType Analysis::getResult() const
{
    return result;
}

void Analysis::setResult(ResultType newResult)
{
    result = newResult;
}

Analysis::AnalysisStatus Analysis::getStatus() const
{
    return status;
}

void Analysis::setStatus(AnalysisStatus newStatus)
{
    status = newStatus;
}

Doctor *Analysis::getDoctor() const
{
    return doctor;
}

void Analysis::setDoctor(Doctor *newDoctor)
{
    doctor = newDoctor;
}

Patient *Analysis::getPatient() const
{
    return patient;
}

void Analysis::setPatient(Patient *newPatient)
{
    patient = newPatient;
}