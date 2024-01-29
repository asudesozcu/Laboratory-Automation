#ifndef ANALYSIS_H
#define ANALYSIS_H

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
 char **examinations;
    int count;

    // Constructor
    ExaminationList();
    ExaminationList( vector<string> &exams);

    // Destructor
    ~ExaminationList();

    int getCount() const;

     char **getExaminations() const;
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

    static double MIN_TEST( string &test);
    static double MAX_TEST( string &test);

    static void setAnalysisStatus(int analysisid,double resultvalue);
    static ExaminationList createExaminationList(Analysis::AnalysisType analysisType);

    static void printAnalyses(Analysis *existingAnalysis);
    static void addAnalysisToList(Analysis *existingAnalysis);
static void writeAnalysisToFile(int UserID, int analysisID);


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
    static  char *bloodExaminations[];
    static  char *urineExaminations[];
};
#endif
