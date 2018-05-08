#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>


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
            /*case 1:
                facultyPayments();
                break;
            case 2:
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
