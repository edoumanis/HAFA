#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "sinartiseis.h"

time_t calendar; //data type for storing system time values
struct tm* cal_info;
char days[3];
char months[3];
char years[5];


void ConsoleColors(int foreGround, int backGround)
{
     WORD wColor = ((backGround & 0x0F) << 4) + (foreGround & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawFrame(){
    int i;
    gotoxy(0,0); //up left corner
    printf("%c",201);
    for(i = 1; i < 110; i++){ //up double line
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(110,0); //up right corner
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(110, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(110, 25); //down right corner
    printf("%c",188);
    for(i = 109; i > 0; i--){ //down double line
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 110; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void FontColor(int foreGround)
{
     WORD wColor;
     //need to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (foreGround & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void label(){
    drawFrame();
    gotoxy(25,2);
    FontColor(9);
    printf("FACULTY RECORD SYSTEM");
    gotoxy(26,3);
    printf("Hellenic Air Force");
    gotoxy(29,4);
    printf("NCO Academy");
    gotoxy(25,24);
    //FontColor(9);
}

void clrRight(){//deletes inputs on right section
int i,j;
for(i=36;i<110;i++){
    for(j=7;j<25;j++){
        gotoxy(i,j);
        printf(" ");
    }
}
}

void clrLeft(){//deletes inputs on left section
int i,j;
    for(i=1;i<35;i++){
        for(j=7;j<25;j++){
            gotoxy(i,j);
            printf(" ");
        }
    }
}

void clrInput(int j){//deletes user's inputs on left section
int i;
    for(i=20;i<35;i++){
        gotoxy(i,j);
        printf(" ");
    }
}

/*int Lines(FILE *f, char* fileName){
        char ch;
        int N = 0;

        f = fopen(fileName, "r");
        while(!feof(f)){ // counts lines of file
            ch = fgetc(f);
            if(ch == '\n'){
                N++;
            }
        }
        return N;
        fclose(f);
}*/

const char * mmToMonth(int m){
    char * minas;
    switch (m){
        case 1:
            minas = "January";
            break;
        case 2:
            minas = "February";
            break;
        case 3:
            minas = "March";
            break;
        case 4:
            minas = "April";
            break;
        case 5:
            minas = "May";
            break;
        case 6:
            minas = "June";
            break;
        case 7:
            minas = "July";
            break;
        case 8:
            minas = "August";
            break;
        case 9:
            minas = "September";
            break;
        case 10:
            minas = "October";
            break;
        case 11:
            minas = "November";
            break;
        case 12:
            minas = "December";
            break;
    }
    return (minas);
}

void facultyPayments(){

    int  i, j, x, flag, year=0, month=0, N, N1, N2, line, sn, l;
    int aNo, tk, db, mb, yb;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], mName[maxMname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char sSurname[maxSurname], c;

    int fhours;
    char subj[maxSubject], lastname[maxSurname], firstname[maxName], class1[maxClass];

    int dd, mm, yyyy, week, mhours, wres=0;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp1, *fp2;

    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if ((strcmp(enable, "+")) == 0) { //counts line only for enabled professors
                    N++;
            }
    }

    kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation only for enable professors
    if (kathigites==NULL){ // check for memory
        printf("There is no enough memory");
        exit (2);
    }
    fseek(fp,0,SEEK_SET); //returns the file position pointer at the begining of the file
    for(i=0; i<N;){ //raise i only if found enable faculty
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if (strcmp(enable, "+") == 0){ //passing files  data into array(only enable faculties)
                kathigites[i].sn = 0;
                strcpy(kathigites[i].ID,ID);
                strcpy(kathigites[i].surname,surname);
                strcpy(kathigites[i].name,name);
                strcpy(kathigites[i].fname,fName);
                strcpy(kathigites[i].mname,mName);
                kathigites[i].db=db;
                kathigites[i].mb=mb;
                kathigites[i].yb=yb;
                strcpy(kathigites[i].rank,rank);
                strcpy(kathigites[i].condition,condition);
                strcpy(kathigites[i].degree,degree);
                strcpy(kathigites[i].address,address);
                kathigites[i].aNo=aNo;
                strcpy(kathigites[i].city,town);
                kathigites[i].tk=tk;
                strcpy(kathigites[i].phone,phone);
                strcpy(kathigites[i].enable,enable);
                ++i;
            }
    }
        fclose(fp);

    do{
        gotoxy(maxPrintLeft, 9);printf("Enter surname:");
        scanf("%s", sSurname);
        int a = strlen(sSurname);//keeps the string length
        line = 7, x=0; sn = 0, flag = -3;
        for(j=0; j<i-1; j++){ // search for faculty
            if (!(strncmp(sSurname, kathigites[j].surname,a))){ // compares the given surname with surnames in the file for the first a letters
                ++x; //counts the same surnames in the file
                ++sn;
                kathigites[j].sn = sn;
                gotoxy(maxPrintLeft,++line);printf("SN: %d - ID:%s",sn, kathigites[j].ID); //if stricmp is true, it types the record
                gotoxy(maxPrintLeft,++line);printf("Fullname:%s %s", kathigites[j].surname, kathigites[j].name);
                line++;

                if (x == 1){
                    flag = j;
                }

                if (x % 5 == 0 ){ //page handles 5 records
                        line = 7; //initialized the first line to 7
                        x = 0;    //initialized the record counter
                        gotoxy(maxPrintLeft,24);printf("Press ENTER key to Continue"); //for viewing next page of records
                        getch();
                        clrRight();
                }

            }
        }
                //gotoxy(maxPrintLeft,23);printf("sn = %d, katyhigites.sn= %d, j = %d",sn, kathigites[9].sn, j);
                //getch();
            if (sn == 0){ //if not found the surname in the record file
                gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (b) for main menu:");
                c = getch();
                clrRight();
                if (c == 'b'){ //back to main menu
                        clrRight();
                        return;
                }
            }
    }while (sn == 0);//while not found the surname

    gotoxy(maxPrintLeft,24);printf("Press <ENTER> key to Continue"); //enter for next input
    getch();

    if (sn == 1){ //if the surname is unique
        strcpy(ID, kathigites[flag].ID);
        strcpy(surname, kathigites[flag].surname);
        strcpy(name, kathigites[flag].name);
    }else{ //if there is more than one same surnames
        clrRight();

        do {
            gotoxy(maxPrintLeft,7);printf("Enter lecture's SN: "); //
            scanf("%d", &sn);//
                for(i=0; i<N;i++){
                        if (sn == kathigites[i].sn){
                            strcpy(surname, kathigites[i].surname);
                            strcpy(name, kathigites[i].name);
                            gotoxy(maxPrintLeft,8);printf("SN: %d - ID:%s",sn, kathigites[i].ID); //if stricmp is true, it types the record
                            gotoxy(maxPrintLeft,9);printf("Fullname:%s %s", kathigites[i].surname, kathigites[i].name);
                            break;
                        }
                    }
                    if (sn != kathigites[i].sn){
                        for (l = 56; l<110; l++){
                            gotoxy(l,7);printf(" ");
                        }
                    gotoxy(maxPrintLeft, 10);printf("Please re-enter SN or press <r> to Return to Main Menu.");
                    c = getch();
                    if (c == 'r'){ //back to main menu
                                clrRight();
                                return;
                        }
                    clrRight();
                }
                }while (sn != kathigites[i].sn);//while the sn is wrong
            }


    fp1 = fopen("assignment.txt", "r");
    if (fp1 == NULL){//checks for errors on opening file
        clrRight();
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N1=0;//initialized line counter
    i=0;
    while (!feof(fp1)){
        fscanf(fp1, "%s %s %s %s %d", subj, lastname, firstname, class1, &fhours);
            if ((!(strcmp(lastname,surname))) &&  (!(strcmp(firstname,name)))){ //scans file for specific surname and name
                N1++; //counts how many times founds the specific surname and name in the file
            }
    }
    if (N1==0){//if there is no record with these items
        gotoxy(maxPrintLeft, 7);printf("The are is no subjects assigned to professor %s %s", surname, name);
        gotoxy(maxPrintLeft, 8);printf("Press any key to continue...");
        getch();
        clrRight();
        return;
    }
    anathesi = (assign*)malloc(N1*sizeof(assign)); //memory allocation
    if (anathesi==NULL){ // check for memory
            printf("There is no enough memory");
            exit (2);
    }
    fseek(fp1,0,SEEK_SET); //returns the file position pointer at the beginning of the file
    for(i=0;i<N1;){
        fscanf(fp1, "%s %s %s %s %d", subj, lastname, firstname, class1, &fhours);
            if ((!(strcmp(lastname,surname))) &&  (!(strcmp(firstname,name)))) {
                strcpy(anathesi[i].subj,subj);
                strcpy(anathesi[i].lastname, lastname);
                strcpy(anathesi[i].firstname, firstname);
                strcpy(anathesi[i].class1,class1);
                anathesi[i].fhours  =  fhours  ;
                i++;
            }
        }
        //clrRight();
    fclose(fp1);



    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }

    clrRight(); i=0;
    N2=0;//initialized line counter
    do{
    gotoxy(maxPrintLeft, 12);printf("Type year(YYYY): ");
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 13);printf("Type month(01-12): ");
    scanf("%d",&month);
        while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name))) && (year == yyyy) && (month == mm)){
                    N2++;
                }
        }
        if (N2 == 0){
            gotoxy(maxPrintLeft, 15);printf("The month or the year is wrong");
            gotoxy(maxPrintLeft, 16);printf("or the professor has not taught the given time.\n");
            gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
            c = getch();
            if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            clrRight();
        }
   }while(N2 == 0);
        programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }
            fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name))) && (year == yyyy) && (month == mm)){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;
                    wres = wres + programma[i].mhours; //add monthly hours
                    i++;
                }
            }
char payFile[40];
FILE *tService;

//sprintf(payFile,"\\\\192.168.1.2\\share\\Payments\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
sprintf(payFile,"%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
tService=fopen(payFile,"w");
    if (tService == NULL){
        gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
        exit(2);
    }
time(&calendar); //system date
cal_info = localtime(&calendar);
strftime(days, 3, "%d", cal_info);
strftime(months, 3, "%m", cal_info);
strftime(years, 5, "%y", cal_info);

fprintf(tService,"\t\t\t  Payments for %d/%d \n",mm,yyyy);
fprintf(tService, "Unit: NCOA \n\n");
fprintf(tService, "Date: %s/%s/%s \n\n", days, months, years);
fprintf(tService, "\t\t\t Statement of Monthly Teaching\n\n");

const char* minas = mmToMonth(mm);

fprintf(tService, "\t 1. It is ensured that %s %s with identification number %s is defined by the F.471/AD.5676/S.1945/3-10-2016/YETHA/GEA/B5/4"
        " decision of the Deputy Minister of National Defense as an %s lecturer at <<Non Commissioned Officer Academy>> and in "
        "%s of %d has completed %d hours of teaching instruction.\n\n", lastname, firstname, ID, condition, minas, yyyy, wres);
fprintf(tService, "\t DATE \t \t SUBJECT \t\tHours\n");
fprintf(tService, "\t ------------------------------------------------\n");
    for (i=0;i<N2;i++){
        fprintf(tService,"\t %d/%-5d \t%-20s \t %d\n", programma[i].dd, programma[i].mm, programma[i].subject2, programma[i].mhours);
    }
fprintf(tService, "\n\t 2. The above %s lecturer holds %s degree.\n\n", condition, degree);
fprintf(tService, "\n\t 3. For the purposes of calculating the rights of the above beneficiary,"
        " the conditions and limitations of Article 2 of Joint Ministerial Decision 2\\245\\003\\3 Aug 08"
        " have been taken into account.\n\n\n");
fprintf(tService, "\t Supervisor \t\t Director \t\t Commander");
fclose(tService);
clrRight();
fclose(fp2);
free(kathigites);
free(anathesi);
free(programma);
}


void allFacultyPayments(){

    int  i, j, flag=0, year=0, month=0, N, N2;
    int aNo, tk, db, mb, yb;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], mName[maxMname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char c;

    char lastname[maxSurname], firstname[maxName];

    int dd, mm, yyyy, week, mhours, wres=0;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp2;

    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if ((strcmp(enable, "+")) == 0) { //counts line only for enabled professors
                    N++;
            }
    }

    kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation only for enable professors
    if (kathigites==NULL){ // check for memory
        printf("There is no enough memory");
        exit (2);
   }
    fseek(fp,0,SEEK_SET); //returns the file position pointer at the begining of the file
    for(i=0; i<N;){ //raise i only if found enable faculty
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if (strcmp(enable, "+") == 0){ //passing files  data into array(only enable faculties)
                kathigites[i].sn = 0;
                strcpy(kathigites[i].ID,ID);
                strcpy(kathigites[i].surname,surname);
                strcpy(kathigites[i].name,name);
                strcpy(kathigites[i].fname,fName);
                strcpy(kathigites[i].mname,mName);
                kathigites[i].db=db;
                kathigites[i].mb=mb;
                kathigites[i].yb=yb;
                strcpy(kathigites[i].rank,rank);
                strcpy(kathigites[i].condition,condition);
                strcpy(kathigites[i].degree,degree);
                strcpy(kathigites[i].address,address);
                kathigites[i].aNo=aNo;
                strcpy(kathigites[i].city,town);
                kathigites[i].tk=tk;
                strcpy(kathigites[i].phone,phone);
                strcpy(kathigites[i].enable,enable);
                ++i;
            }
    }
        fclose(fp);


    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }

    clrRight(); i=0;
    N2=0;//initialized line counter
    do{
    gotoxy(maxPrintLeft, 12);printf("Type year(YYYY): ");
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 13);printf("Type month(01-12): ");
    scanf("%d",&month);
        while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((year == yyyy) && (month == mm)){
                    N2++;
                }
        }
        if (N2 == 0){
            gotoxy(maxPrintLeft, 15);printf("The month or the year is wrong\n.");
            gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
            c = getch();
            if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            clrRight();
        }
   }while(N2 == 0);
        programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }
            fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){

                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((year == yyyy) && (month == mm)){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;
                    wres = wres + programma[i].mhours; //add monthly hours
                    i++;
                }
            }

char payFile[40];
FILE *tService;

//sprintf(payFile,"\\\\192.168.1.2\\share\\Payments\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
sprintf(payFile,"%d_%d.txt", mm, yyyy);
tService=fopen(payFile,"w");
    if (tService == NULL){
        gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
        exit(2);
    }
time(&calendar); //system date
cal_info = localtime(&calendar);
strftime(days, 3, "%d", cal_info);
strftime(months, 3, "%m", cal_info);
strftime(years, 5, "%y", cal_info);


const char* minas = mmToMonth(mm);
int countN, z, y;

countN = 0;
for (i=0;i<N2;i++){// founds duplicate records in programma[]
        for(j=i+1;j<N2;j++){
            if(!(strcmp(programma[i].lastname2,programma[j].lastname2)) && !(strcmp(programma[i].firstname2,programma[j].firstname2))){
                break;
            }
        }


        if (j == N2){ //hit the end of array
            strcpy(lastname, programma[i].lastname2);
            strcpy(firstname, programma[i].firstname2);

            fprintf(tService,"\t\t\t  Payments for %d/%d \n",mm,yyyy);
            fprintf(tService, "Unit: NCOA \n");
            fprintf(tService, "Date: %s/%s/%s \n\n", days, months, years);
            fprintf(tService, "\t\t\t Statement of Monthly Teaching\n\n");

            for (z=0;z<N2;z++){//counts the monthly teaching hours of each trainer
                if (!(strcmp(lastname, programma[z].lastname2)) && (!(strcmp(firstname, programma[z].firstname2)))){
                    countN = countN + programma[z].mhours;
                }
            }

            for (z=0;z<N;z++){//finds the record position in kathigites[]
                if (!(strcmp(lastname, kathigites[z].surname)) && (!(strcmp(firstname, kathigites[z].name)))){
                    flag = z;
                }
            }
            fprintf(tService, "\t 1. It is ensured that %s %s with identification number %s is defined by the F.471/AD.5676/S.1945/3-10-2016/YETHA/GEA/B5/4"
                    " decision of the Deputy Minister of National Defense as an %s lecturer at <<Non Commissioned Officer Academy>> and in "
                    "%s of %d has completed %d hours of teaching instruction.\n\n", lastname, firstname, kathigites[flag].ID, kathigites[flag].condition, minas, yyyy, countN);
            fprintf(tService, "\t DATE \t SUBJECT \t\t\tHOURS\n");
            fprintf(tService, "\t -----------------------------------------\n");

               for (y=0;y<N2;y++){

                    if ((!strcmp(programma[y].firstname2,firstname)) && (!strcmp(programma[y].lastname2,lastname))){
                        fprintf(tService,"\t %d/%-5d \t%-20s \t %d\n", programma[y].dd, programma[y].mm, programma[y].subject2, programma[y].mhours);
                    }
                }

            fprintf(tService, "\n\t 2. The above %s lecturer holds %s degree.\n", kathigites[flag].condition, kathigites[flag].degree);
            fprintf(tService, "\n\t 3. For the purposes of calculating the rights of the above beneficiary,"
                    " the conditions and limitations of Article 2 of Joint Ministerial Decision 2\\245\\003\\3 Aug 08"
                    " have been taken into account.\n\n");
            fprintf(tService, "\t Supervisor \t\t Director \t\t Commander\n\n \f");
            countN = 0;
        }
}
clrRight();

fclose(tService);
fclose(fp2);

free(kathigites);
free(anathesi);
free(programma);
}


void teachingServicesCertificate(){

    int  i, j, x, flag=-3, flag1=0, N, N2, line, sn;
    int aNo, tk, db, mb, yb;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], mName[maxMname],rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char sSurname[maxSurname], c;
    int dd, mm, yyyy, week, mhours, countHH;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp2;

    clrRight();
    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file faculties.txt");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
         fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
        N++;//counts the number of faculties
    }
    kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation
    if (kathigites == NULL){ // check for memory
        printf("There is no enough memory");
        exit (2);
    }
    fseek(fp,0,SEEK_SET); //returns the file position pointer at the begining of the file
    for(i=0; i<N;i++){
         fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
        kathigites[i].sn = 0;
        strcpy(kathigites[i].ID,ID);
        strcpy(kathigites[i].surname,surname);
        strcpy(kathigites[i].name,name);
        strcpy(kathigites[i].fname,fName);
        strcpy(kathigites[i].mname,mName);
        kathigites[i].db=db;
        kathigites[i].mb=mb;
        kathigites[i].yb=yb;
        strcpy(kathigites[i].rank,rank);
        strcpy(kathigites[i].condition,condition);
        strcpy(kathigites[i].degree,degree);
        strcpy(kathigites[i].address,address);
        kathigites[i].aNo=aNo;
        strcpy(kathigites[i].city,town);
        kathigites[i].tk=tk;
        strcpy(kathigites[i].phone,phone);
        strcpy(kathigites[i].enable,enable);
    }
    fclose(fp);

    do{
        gotoxy(maxPrintLeft, 9);printf("Enter surname:");
        scanf("%s", sSurname);
        int a = strlen(sSurname);//keeps the string length
        line = 7, x=0; sn = 0, flag = -3;
        //clrRight();
            for(j=0; j<i-1; j++){ // search for faculty
                if (!(strncmp(sSurname, kathigites[j].surname,a))){ // compares the given surname with surnames in the file for the first a letters){ // compares the given surname with surnames in the file
                    ++x; //counts the same surnames in the file
                    ++sn;
                    kathigites[j].sn = sn;
                    gotoxy(maxPrintLeft,++line);printf("SN: %d - ID:%s",sn, kathigites[j].ID); //if stricmp is true, it types the record
                    gotoxy(maxPrintLeft,++line);printf("Fullname:%s %s", kathigites[j].surname, kathigites[j].name);
                    line++;

                    if (x == 1){
                        flag = j;
                    }
                    if (x % 5 == 0 ){ //page handles 5 records
                        line = 7; //initialized the first line to 7
                        x = 0;    //initialized the record counter
                        gotoxy(maxPrintLeft,24);printf("Press ENTER key to Continue"); //for viewing next page of records
                        getch();
                        clrRight();
                    }
                }
            }

            if (sn == 0){ //if not found the surname in the record file
                gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (r) for main menu:");
                c = getch();
                clrRight();
                if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                }
            }

    }while (sn == 0);//while not found the surname in the file

            gotoxy(maxPrintLeft,24);printf("Press <ENTER> key to Continue"); //enter for next input
            getch();

            //clrRight();
            if (sn == 1){ //if the surname is unique
                strcpy(ID, kathigites[flag].ID);
                strcpy(surname, kathigites[flag].surname);
                strcpy(name, kathigites[flag].name);
            }else{
                clrRight();
                do {
                    gotoxy(maxPrintLeft,7);printf("Enter lecture's SN: "); //
                    scanf("%d", &sn);//
                    for(i=0; i<N;i++){
                        if (sn == kathigites[i].sn){
                            strcpy(surname, kathigites[i].surname);
                            strcpy(name, kathigites[i].name);
                            //gotoxy(maxPrintLeft,8);printf("SN: %d - ID:%s",sn, kathigites[i].ID); //if stricmp is true, it types the record
                            //gotoxy(maxPrintLeft,9);printf("Fullname:%s %s", kathigites[i].surname, kathigites[i].name);
                            break;
                        }
                    }
                }while (sn != kathigites[i].sn);//while the sn is wrong
            }

    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
        //clrRight();
        i=0;

        N2=0;//initialized line counter
            while (!feof(fp2)){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &week, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
                    if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name)))){
                        ++N2;
                    //gotoxy(maxPrintLeft, 15);printf("N2 = %d", N2);
                    }
            }
            programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }
            fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name)))){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    //strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;
                    //wres = wres + programma[i].mhours; //add monthly hours
                    i++;
                }
            }

char teachingService[40];
FILE *tService;

//sprintf(teachingService,"\\\\192.168.1.3\\share\\tService\\%s_%s.txt", lastname2, firstname2);
sprintf(teachingService,"%s_%s.txt", lastname2, firstname2);
tService=fopen(teachingService,"w");
if (tService == NULL){
        gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
        exit(2);
}

time(&calendar); //system date
cal_info = localtime(&calendar);
strftime(days, 3, "%d", cal_info);
strftime(months, 3, "%m", cal_info);
strftime(years, 5, "%y", cal_info);
clrRight();
fprintf(tService, "\t\t\t\t\t\tNon-Commissioned Officers Academy\n");
fprintf(tService, "\t\t\t\t\t\tEducation Support Division\n");
fprintf(tService, "\t\t\t\t\t\tTel:+302109999999\n");
fprintf(tService, "\t\t\t\t\t\tDekeleia, %s/%s/%s \n\n\n\n", days, months, years);
fprintf(tService,"\t\t\t Certificate of Teaching Service \n\n");

fprintf(tService, "\t Assured that %s %s %s, taught at the Non-Commissioned Officers Academy,"
        "as a %s, the following lessons with the corresponding per year and month, hours: \n\n", kathigites[flag1].rank, lastname2, firstname2, kathigites[flag1].condition);
    for (i=0;i<N2;i++){
        for(j=i+1;j<N2;j++){
            if (!(strcmp(programma[i].subject2, programma[j].subject2))){
                break;
            }
        }
        if (j == N2){
            fprintf(tService, "%20s \n", programma[i].subject2);
        }
    }
fprintf(tService, "\t ------------------------------------------------------\n");
fprintf(tService,"\t %-17s %10s %8s %8s\n", "MONTH", "YEAR", "HOURS", "COMINGS");
fprintf(tService, "\t ------------------------------------------------------\n");

    int countSynHH = 0, comingsSyn = 0, comings=0;;
    countHH = programma[0].mhours;

    for(i = 0; i < N2; i++) {
        for(j = i+1; j < N2; j++) {
            if((programma[i].mm == programma[j].mm) && (programma[i].yyyy == programma[j].yyyy)){
               //finds duplicate elements
               countHH =  countHH + programma[j].mhours;
               ++comings;
               break;
            }
        }

        //Hit the end of the array
        if(j == N2)
        {
           fprintf(tService,"\t %-17s %10d %6d %8d\n", mmToMonth(programma[i].mm), programma[i].yyyy, countHH, comings);
           fprintf(tService, "\t ------------------------------------------------------\n");
            countSynHH = countSynHH + countHH;//total teaching hours
            comingsSyn = comingsSyn + comings;//total comings
            countHH = programma[i+1].mhours;//initialized counter of month hours
            comings = 0; //initialized month comings
        }
    }
    fprintf(tService,"\t %-17s %17d %8d\n", "TOTAL:", countSynHH, comingsSyn);
    fprintf(tService, "\t ------------------------------------------------------\n");

fprintf(tService, "\n\n\t Supervisor \t\t Director \t\t Commander");
fclose(tService);

free(kathigites);
free(anathesi);
free(programma);

}


void facRemainingHours(){
FILE *fp1, *fp2;
int N1, N2, i, j, z, y, k, countHHH = 0, *anathesiFlag;

int fhours;
char subj[maxSubject], lastname[maxSurname], firstname[maxName], class1[maxClass];

int dd, mm, yyyy, week, mhours, wres=0;
char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];



 fp1 = fopen("assignment.txt", "r");
 fp2 = fopen("program.txt", "r");
    if ((fp1 == NULL) || (fp2 == NULL)){//checks for errors on opening file
        clrRight();
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N1=0;
    N2=0;   //initialized line counters
    while (!feof(fp1)){
        fscanf(fp1, "%s %s %s %s %d", subj, lastname, firstname, class1, &fhours);
                N1++; //counts the records of the file

    }
     //memory allocation
    while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                    N2++;//counts the records of the file
    }
    anathesi = (assign*)malloc(N1*sizeof(assign));
    programma = (pro*)malloc(N2*sizeof(pro));
    if ((anathesi==NULL) || (programma==NULL)){ // check for memory
            printf("There is no enough memory");
            exit (2);
    }
    fseek(fp1,0,SEEK_SET); //returns the file position pointer at the beginning of the file
    fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
    for(i=0;i<N1;i++){
        fscanf(fp1, "%s %s %s %s %d", subj, lastname, firstname, class1, &fhours);
                strcpy(anathesi[i].subj,subj);
                strcpy(anathesi[i].lastname, lastname);
                strcpy(anathesi[i].firstname, firstname);
                strcpy(anathesi[i].class1,class1);
                anathesi[i].fhours  =  fhours;
    }
    for(i=0;i<N2;i++){
        fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &week, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
                programma[i].dd  =  dd;
                programma[i].mm  =  mm;
                programma[i].yyyy  =  yyyy;
                strcpy(programma[i].subject2,subj2);
                strcpy(programma[i].lastname2, lastname2);
                strcpy(programma[i].firstname2, firstname2);
                strcpy(programma[i].class2,class2);
                programma[i].mhours  =  mhours;
                wres = wres + programma[i].mhours; //add monthly hours

    }

    fclose(fp1);
    fclose(fp2);

    char payFile[40];
    FILE *tService;

    time(&calendar); //system date
    cal_info = localtime(&calendar);
    strftime(days, 3, "%d", cal_info);
    strftime(months, 3, "%m", cal_info);
    strftime(years, 5, "%Y", cal_info);

    //sprintf(payFile,"\\\\192.168.1.2\\share\\Payments\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
    sprintf(payFile,"remaining_%s_%s_%s.txt", days, months, years);
    tService=fopen(payFile,"w");
        if (tService == NULL){
            gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
            exit(2);
        }

    anathesiFlag = calloc(N2, sizeof(int)*N2);
    for (z=0;z<N2;z++){
                    countHHH = programma[z].mhours;
                    for(y=z+1;y<N2;y++){ //vriskei tin mia ana eidos eggrafi
                        if ((!(strcmp(programma[z].class2, programma[y].class2))) && (!(strcmp(programma[z].subject2, programma[y].subject2))))
                        {
                            countHHH = countHHH + programma[y].mhours; //prosthetei tis wres
                            anathesiFlag[y] = -1; //gia na min tin xanametrisei
                        }
                    }
                    if (anathesiFlag[z] != -1)
                    {
                        anathesiFlag[z] = countHHH;
                        countHHH = 0;
                    }
                }

    fprintf(tService, "Unit: NCOA \n");
    fprintf(tService, "Date: %s/%s/%s \n\n", days, months, years);
    fprintf(tService, "\t\t\t Management of Teaching Hours\n\n");

    for (i=0;i<N1;i++){
        for (j=i+1;j<N1;j++){
            if ((!(strcmp(anathesi[i].class1,anathesi[j].class1)))){
                break;
            }
        }
        if (j == N1){
                fprintf(tService, "%s\n", anathesi[i].class1);
                fprintf(tService, "%-19s %-17s %5s %5s %5s %8s\n", "PROFESSOR",  "SUBJECT", "HOURS", "EXEC",  "REM", "PERC");
                fprintf(tService, "------------------------------------------------------------------\n");
                 for (k=0;k<N1-1;k++){
                    if ((!(strcmp(anathesi[i].class1, anathesi[k].class1)))){
                        for (z=0;z<N2;z++){
                                if ((!(strcmp(anathesi[i].class1, programma[z].class2))) && (!(strcmp(anathesi[k].subj, programma[z].subject2)))){
                                   fprintf(tService, "%.1s.%-17s %-17s %d %7d %6d %10.2f\n", anathesi[k].firstname, anathesi[k].lastname, anathesi[k].subj, anathesi[k].fhours, anathesiFlag[z], anathesi[k].fhours-anathesiFlag[z], (anathesiFlag[z]*100.0/anathesi[k].fhours));
                                   break;
                                }
                        }
                    }
                }
        }
        fprintf(tService, "\n");
    }
  fclose(tService);
}

void selfAffirmationForm(){

FILE *fp, *fp2;
int i, x, j, N, N2, line, sn, flag, l ;
char c, sSurname[maxSurname];
int tk, aNo, db, mb, yb;
char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], mName[maxMname],rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];

int dd, mm, yyyy, week, mhours,  wres=0, year = 0, month = 0;
char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];


 fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file faculties.txt");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
        N++;//counts the number of faculties
    }
    kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation
    if (kathigites == NULL){ // check for memory
        printf("There is no enough memory");
        exit (2);
    }
    fseek(fp,0,SEEK_SET); //returns the file position pointer at the begining of the file
    for(i=0; i<N;i++){
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
        kathigites[i].sn = 0;
        strcpy(kathigites[i].ID,ID);
        strcpy(kathigites[i].surname,surname);
        strcpy(kathigites[i].name,name);
        strcpy(kathigites[i].fname,fName);
        strcpy(kathigites[i].mname,mName);
        kathigites[i].db=db;
        kathigites[i].mb=mb;
        kathigites[i].yb=yb;
        strcpy(kathigites[i].rank,rank);
        strcpy(kathigites[i].condition,condition);
        strcpy(kathigites[i].degree,degree);
        strcpy(kathigites[i].address,address);
        kathigites[i].aNo=aNo;
        strcpy(kathigites[i].city,town);
        kathigites[i].tk=tk;
        strcpy(kathigites[i].phone,phone);
        strcpy(kathigites[i].enable,enable);
    }
    fclose(fp);

    do{
        clrRight();
        gotoxy(maxPrintLeft, 9);printf("Enter surname:");
        scanf("%s", sSurname);
        int a = strlen(sSurname);//keeps the string length
        line = 7, x=0; sn = 0, flag = -3;
        for(j=0; j<i-1; j++){ // search for faculty
            if (!(strncmp(sSurname, kathigites[j].surname,a))){ // compares the given surname with surnames in the file for the first a letters
                ++x; //counts the same surnames in the file
                ++sn;
                kathigites[j].sn = sn;
                gotoxy(maxPrintLeft,++line);printf("SN: %d - ID:%s",sn, kathigites[j].ID);
                gotoxy(maxPrintLeft,++line);printf("Fullname:%s %s", kathigites[j].surname, kathigites[j].name);
                line++;

                if (x == 1){
                    flag = j;
                }

                if (x % 5 == 0 ){ //page handles 5 records
                        line = 7; //initialized the first line to 7
                        x = 0;    //initialized the record counter
                        gotoxy(maxPrintLeft,24);printf("Press ENTER key to Continue"); //for viewing next page of records
                        getch();
                        clrRight();
                }

            }
        }
                //gotoxy(maxPrintLeft,23);printf("sn = %d, katyhigites.sn= %d, j = %d",sn, kathigites[9].sn, j);
                //getch();
            if (sn == 0){ //if not found the surname in the record file
                gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (b) for main menu:");
                c = getch();
                clrRight();
                if (c == 'b'){ //back to main menu
                        clrRight();
                        return;
                }
            }
    }while (sn == 0);//while not found the surname

    gotoxy(maxPrintLeft,24);printf("Press <ENTER> key to Continue"); //enter for next input
    getch();

    if (sn == 1){ //if the surname is unique
        strcpy(ID, kathigites[flag].ID);
        strcpy(surname, kathigites[flag].surname);
        strcpy(name, kathigites[flag].name);
    }else{ //if there is more than one same surnames
        clrRight();

        do {
            gotoxy(maxPrintLeft,7);printf("Enter lecture's SN:");
            scanf("%d", &sn);
                for(i=0; i<N;i++){
                        if (sn == kathigites[i].sn){
                            strcpy(surname, kathigites[i].surname);
                            strcpy(name, kathigites[i].name);
                            gotoxy(maxPrintLeft,8);printf("SN: %d - ID:%s",sn, kathigites[i].ID); //if stricmp is true, it types the record
                            gotoxy(maxPrintLeft,9);printf("Fullname:%s %s", kathigites[i].surname, kathigites[i].name);
                            flag = i;
                            break;
                        }
                }
                if (sn != kathigites[i].sn){
                    for (l = 56; l<110; l++){
                        gotoxy(l,7);printf(" ");
                    }
                    gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
                    c = getch();
                    if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                    }

                }
            } while (sn != kathigites[i].sn);//while the sn is wrong

        getch();
    }

    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }

    clrRight(); j=0;
    N2=0;//initialized line counter
    do{
    gotoxy(maxPrintLeft, 12);printf("Type year(YYYY): ");
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 13);printf("Type month(01-12): ");
    scanf("%d",&month);
        while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name))) && (year == yyyy) && (month == mm)){
                    N2++;
                }
        }
        if (N2 == 0){
            gotoxy(maxPrintLeft, 15);printf("The month or the year is wrong");
            gotoxy(maxPrintLeft, 16);printf("or the professor has not taught the given time.\n");
            gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
            c = getch();
            if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            clrRight();
        }
   }while(N2 == 0);
        programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }
            fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(j=0;j<N2;){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name))) && (year == yyyy) && (month == mm)){
                    programma[j].dd  =  dd;
                    programma[j].mm  =  mm;
                    programma[j].yyyy  =  yyyy;
                    strcpy(programma[j].subject2,subj2);
                    strcpy(programma[j].lastname2, lastname2);
                    strcpy(programma[j].firstname2, firstname2);
                    strcpy(programma[j].class2,class2);
                    programma[j].mhours  =  mhours;
                    wres = wres + programma[j].mhours; //add monthly hours
                    j++;
                }
            }
            fclose(fp2);

const char* minas = mmToMonth(mm);
char affirmation[80];
FILE *tService;

//sprintf(payFile,"\\\\192.168.1.2\\share\\Affirmation\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
sprintf(affirmation,"%s_%s_%s_%d_%d.txt", "Affirmation", lastname2, firstname2, mm, yyyy);
tService=fopen(affirmation,"w");
    if (tService == NULL){
        gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
        exit(2);
    }

fprintf(tService, "\t\t\t SELF AFFIRMATION\n\n");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %s", "|TO", "|" ," Aviation Financial and Accounting Center        |\n");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %21s %-26s %s\n","|FULL NAME", "|" , lastname2, firstname2, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48s %s\n", "|FATHER'S NAME", "|", kathigites[flag].fname, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48s %s\n", "|MOTHER'S NAME", "|", kathigites[flag].mname, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %2d/%2d/%-42d %s\n", "|DATE OF BIRTH", "|", kathigites[flag].db, kathigites[flag].mb, kathigites[flag].yb, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48s %s\n", "|ID NUMBER", "|", kathigites[flag].ID, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-68s %s\n", "|RESIDENTIAL DATA", "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48s %s\n", "|CITY", "|", kathigites[flag].city, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48s %s\n", "|ADDRESS", "|", kathigites[flag].address, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48d %s\n", "|No", "|", kathigites[flag].aNo, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "%-17s %s %-48d %s\n", "|POSTAL CODE", "|",  kathigites[flag].tk, "|");
fprintf(tService, "|--------------------------------------------------------------------|\n");
fprintf(tService, "\t At my sole discretion and knowing the penalties provided by the applicable legislation "
        "regarding the accuracy of my information and statements, I declare responsibly:\n");
fprintf(tService, "\t 1. During the month of %s and year %d, I went beyond compulsory hours and %d hours of teaching.\n", minas, year, wres);
    if (!strcmp(kathigites[flag].condition,"Hourly_Wage")){
            //prints affirmation for Hourly_wage professors
        fprintf(tService, "\t 2. The total of the above earnings I have received or will receive for the "
           "month of %s is lower than the total gross salary of the President of the "
           "Supreme Court as determined by the provisions of Article 6 of Law 1256/82 as currently in force\n\n\n", minas);
    }else{
        //prints for internal and external military professors
        fprintf(tService, "\t 2. I give up the expected compensation for the forty (40) hours I have spent per month according to the provisions"
        " of the Ministerial Order F.540/2/8756/S.766/ 12 Jan 18 of the Minister of National Defense and Finance.\n\n\n");
    }
fprintf(tService, "%65s", "Signature");


fclose(tService);
free(kathigites);
free(programma);

}

void allSelfAffirmationForm(){

    int  i, j, year=0, month=0, N, N2;
    int aNo, tk, db, mb, yb;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], mName[maxMname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char c;

    int dd, mm, yyyy, week, mhours, wres=0;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp2;

    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if ((strcmp(enable, "+")) == 0) { //counts line only for enabled professors
                    N++;
            }
    }

    kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation only for enable professors
    if (kathigites==NULL){ // check for memory
        printf("There is no enough memory");
        exit (2);
   }
    fseek(fp,0,SEEK_SET); //returns the file position pointer at the begining of the file
    for(i=0; i<N;){ //raise i only if found enable faculty
        fscanf(fp, "%s %s %s %s %s %d %d %d %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, mName, &db, &mb, &yb, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if (strcmp(enable, "+") == 0){ //passing files  data into array(only enable faculties)
                kathigites[i].sn = 0;
                strcpy(kathigites[i].ID,ID);
                strcpy(kathigites[i].surname,surname);
                strcpy(kathigites[i].name,name);
                strcpy(kathigites[i].fname,fName);
                strcpy(kathigites[i].mname,mName);
                kathigites[i].db=db;
                kathigites[i].mb=mb;
                kathigites[i].yb=yb;
                strcpy(kathigites[i].rank,rank);
                strcpy(kathigites[i].condition,condition);
                strcpy(kathigites[i].degree,degree);
                strcpy(kathigites[i].address,address);
                kathigites[i].aNo=aNo;
                strcpy(kathigites[i].city,town);
                kathigites[i].tk=tk;
                strcpy(kathigites[i].phone,phone);
                strcpy(kathigites[i].enable,enable);
                ++i;
            }
    }
        fclose(fp);


    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }

    clrRight(); i=0;
    N2=0;//initialized line counter
    do{
    gotoxy(maxPrintLeft, 12);printf("Type year(YYYY): ");
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 13);printf("Type month(01-12): ");
    scanf("%d",&month);
        while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((year == yyyy) && (month == mm)){
                    N2++;
                }
        }
        if (N2 == 0){
            gotoxy(maxPrintLeft, 15);printf("The month or the year is wrong\n.");
            gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
            c = getch();
            if (c == 'r'){ //back to main menu
                        clrRight();
                        return;
                }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            clrRight();
        }
   }while(N2 == 0);
        programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }
            fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){

                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm,  &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if ((year == yyyy) && (month == mm)){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;

                    i++;
                }
            }
    const char* minas = mmToMonth(mm);
    char affirmation[80];
    FILE *tService;

    //sprintf(payFile,"\\\\192.168.1.2\\share\\Affirmation\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
    sprintf(affirmation,"%s_%d_%d.txt", "Affirmation", mm, yyyy);
    tService=fopen(affirmation,"w");
        if (tService == NULL){
            gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
            exit(2);
        }
        for (i=0;i<N;i++){

                        fprintf(tService, "\t\t\t SELF AFFIRMATION\n\n");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %s", "|TO", "|" ," Aviation Financial and Accounting Center        |\n");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %21s %-26s %s\n","|FULL NAME", "|" , kathigites[i].surname, kathigites[i].name, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48s %s\n", "|FATHER'S NAME", "|", kathigites[i].fname, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48s %s\n", "|MOTHER'S NAME", "|", kathigites[i].mname, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %2d/%2d/%-42d %s\n", "|DATE OF BIRTH", "|", kathigites[i].db, kathigites[i].mb, kathigites[i].yb, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48s %s\n", "|ID NUMBER", "|", kathigites[i].ID, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-68s %s\n", "|RESIDENTIAL DATA", "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48s %s\n", "|CITY", "|", kathigites[i].city, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48s %s\n", "|ADDRESS", "|", kathigites[i].address, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48d %s\n", "|No", "|", kathigites[i].aNo, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        fprintf(tService, "%-17s %s %-48d %s\n", "|POSTAL CODE", "|",  kathigites[i].tk, "|");
                        fprintf(tService, "|--------------------------------------------------------------------|\n");
                        for (j=0;j<N2;j++){
                                if (!(strcmp(kathigites[i].surname,programma[j].lastname2)) && (!(strcmp(kathigites[i].name,programma[j].firstname2)))&& (year == programma[j].yyyy) && (month == programma[j].mm)){
                                    wres = wres + programma[j].mhours;
                                }
                        }
                        fprintf(tService, "\t At my sole discretion and knowing the penalties provided by the applicable legislation "
                                "regarding the accuracy of my information and statements, I declare responsibly:\n");
                        fprintf(tService, "\t 1. During the month of %s and year %d, I went beyond compulsory hours and %d hours of teaching.\n", minas, year, wres);
                            if (!strcmp(kathigites[i].condition,"Hourly_Wage")){
                                    //prints affirmation for Hourly_wage professors
                                fprintf(tService, "\t 2. The total of the above earnings I have received or will receive for the "
                                   "month of %s is lower than the total gross salary of the President of the "
                                   "Supreme Court as determined by the provisions of Article 6 of Law 1256/82 as currently in force\n\n\n" ,minas);
                            }else{
                                //prints for internal and external military professors
                                fprintf(tService, "\t 2. I give up the expected compensation for the forty (40) hours I have spent per month according to the provisions"
                                " of the Ministerial Order F.540/2/8756/S.766/ 12 Jan 18 of the Minister of National Defense and Finance.\n\n\n");
                            }
                        fprintf(tService, "%65s", "Signature\n\f");

                    wres = 0;
        }


    fclose(tService);
    free(kathigites);
    free(programma);

}

int dayofweek(int d, int m, int y) //returns an integer for each day of the week
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


void schedule(){
int year, weekNo, N2, i, j=0, flag, nYear, nMonth, nDay, weekDay;
char classroom[maxClass];
int dd, mm, yyyy, week, mhours;
char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];


FILE *fp2, *spec;

fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
do{
    clrRight();
    gotoxy(maxPrintLeft, 12);printf("Type academic year:");//asks the year that starts the academic year
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 14);printf("Type number of training week:");//the first is the week in which the lessons are begging
    scanf("%d", &weekNo);
    clrRight();
    N2=0;
    flag = 0;
    nMonth = 0;
    nDay = 0;
    while (!feof(fp2)){//counts the records depending on the weekNo
        fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);

            if ((((yyyy == year)&&(mm>=9))|| ((yyyy == year+1)&&(mm<=8))) && (weekNo == week)){ //inside the academic year and correct week
                if (flag == 0){ //stores the month and day only the first time for comparison reasons
                    nYear = yyyy;
                    nMonth = mm;
                    nDay = dd;
                    flag = 1;
                }
                if (nMonth>mm){ //finds the first day of the schedule week
                    nMonth = mm;
                    nDay = dd;
                }else if ((nMonth == mm) && (nDay>dd)){
                    nDay = dd;
                }
                N2++;//keeps the number of records to allocate to memory

            }
    }
    weekDay = dayofweek(nDay, nMonth, nYear);

    if (N2 == 0){//not found records for weekNo
        gotoxy(maxPrintLeft, 15);printf("The academic year or the training week is wrong\n.");
        gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
        char c = getch();
            if (c == 'r'){ //back to main menu
                clrRight();
                return;
            }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            flag = 0;

        }
   }while(N2 == 0);

   programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }

     fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm,  &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if (weekNo == week){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    programma[i].trWeek = week;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;
                    i++;
                }
            }

    spec = fopen("specOrder.txt", "r");

    if (spec == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
char weekSchedule[80];
    FILE *tService;

    //sprintf(payFile,"\\\\192.168.1.2\\share\\Affirmation\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
    sprintf(weekSchedule,"%s.txt", "Schedule");
    tService=fopen(weekSchedule,"w");
        if (tService == NULL){
            gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
            exit(2);
        }

    while(weekDay<6){ //6 is for Saturday
        while (1){
            fscanf(spec, "%s", classroom);
                if (feof(spec)){//if reaches eof stops the while condition
                break;
            }
            if (j==0){
                fprintf(tService, "Week:%d \tEducational Schedule %d/%d/%d \n", weekNo, nDay, nMonth, nYear);
            }
            for (i=0;i<N2;i++){
                if (!(strcmp(programma[i].class2, classroom)) && (programma[i].dd == nDay) && (programma[i].mm == nMonth)) {
                    fprintf(tService, "|------------------------------------------------|\n");
                    fprintf(tService, "%-2s %s %-2s %-15s %-20s %-2s\n","|", classroom, "|", programma[i].lastname2, programma[i].firstname2, "|");
                    fprintf(tService, "|        |---------------------------------------|\n");
                    fprintf(tService, "%-8s %-5s %-33s %s \n","|", "|", programma[i].subject2, "|");
                    i=0;
                    break;
                }//if
            }//for
            j++;
            if (j==7){
                j=0;
                fprintf(tService, "|------------------------------------------------| \f");//page break
            //fprintf(tService, "%d/%d/%d \n", nDay, nMonth, nYear);

            }
        }//while
        fseek(spec,0,SEEK_SET);

        struct tm t = {t.tm_year = nYear-1900, t.tm_mon = nMonth-1, t.tm_mday = nDay};
        t.tm_mday+=1;
        mktime(&t);//converts the structure pointed to by timeptr into a time_t value according to the local time zone.
        nDay = t.tm_mday;
        nMonth = t.tm_mon+1;//because months starts from 0 for January

            weekDay = dayofweek(nDay, nMonth, nYear);// the day of the week, 1 for Monday
            //gotoxy(maxPrintLeft, 17);printf("%d", weekDay);
            //getch();


    }
fclose(tService);
fclose(fp2);
free(programma);

}


void scheduleVal(){
int year, weekNo, N2, i, j=0, flag, nYear, nMonth, nDay;
int dd, mm, yyyy, week, mhours;
char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];


FILE *fp2;

fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    do{
        clrRight();
        gotoxy(maxPrintLeft, 12);printf("Type academic year:");//asks the year that starts the academic year
        scanf("%d", &year);
        gotoxy(maxPrintLeft, 14);printf("Type number of training week:");//the first is the week in which the lessons are begging
        scanf("%d", &weekNo);
        clrRight();
        N2=0;
        flag = 0;
        nMonth = 0;
        nDay = 0;
        while (!feof(fp2)){//counts the records depending on the weekNo
            fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
            if ((((yyyy == year)&&(mm>=9))|| ((yyyy == year+1)&&(mm<=8))) && (weekNo == week)){ //inside the academic year and correct week
                if (flag == 0){ //stores the month and day only the first time for comparison reasons
                    nYear = yyyy;
                    nMonth = mm;
                    nDay = dd;
                    flag = 1;
                }
                if (nMonth>mm){ //finds the first day of the schedule week
                    nMonth = mm;
                    nDay = dd;
                }else if ((nMonth == mm) && (nDay>dd)){
                    nDay = dd;
                }
                N2++;//keeps the number of records to allocate to memory

            }
    }

    if (N2 == 0){//not found records for weekNo
        gotoxy(maxPrintLeft, 15);printf("The academic year or the training week is wrong\n.");
        gotoxy(maxPrintLeft, 17);printf("Press <ENTER> and re-enter or <r> to Return to Main Menu.");
        char c = getch();
            if (c == 'r'){ //back to main menu
                clrRight();
                return;
            }
            fseek(fp2,0,SEEK_SET);//returns pointer to the begging
            flag = 0;

        }
   }while(N2 == 0);

   programma = (pro*)malloc(N2*sizeof(pro)); //memory allocation
            if (programma == NULL){ // check for memory
                printf("There is no enough memory");
                exit (2);
            }

     fseek(fp2,0,SEEK_SET); //returns the file position pointer at the beginning of the file
            for(i=0;i<N2;){
                fscanf(fp2, "%d %d %d %d %s %s %s %s %d", &dd, &mm,  &yyyy, &week, subj2, lastname2, firstname2, class2, &mhours);
                if (weekNo == week){
                    programma[i].dd  =  dd;
                    programma[i].mm  =  mm;
                    programma[i].yyyy  =  yyyy;
                    programma[i].trWeek = week;
                    strcpy(programma[i].subject2,subj2);
                    strcpy(programma[i].lastname2, lastname2);
                    strcpy(programma[i].firstname2, firstname2);
                    strcpy(programma[i].class2,class2);
                    programma[i].mhours  =  mhours;
                    i++;
                }
            }

    char validateSchedule[80];
    FILE *tService;

    //sprintf(payFile,"\\\\192.168.1.2\\share\\Affirmation\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
    sprintf(validateSchedule,"%d_%d_%s.txt",weekNo, year, "Validation");
    tService=fopen(validateSchedule, "w");
        if (tService == NULL){
            gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
            exit(2);
        }
    fprintf(tService, "Validate weekly schedule for daily overtime teaching \n\n");
       for (i=0;i<N2;i++){
              for (j=i+1;j<N2;j++){
                 if (!(strcmp(programma[i].lastname2,programma[j].lastname2)) && !(strcmp(programma[i].firstname2,programma[j].firstname2))&&
                    (strcmp(programma[i].subject2,programma[j].subject2))&& (programma[i].dd == programma[j].dd) && (programma[i].mm == programma[j].mm) &&
                    (programma[i].yyyy == programma[j].yyyy) && (programma[i].mhours+programma[j].mhours>7)){
                        fprintf(tService, "%d/%d\n", programma[i].dd, programma[i].mm);
                        fprintf(tService, "%s %s\n", programma[i].lastname2, programma[i].firstname2);
                        fprintf(tService, "%s %s\n", programma[i].subject2, programma[i].class2);
                        fprintf(tService, "%8s %s\n", programma[j].subject2, programma[j].class2);
                        fprintf(tService, "Daily Teaching Hours: %d\n", programma[i].mhours+programma[j].mhours);
                        fprintf(tService, "|------------------------------------------------|\n");


                    }
                }
            }

    fclose(fp2);
    fclose(tService);
    free(programma);
}



void window_one(){
    int choice, x=2, temp, status;
    FontColor(4);

    clrLeft();
    while(1){
        clrInput(16);
        gotoxy(x,8);printf("1. Namely");
        gotoxy(x,10);printf("2. For all the stuff");
        gotoxy(x,12);printf("3. Main Menu");
        gotoxy(x,16);printf("Enter your choice:");
        status = scanf("%d", &choice);
        while (status != 1){
            while ((temp=getchar()) != EOF && temp != '\n'){
                clrInput(16);
                gotoxy(x,16);printf("Enter your choice:");
                status = scanf("%d", &choice);
            }
        }
        switch(choice){
            case 1:
                facultyPayments();
                break;
            case 2:
                allFacultyPayments();
                break;
            case 3:
                main_window();
                break;
        }
    }

}

void window_three(){
    int choice, x=2, temp, status;
    FontColor(4);

    clrLeft();
    while(1){
        clrInput(16);
        gotoxy(x,8);printf("1. Namely");
        gotoxy(x,10);printf("2. For all the stuff");
        gotoxy(x,12);printf("3. Main Menu");
        gotoxy(x,16);printf("Enter your choice:");
        status = scanf("%d", &choice);
        while (status != 1){
            while ((temp=getchar()) != EOF && temp != '\n'){
                clrInput(16);
                gotoxy(x,16);printf("Enter your choice:");
                status = scanf("%d", &choice);
            }
        }
        switch(choice){
            case 1:
                selfAffirmationForm();
                break;
            case 2:
                allSelfAffirmationForm();
                break;
            case 3:
                main_window();
                break;
        }
    }

}

void window_five(){
    int choice, x=2, temp, status;
    FontColor(4);

    clrLeft();
    while(1){
        clrInput(16);
        gotoxy(x,8);printf("1. Weekly Schedule");
        gotoxy(x,10);printf("2. Schedule Validation");
        gotoxy(x,12);printf("3. Main Menu");
        gotoxy(x,16);printf("Enter your choice:");

        status = scanf("%d", &choice);
        while (status != 1){
            while ((temp=getchar()) != EOF && temp != '\n'){
                clrInput(16);
                gotoxy(x,16);printf("Enter your choice:");
                status = scanf("%d", &choice);
            }
        }
        switch(choice){
            case 1:
                schedule();
                break;
            case 2:
                scheduleVal();
                break;
            case 3:
                main_window();
                break;
        }
    }

}


void main_window(){
    int choice, x=2, status, temp;
    FontColor(4);

    clrLeft();
    while(1){
            clrInput(20);
            gotoxy(x,8);printf("1. Faculty Payments");
            gotoxy(x,10);printf("2. Teaching Services Certificate");
            gotoxy(x,12);printf("3. Self-Affirmation Form");
            gotoxy(x,14);printf("4. Faculties' Remaining Hours");
            gotoxy(x,16);printf("5. Schedule");
            gotoxy(x,18);printf("6. Exit");
            gotoxy(x,20);printf("Enter your choice:");

        status = scanf("%d", &choice);
        while (status != 1){
            while ((temp=getchar()) != EOF && temp != '\n'){
                clrInput(20);
                gotoxy(x,20);printf("Enter your choice:");
                status = scanf("%d", &choice);
            }
        }
        switch(choice){
            case 1:
                window_one();
                break;
            case 2:
                teachingServicesCertificate();
                break;            case 3:
                window_three();
                break;
            case 4:
                facRemainingHours();
                break;
            case 5:
                window_five();
                break;
            case 6:
                exit(0);
                break;
            default:
                break;
        }
    }
}

