#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define maxID 15
#define maxSurname 30
#define maxName 25
#define maxFname 25
#define maxMname 25
#define maxRank 10
#define maxCondition 25
#define maxDegree 25
#define maxAddress 30
#define maxCity 25
#define maxPhone 15
#define maxEnable 5
#define maxSubject 30
#define maxClass 10
#define maxPrintLeft 37

void ConsoleColors(int foreGround, int backGround);
void gotoxy(int x, int y);
void drawFrame();
void FontColor(int foreGround);
void label();
void clrRight();
void clrLeft();
void facultyPayments();
void allFacultyPayments();
void teachingServicesCertificate();
void facRemainingHours();
void selfAffirmationForm();
void allSelfAffirmationForm();
void window_one();
void window_three();
void main_window();

void teachingServicesCertificate();


typedef struct faculty{
    int sn;
    char ID[maxID];
    char surname[maxSurname];
    char name[maxName];
    char fname[maxFname];
    char mname[maxMname];
    int db;
    int mb;
    int yb;
    char rank[maxRank];
    char condition [maxCondition];
    char degree[maxDegree];
    char address[maxAddress];
    int aNo;
    char city[maxCity];
    int tk;
    char phone[maxPhone];
    char enable[maxEnable];
    } fac;
fac *kathigites;

typedef struct program{
    int dd;
    int mm;
    int yyyy;
    int trWeek;
    char subject2[maxSubject];
    char lastname2[maxSurname];
    char firstname2[maxName];
    char class2[maxClass];
    int mhours;
    }pro;
pro *programma;

typedef struct assignement{
    char subj[maxSubject];
    char lastname[maxSurname];
    char firstname[maxName];
    char class1[maxClass];
    int fhours;
    }assign;
assign *anathesi;

