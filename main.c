#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define maxID 15
#define maxSurname 30
#define maxName 25
#define maxFname 25
#define maxRank 10
#define maxCondition 10
#define maxDegree 10
#define maxAddress 30
#define maxCity 25
#define maxPhone 15
#define maxEnable 5
#define maxSubject 15
#define maxClass 10
#define maxPrintLeft 37




typedef struct faculty{
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

void ConsoleColors(int foreGround, int backGround) //forground and background colors
{
     WORD wColor = ((backGround & 0x0F) << 4) + (foreGround & 0x0F);
     //Retrives handle to standard output device(active console screen buffer
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //Define coordinates, set at the top left cell of the buffer for (0,0)
     COORD coord = {0, 0};
     //Counts how many characters were written
     DWORD found;
     //Contains information about console screen buffer
     CONSOLE_SCREEN_BUFFER_INFO csbi;
	 // Sets attribute of characters written to the console screen buffer (color attribute)
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //Fills the buffer with space character.
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &found);
          //Sets the character attributes
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &found );
          //Sets the cursor at the beggining {0,0}
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

COORD coord = {0,0}; //Sets the cursor at the beggining {0,0}
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; //defines x and y for coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //sets the cursor to specific position
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
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
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
for(i=0;i<78;i++){
    for(j=7;j<25;j++){
        gotoxy(i,j);
        printf(" ");
    }
}
}

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

    int  i, j, x, flag=-3, flag1=0, year=0, month=0, N, N1, N2, line, str=1;
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

        line = 7, x=0;
        for(j=0; j<i-1; j++){ // search for faculty
            if (!(stricmp(sSurname, kathigites[j].surname))){ // compares the given surname with surnames in the file
                gotoxy(maxPrintLeft,++line);printf("ID:%s",kathigites[j].ID); //if stricmp is true, it types the record
                gotoxy(maxPrintLeft,++line);printf("Fullname:%s %s", kathigites[j].surname, kathigites[j].name);
                line++;
                ++x; //counts the same surnames in the file
                flag = 0;
                flag1 = j;
            }
                switch (x){
                    case 1: //if there is no identical surnames
                        flag = -1;//keeps the element's array index
                        break;

                    case 5: //if there are more than five records to display
                        gotoxy(maxPrintLeft,24);printf("Press ENTER key to Continue"); //for viewing next page of records
                        getch();
                        clrRight();
                        line = 7; //initialized the first line to 7
                        x = 0;    //initialized the record counter
                        flag = -2;
                        break;
                }
            }

            if (flag == -3){ //if not found the surname in the record file
                gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (b) for main menu:");
                c = getch();
                clrRight();
                if (c == 'b'){ //back to main menu
                        clrRight();
                        return;
                }
            }
    }while (flag == -3);//while not found the surname

    gotoxy(maxPrintLeft,24);printf("Press <ENTER> key to Continue"); //enter for next input
    getch();

    if (flag == -1){ //if the surname is unique
        strcpy(ID, kathigites[flag1].ID);
        strcpy(surname, kathigites[flag1].surname);
        strcpy(name, kathigites[flag1].name);
    }else{ //if there is more than one same surnames
        do {
            gotoxy(maxPrintLeft,9);printf("Enter professor's ID: "); //ask for ID because is unique
            scanf("%s", ID);
                for(i=0; i<N;i++){
                    str = strcmp(ID, kathigites[i].ID);
                        if  (str == 0){ //if ID is the same with record kathigites.[]ID
                            strcpy(surname, kathigites[i].surname);
                            strcpy(name, kathigites[i].name);
                            break;
                        }
                    }
                    if (str != 0){ //if not found the surname in the record file
                        clrRight();
                        gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                        gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (b) for main menu:");
                        c = getch();
                        clrRight();
                        if (c == 'b'){
                            clrRight();
                            return;
                        }
                    }
                } while (str != 0);//while the ID is wrong
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
        clrRight();
    fclose(fp1);

    gotoxy(maxPrintLeft, 7);printf("Type year: ");
    scanf("%d", &year);
    gotoxy(maxPrintLeft, 8);printf("Type month: ");
    scanf("%d",&month);

    fp2 = fopen("program.txt", "r");

    if (fp2 == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }
    clrRight(); i=0;
    N2=0;//initialized line counter
        while (!feof(fp2)){
            fscanf(fp2, "%d %d %d %s %s %s %s %d", &dd, &mm, &yyyy, subj2, lastname2, firstname2, class2, &mhours);
                if ((!(strcmp(lastname2,surname))) &&  (!(strcmp(firstname2,name))) && (year == yyyy) && (month == mm)){
                    N2++;
                }
        }
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
FILE *pay;

sprintf(payFile,"\\\\192.168.1.2\\share\\Payments\\%s_%s_%d_%d.txt", lastname, firstname, mm, yyyy);
pay=fopen(payFile,"w");
    if (pay == NULL){
        gotoxy(maxPrintLeft, 20);printf("Problem with file opening");
        exit(2);
    }
fprintf(pay,"\t\t\t  Payments for %d/%d \n",mm,yyyy);
fprintf(pay, "Unit: NCOA \n\n");
fprintf(pay, "Date: \n\n");
fprintf(pay, "\t\t\t Statement of Monthly Teaching\n\n");

const char* minas = mmToMonth(mm);

fprintf(pay, "\t 1. Assured that %s %s with identification number %s, in the month of %s %d taught at the "
        "<<Non Commissioned Officer Academy>>, %d hours in accordance with Order F.456/E.6658/456 as analyzed below:\n\n", lastname, firstname, ID, minas, yyyy, wres);
fprintf(pay, "\t DATE \t SUBJECT \t Hours\n");
fprintf(pay, "\t ----------------------------------\n");
    for (i=0;i<N2;i++){
        fprintf(pay,"\t %d/%d \t%s \t %d\n", programma[i].dd, programma[i].mm, programma[i].subject2, programma[i].mhours);
    }
fprintf(pay, "\n\t 2. Assured that %s %s with identification number %s, in the month of %d %d taught at the "
        "<<Non Commissioned Officer Academy>>, %d hours in accordance with Order F.456/E.6658/456 as analyzed below:\n\n", lastname, firstname, ID, mm, yyyy, wres);
fprintf(pay, "\t 3. Assured that %s %s with identification number %s, in the month of %d %d taught at the "
        "<<Non Commissioned Officer Academy>>, %d hours in accordance with Order F.456/E.6658/456 as analyzed below:\n\n\n", lastname, firstname, ID, mm, yyyy, wres);
fprintf(pay, "\t Supervisor \t\t Director \t\t Commander");
fclose(pay);

free(kathigites);
free(anathesi);
free(programma);
}


void main_menu(){
    int choice, x=2;
    FontColor(4);

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
                facultyPayments();
                break;
            /*case 2:
                teachingServicesCertificate();
                break;
            case 3:
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
    main_menu();
    gotoxy(0,25);

    return 0;
}
