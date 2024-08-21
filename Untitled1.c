#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

#define BLACK           0
#define BLUE            1
#define GREEN           2
#define JADE            3
#define RED             4
#define AMETHYST        5
#define YELLOW          6
#define WHITE           7
#define GRAY            8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTJADE       11
#define LIGHTRED        12
#define LIGHTAMETHYST   13
#define LIGHTYELLOW     14
#define DARKWHITE       15

#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_W 0x57
#define VK_J 0x4A
#define VK_H 0x48

#define MAX_X       98
#define MAX_Y       38
#define CENTER_X    50
#define CENTER_Y    20

#define MAX_MAP_X 20
#define MAX_MAP_Y 8

int testMap[MAX_MAP_Y][MAX_MAP_X] = {
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    {7, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 7},
    {7, 3, 0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 7},
    {7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 7},
    {7, 0, 0, 0, 0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
};

int playerX = 3;
int playerY = 4;
int playerWay = 0;
int isClicked = 0;

int score = 0;
int enemy = 0;

void Reset(){
    srand(time(NULL));
}

void SetConsole(){
    system("title 2.5D TEST");
    system("mode con:cols=150 lines=40");

    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(consoleHandle, Cur);
}

void TextColor(int color_number){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void ConsoleClear(){
    system("cls");
}

void MainFrame(){
    TextColor(WHITE);
    for(int i = 1; i < MAX_Y + 1; i++){
        for(int j = 1; j < MAX_X + 1; j++){
            gotoxy(j, i);
            if(i == 1 || j == 1 ||
               i == MAX_Y || j == MAX_X){
                printf("*");
            }
        }
    }
}

void MainFrameWithClear(){
    TextColor(WHITE);
    for(int i = 1; i < MAX_Y + 1; i++){
        for(int j = 1; j < MAX_X + 1; j++){
            gotoxy(j, i);
            if(i == 1 || j == 1 ||
               i == MAX_Y || j == MAX_X){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
    }
}

void PlaceBlock(int x, int y, int width, int height, int color_number){
    TextColor(color_number);
    int buffX = x - (width / 2);
    int buffY = y - (height / 2);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(buffX + i > 1 && buffX + i < MAX_X && buffY + j > 1 && buffY + j < MAX_Y){
                gotoxy(buffX + i, buffY + j);
                printf("*");
            }
        }
    }
}

int CollisionCheck(int x, int y){
    if(testMap[playerY + y][playerX + x] != 3 &&
       testMap[playerY + y][playerX + x] != 7)
        return 1;
    else return 0;
}

void GenerateCrossHair(int shoot){
    if(shoot == 1) TextColor(LIGHTYELLOW);
    else TextColor(LIGHTRED);
    gotoxy(CENTER_X, CENTER_Y);
    printf("¡ä");
}

void GenerateEnemy(){
    if(enemy == 0) {
        while(1){
            int x = rand() % MAX_MAP_X;
            int y = rand() % MAX_MAP_Y;
            if(testMap[y][x] == 0){
                testMap[y][x] = 4;
                break;
            }
        }
        enemy = 1;
    }
}

void GenerateMiniMap(){

    int startX = 105;
    int startY = 15;

    TextColor(WHITE);
    gotoxy(startX, startY - 1);
    printf("MiniMap");

    TextColor(GRAY);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 5; j++){
            if(i == 0 || i == 9 || j == 0 || j == 4){
                gotoxy(startX + i, startY + j);
                printf("*");
            }
        }
    }

    TextColor(testMap[playerY - 1][playerX - 1]);
    gotoxy(startX + 2, startY + 1);
    printf("*");

    TextColor(testMap[playerY - 1][playerX]);
    gotoxy(startX + 4, startY + 1);
    printf("*");

    TextColor(testMap[playerY - 1][playerX + 1]);
    gotoxy(startX + 6, startY + 1);
    printf("*");

    TextColor(testMap[playerY][playerX - 1]);
    gotoxy(startX + 2, startY + 2);
    printf("*");

    TextColor(LIGHTYELLOW);
    gotoxy(startX + 4, startY + 2);
    if(playerWay == 0) printf("¡è");
    else if(playerWay == 1) printf("¡æ");
    else if(playerWay == 2) printf("¡é");
    else if(playerWay == 3) printf("¡ç");

    TextColor(testMap[playerY][playerX + 1]);
    gotoxy(startX + 6, startY + 2);
    printf("*");

    TextColor(testMap[playerY + 1][playerX - 1]);
    gotoxy(startX + 2, startY + 3);
    printf("*");

    TextColor(testMap[playerY + 1][playerX]);
    gotoxy(startX + 4, startY + 3);
    printf("*");

    TextColor(testMap[playerY + 1][playerX + 1]);
    gotoxy(startX + 6, startY + 3);
    printf("*");

}

void GenerateScene(){

    int generate_width = 3;
    int generate_deep = 1;
    int blockW = 48;
    int blockH = 27;
    float buff;

    if(playerWay == 0) generate_deep = playerY;
    else if(playerWay == 1) generate_deep = MAX_MAP_X - playerX;
    else if(playerWay == 2) generate_deep = MAX_MAP_Y - playerY;
    else if(playerWay == 3) generate_deep = playerX;


    for(int j = generate_deep; j > 0; j--){
        for(int i = generate_width; i >= -generate_width; i--){

            buff = sqrt(i*i + j*j);

            switch(playerWay){
            case 0:
                if(testMap[playerY - j][playerX + i] != 0 &&
                   playerY - j >= 0 && playerY - j < MAX_MAP_Y &&
                   playerX + i >= 0 && playerX + i < MAX_MAP_X){
                    if(testMap[playerY - j][playerX + i] == 4) PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (1 / buff), blockH * (2 / buff), testMap[playerY - j][playerX + i]);
                    else PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (2 / buff), blockH * (2 / buff), testMap[playerY - j][playerX + i]);
                }
                break;
            case 1:
                if(testMap[playerY + i][playerX + j] != 0 &&
                   playerY + i >= 0 && playerY + i < MAX_MAP_Y &&
                   playerX + j >= 0 && playerX + j < MAX_MAP_X){
                    if(testMap[playerY + i][playerX + j] == 4) PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (1 / buff), blockH * (2 / buff), testMap[playerY + i][playerX + j]);
                    else PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (2 / buff), blockH * (2 / buff), testMap[playerY + i][playerX + j]);
                }
                break;
            case 2:
                if(testMap[playerY + j][playerX - i] != 0 &&
                   playerY + j >= 0 && playerY + j < MAX_MAP_Y &&
                   playerX - i >= 0 && playerX - i < MAX_MAP_X){
                    if(testMap[playerY + j][playerX - i] == 4) PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (1 / buff), blockH * (2 / buff), testMap[playerY + j][playerX - i]);
                    else PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (2 / buff), blockH * (2 / buff), testMap[playerY + j][playerX - i]);
                }
                break;
            case 3:
                if(testMap[playerY - i][playerX - j] != 0 &&
                   playerY - i >= 0 && playerY - i < MAX_MAP_Y &&
                   playerX - j >= 0 && playerX - j < MAX_MAP_X){
                    if(testMap[playerY - i][playerX - j] == 4) PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (1 / buff), blockH * (2 / buff), testMap[playerY - i][playerX - j]);
                    else PlaceBlock(CENTER_X + (24 * i * (3 / buff)), CENTER_Y, blockW * (2 / buff), blockH * (2 / buff), testMap[playerY - i][playerX - j]);
                }
                break;
            }
        }
    }
}

void GetCommand(){
    while(!isClicked){
        if(GetAsyncKeyState(VK_A) & 0x8000){
            if(playerWay == 0) playerWay = 3;
            else playerWay -= 1;
            isClicked = 1;
        }
        if(GetAsyncKeyState(VK_D) & 0x8000){
            if(playerWay == 3) playerWay = 0;
            else playerWay += 1;
            isClicked = 1;
        }
        if(GetAsyncKeyState(VK_W) & 0x8000){
            if(playerWay == 0 && CollisionCheck(0, -1)) playerY -= 1;
            else if(playerWay == 1 && CollisionCheck(1, 0)) playerX += 1;
            else if(playerWay == 2 && CollisionCheck(0, 1)) playerY += 1;
            else if(playerWay == 3 && CollisionCheck(-1, 0)) playerX -= 1;
            isClicked = 1;
        }
        if(GetAsyncKeyState(VK_S) & 0x8000){
            if(playerWay == 0 && CollisionCheck(0, 1)) playerY += 1;
            else if(playerWay == 1 && CollisionCheck(-1, 0)) playerX -= 1;
            else if(playerWay == 2 && CollisionCheck(0, -1)) playerY -= 1;
            else if(playerWay == 3 && CollisionCheck(1, 0)) playerX += 1;
            isClicked = 1;
        }
        if(GetAsyncKeyState(VK_J) & 0x8000){
            if(playerWay == 0) playerWay = 2;
            else if(playerWay == 1) playerWay = 3;
            else if(playerWay == 2) playerWay = 0;
            else if(playerWay == 3) playerWay = 1;
            isClicked = 1;
        }
        if(GetAsyncKeyState(VK_H) & 0x8000){
            int bx = 0, by = 0;
            int x = 0, y = 0;
            if(playerWay == 0) y = -1;
            else if(playerWay == 1) x = 1;
            else if(playerWay == 2) y = 1;
            else if(playerWay == 3) x = -1;

            GenerateCrossHair(1);
            Sleep(50);
            while(1){
                bx = bx + x;
                by = by + y;
                if(testMap[playerY + by][playerX + bx] == 3 || testMap[playerY + by][playerX + bx] == 7) break;
                else if(testMap[playerY + by][playerX + bx] == 4){
                    testMap[playerY + by][playerX + bx] = 0;
                    score++;
                    enemy = 0;
                    break;
                }
            }

            isClicked = 1;
        }
    }
}

void GenerateText(){
    TextColor(WHITE);

    gotoxy(105, 36);
    printf("THE GAME TEST");
    gotoxy(105, 37);
    printf("MADE BY TRAUM");

     gotoxy(105, 5);
    printf("Score : %3d", score);

    gotoxy(105, 10);
    printf("PLAYER X, Y : %2d, %2d", playerX, playerY);
    gotoxy(105, 11);
    printf("PLAYER DIR : %d", playerWay);

    gotoxy(105, 30);
    printf("Key");
    gotoxy(105, 31);
    printf("W : ÀüÁø S : ÈÄÁø A : ÁÂÈ¸Àü D : ¿ìÈ¸Àü");
    gotoxy(105, 32);
    printf("J : µÚµ¹±â H : ÃÑ½î±â");
}

int main(void){

    Reset();
    SetConsole();

    while(1){
        MainFrameWithClear();

        GenerateEnemy();
        GenerateScene();
        GenerateCrossHair(0);

        GenerateMiniMap();

        GenerateText();

        Sleep(100);

        GetCommand();
        isClicked = 0;

    }

    return 0;
}
