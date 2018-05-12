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

void facultyPayments(){

    int  i, j, x, flag=-3, flag1=0, year=0, month=0, N, N1, N2, line, str=1;
    
	int aNo, tk;
    char ID[maxID], surname[maxSurname], name[maxName], fName[maxFname], rank[maxRank], condition[maxCondition], degree[maxDegree],
            address[maxAddress], town[maxCity], phone[maxPhone], enable[maxEnable];
    char sSurname[maxSurname], c;

    
    
     FILE *fp;

    clrRight();
    fp = fopen("faculties.txt", "r");

    if (fp == NULL ){
        gotoxy(maxPrintLeft, 9);printf("Problem opening the file");
        exit (2);
    }else{
        N=0;//initialized line counter
        while (!feof(fp)){
            fscanf(fp, "%s %s %s %s %s %s %s %s %d %s %d %s %s", ID, surname, name, fName, rank, condition, degree,
                    address,&aNo, town, &tk, phone, enable);
                if ((strcmp(enable, "+")) == 0) { //counts line only for enabled professors
                    N++;
                }
        }

        kathigites = (fac*)malloc(N*sizeof(fac)); //memory allocation
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
    }
    do{
        gotoxy(maxPrintLeft, 9);printf("Enter surname:");
        scanf("%s", sSurname);

        clrRight();
        line = 7, x=-1;
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
                    case 0: //if there is no identical surnames
                        flag = -1;//keeps the element's array index
                        break;

                    case 5: //if there are more than five records to display
                        gotoxy(maxPrintLeft,24);printf("Press ENTER key to Continue"); //enter for next page of records
                        getch();
                        clrRight();
                        line = 7; //initialized the first line to 7
                        x = 0;     //initialized the record counter
                        flag = -2;
                        break;
                }
            }

            if (flag == -3){ //if not found the surname in the record file
                gotoxy(maxPrintLeft, 9);printf("There is no record with this item");
                gotoxy(maxPrintLeft, 10);printf("Press any key for re-enter OR (b) for main menu:");
                c = getch();
                clrRight();
                if (c == 'b'){
                        clrRight();
                        return;
                }
            }
    }while (flag == -3);

            gotoxy(maxPrintLeft,24);printf("Press <ENTER> key to Continue"); //enter for next input
            getch();

            clrRight();
            if (flag == -1){
                strcpy(ID, kathigites[flag1].ID);
                strcpy(surname, kathigites[flag1].surname);
                strcpy(name, kathigites[flag1].name);
            }else{
                do {
                    gotoxy(maxPrintLeft,9);printf("Enter professor's ID: ");
                    scanf("%s", ID);
                    for(i=0; i<N;i++){
                        str = strcmp(ID, kathigites[i].ID);
                        if  (str == 0){
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
                } while (str != 0);
            }

    
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
