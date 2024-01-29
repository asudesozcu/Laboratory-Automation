#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "device.h"
#include "labworker.h"
#include "analysis.h"
vector<Analysis *> Analysis::allAnalysis;

#define INITIAL_CAPACITY 10
using namespace std;
ExaminationList::ExaminationList() : examinations(nullptr), count(0)
{
}

ExaminationList::ExaminationList(vector<string> &exams) : count(exams.size())
{
    examinations = new char *[count];
    for (int i = 0; i < count; ++i)
    {
        examinations[i] = new char[exams[i].size() + 1];
        strcpy(examinations[i], exams[i].c_str());
    }
}

ExaminationList::~ExaminationList()
{
    delete[] examinations;
}
int ExaminationList::getCount() const
{
    return count;
}

char **ExaminationList::getExaminations() const
{
    return examinations;
}

Analysis::Analysis() {}
Analysis::Analysis(AnalysisType type, ResultType result, AnalysisStatus status,
                   const string &date, Doctor *doctor, Patient *patient,
                   int id, double resultvalue)
    : type(type), result(result), status(status), date(date), doctor(doctor), patient(patient),
      id(id), resultvalue(resultvalue) {}


Analysis::~Analysis()
{
}

int Analysis::numAnalyses = 0;
int Analysis::analysesCapacity = 0;

char *Analysis::bloodExaminations[] = {"WBC", "NEU", "LYM", "MONO", "EOS",
                                       "BASO", "RBC", "HGB", "HCT", "MCV"};

char *Analysis::urineExaminations[] = {"Glucose", "Protein", "Bilirubin",
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

double Analysis::MIN_TEST(string &test)
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

return 0;
}

double Analysis::MAX_TEST(string &test)
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
    return 0;
}
ostream &operator<<(ostream &os, const Analysis::AnalysisStatus &status)
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

ostream &operator<<(ostream &os, const Analysis::ResultType &resultType)
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

void Analysis::setAnalysisStatus(int analysisid, double resultvalue)
{
    for (size_t i = 0; i < numAnalyses; i++)
    {
        if (Analysis::allAnalysis[i]->getID() == analysisid)
        {
            Analysis *currentAnalysis = Analysis::allAnalysis[i];
            currentAnalysis->setResult(Analysis::ResultType::NORMAL);


            string currentTest = currentAnalysis->examinationlist->examinations[0];

            double minNormalValue = MIN_TEST(currentTest);
            double maxNormalValue = MAX_TEST(currentTest);
            currentAnalysis->setStatus(AnalysisStatus::TESTCONCLUDED);


            if (resultvalue < minNormalValue)
            {
                currentAnalysis->setResult(Analysis::ResultType::LOW);

            }
            else if (resultvalue > maxNormalValue)
            {
                currentAnalysis->setResult(Analysis::ResultType::HIGH);

            }

            cout << "Analysis Type for ID " << analysisid << " set successfully." << endl;
            return;
        }
    }
}

ExaminationList Analysis::createExaminationList(Analysis::AnalysisType analysisType)
{
    ExaminationList list;

    switch (analysisType)
    {
    case Analysis::AnalysisType::BLOOD:
        list.count = 10;
        list.examinations = new char *[list.count];
        for (size_t i = 0; i < list.count; ++i)
        {
            list.examinations[i] = strdup(bloodExaminations[i]);
        }

        break;
    case Analysis::AnalysisType::URINE:
        list.count = 10;
        list.examinations = new char *[list.count];
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

void Analysis::printAnalyses(Analysis *existingAnalysis)
{

    cout << "ID: " << existingAnalysis->getID() << endl;
    cout << "Doctor: " << existingAnalysis->doctor->userInfo.getName() << endl;
    cout << "Type: " << (existingAnalysis->getType() == Analysis::AnalysisType::BLOOD ? "Blood" : "Urine") << endl;
    cout << "Date: " << existingAnalysis->getDate() << endl;
    cout << "Result: " << existingAnalysis->getResult() << endl;
    cout << "Status: " << existingAnalysis->getStatus() << endl;
    cout << "Patient: " << existingAnalysis->getPatient()->getUserInfo().getName() << endl;
    cout << endl;
}

void Analysis::addAnalysisToList(Analysis *existingAnalysis)
{
    if (Analysis::allAnalysis.size() >= INITIAL_CAPACITY)
    {
        Analysis::allAnalysis.reserve(Analysis::allAnalysis.size() + 2);
    }

    Analysis::allAnalysis.push_back(existingAnalysis);
    cout << "Analysis has been added to the general list." << endl;
}

void Analysis::writeAnalysisToFile(int UserID, int analysisID)
{
    Analysis *analysize = nullptr;

    for (Analysis *analysis : allAnalysis)
    {
        if (analysis->getID() == analysisID)
        {
            analysize = analysis;
            break;
        }
    }

    if (analysize == nullptr)
    {
        cout << "Analysis not found." << endl;
        return;
    }

    if (UserID == analysize->getDoctor()->getUserInfo().getId() || UserID == analysize->getPatient()->getUserInfo().getId())
    {
        ofstream file("analysis_details.txt"); 

        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }

        file << "Analysis ID: " << analysize->getID() << "\n";
        file << "Doctor: " << analysize->getDoctor()->getUserInfo().getName() << " " << analysize->getDoctor()->getUserInfo().getSurname() << "\n";
        file << "Patient: " << analysize->getPatient()->getUserInfo().getName() << " " << analysize->getPatient()->getUserInfo().getSurname() << " " << analysize->getPatient()->getUserInfo().getId() << "\n";
        file << "Type: " << (analysize->getType() == Analysis::AnalysisType::BLOOD ? "Blood" : "Urine") << "\n";
        file << "Date: " << analysize->getDate() << "\n";
        file << "Result: " << analysize->getResult() << "\n";
        file << "Status: " << analysize->getStatus() << "\n";
        file << "\n";

        file.close();

        cout << "Analysis details written to file." << endl;
    }
    else
    {
        cout << "File is accessible only for doctor and patient." << endl;
    }
}

const string &Analysis::getDate() const
{
    return date;
}

void Analysis::setDate(const string &newDate)
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