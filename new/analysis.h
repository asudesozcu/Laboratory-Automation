#ifndef ANALYSIS_H
#define ANALYSIS_H
#define INITIAL_CAPACITY 10

#include <vector>
#include <string>
#include <iostream>
#include "doctor.h"
#include "patient.h"
#include "users.h"

using namespace std;
class Doctor;
class Patient;
class ExaminationList
{
public:
    const char **examinations;
    int count;

    // Constructor
    ExaminationList();
    ExaminationList(const vector<string> &exams);

    // Destructor
    ~ExaminationList();

    // Getter for count
    int getCount() const;

    // Getter for examinations
    string **getExaminations() const;
};

class Analysis
{
public:
    static vector<Analysis *> allAnalysis;

    enum AnalysisType
    {
        BLOOD,
        URINE
    };

    enum ResultType
    {
        LOW,
        NORMAL,
        HIGH
    };

    enum AnalysisStatus
    {
        INPROGRESS,
        TESTCONCLUDED
    };

    // Constructors
   Analysis() ;

Analysis(AnalysisType type, ResultType result, AnalysisStatus status,
                   const string &date, Doctor *doctor, Patient *patient,
                   int id, double resultvalue) ;

   
    // Destructor
    ~Analysis();

    // Getters and setters
    const string &getDate() const;
    void setDate(const string &newDate);

    int getID() const;
    void setID(int newID);

    double getResultValue() const;
    void setResultValue(double newValue);

    ExaminationList *getExaminationList() const;
    void setExaminationList(ExaminationList *newList);

    AnalysisType getType() const;
    void setAnalysisType(AnalysisType newType);

    ResultType getResult() const;
    void setResult(ResultType newResult);

    AnalysisStatus getStatus() const;
    void setStatus(AnalysisStatus newStatus);

    Doctor *getDoctor() const;
    void setDoctor(Doctor *newDoctor);

    Patient *getPatient() const;
    void setPatient(Patient *newPatient);

    // Other member functions
    static double MIN_TEST(const string &test);
    static double MAX_TEST(const string &test);

    static void setAnalysisStatus(int analysisid);
    static ExaminationList createExaminationList(Analysis::AnalysisType analysisType);
    static void printAnalyses(const vector<Analysis *> &existingAnalysis);
    static void addAnalysisToList(Analysis *existingAnalysis);
    void writeAnalysisToFile(int UserID, Analysis *analyse);

    AnalysisType type;
    ResultType result;
    AnalysisStatus status;
    string date;
    Doctor *doctor;
    Patient *patient;
    int id;
    double resultvalue;
    ExaminationList *examinationlist;
    static int numAnalyses;
    static int analysesCapacity;
    static const char *bloodExaminations[];
    static const char *urineExaminations[];
};
#endif
