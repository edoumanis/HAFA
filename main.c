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

time_t calendar; //data type for storing system time values
struct tm* cal_info;
char days[3];
char months[3];
char years[5];

void main_window();
void window_one();

typedef struct faculty{
    int sn;
    char ID[maxID];
    char surname[maxSurname];
    char name[maxName];
    char fname[maxFname];
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

    int  i, j, x, flag, year=0, month=0, N, N1, N2, line, sn;
    int aNo, tk;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char sSurname[maxSurname], c;

    int fhours;
    char subj[maxSubject], lastname[maxSurname], firstname[maxName], class1[maxClass];

    int dd, mm, yyyy, mhours, wres=0;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp1, *fp2;

    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, rank, condition, degree,
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
        fscanf(fp, "%s %s %s %s %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if (strcmp(enable, "+") == 0){ //passing files  data into array(only enable faculties)
                kathigites[i].sn = 0;
                strcpy(kathigites[i].ID,ID);
                strcpy(kathigites[i].surname,surname);
                strcpy(kathigites[i].name,name);
                strcpy(kathigites[i].fname,fName);
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
                } while (sn != kathigites[i].sn);//while the sn is wrong
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
            fscanf(fp2, "%d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
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
                fscanf(fp2, "%d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
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

free(kathigites);
free(anathesi);
free(programma);
}


void allFacultyPayments(){

    int  i, j, flag=0, year=0, month=0, N, N2;
    int aNo, tk;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char  c;


    char lastname[maxSurname], firstname[maxName];

    int dd, mm, yyyy, mhours, wres=0;
    char subj2[maxSubject], lastname2[maxSurname], firstname2[maxName], class2[maxClass];

    FILE *fp, *fp2;

    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    N=0;//initialized line counter
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %s %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, rank, condition, degree,
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
        fscanf(fp, "%s %s %s %s %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, rank, condition, degree,
                address,&aNo, town, &tk, phone, enable);
            if (strcmp(enable, "+") == 0){ //passing files  data into array(only enable faculties)
                kathigites[i].sn = 0;
                strcpy(kathigites[i].ID,ID);
                strcpy(kathigites[i].surname,surname);
                strcpy(kathigites[i].name,name);
                strcpy(kathigites[i].fname,fName);
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
            fscanf(fp2, "%d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
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

                fscanf(fp2, "%d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
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

fclose(tService);

free(kathigites);
free(anathesi);
free(programma);
}

void window_one(){
    int choice, x=2;
    FontColor(4);

    clrLeft();
    while(1){
        gotoxy(x,8);printf("1. Namely");
        gotoxy(x,10);printf("2. For all the stuff");
        gotoxy(x,12);printf("3. Main Menu");
        gotoxy(x,16);printf("Enter your choice:");
        scanf("%d", &choice);
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



void main_window(){
    int choice, x=2;
    FontColor(4);

    clrLeft();
    while(1){
        gotoxy(x,8);printf("1. Faculty Payments");
        gotoxy(x,10);printf("2. Teaching Services Certificate");
        gotoxy(x,12);printf("3. Subjects' Remaining Hours");
        gotoxy(x,14);printf("4. Faculties' Remaining Hours");
        gotoxy(x,16);printf("5. Exit");
        gotoxy(x,18);printf("Enter your choice:");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                window_one();
                break;
            /*case 2:
                teachingServicesCertificate();
                break;*/
            /*case 3:
                subjectsRemainingHours();
                break;
            case 4:
                facultiesRemainingHours();
                break;*/
            case 5:
                exit(0);
                break;
        }
    }
}

int main()
{
    ConsoleColors(17,15);
    label();
    main_window();
    gotoxy(0,25);

    return 0;
}
