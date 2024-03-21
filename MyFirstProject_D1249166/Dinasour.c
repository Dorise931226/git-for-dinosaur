#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#define ROAD_LENGTH 50 //路面長度
#define DINO_PLACE  6  //小恐龍在路面上的第幾格

struct dino {
    char road[ROAD_LENGTH + 1];	//字串結尾需要'\0'
    int  jump_Time_Left;		//小恐龍掉到地面的時間
    int  score;					//得到的分數
    int  wait_Time;				//每次迴圈等待的時間
    int  barrier_Chance;		//放置障礙物的機率
    //剩下看各位有需要甚麼
};
typedef struct dino Dino;

Dino* init(void) {
    //Dino MyDino;
    //Dino* MyDinoPtr = &MyDino;

    Dino* MyDinoPtr = (Dino*)malloc(sizeof(Dino));

    if (MyDinoPtr != NULL) {
        MyDinoPtr->jump_Time_Left = 0;
        MyDinoPtr->barrier_Chance = 10;
        MyDinoPtr->score = 0;
        MyDinoPtr->wait_Time = 150;
        for (int i = 0; i < ROAD_LENGTH; i++) {
            MyDinoPtr->road[i] = '_';
        }
        MyDinoPtr->road[ROAD_LENGTH - 1] = 'X';
        MyDinoPtr->road[ROAD_LENGTH] = '\0';
    }
    return MyDinoPtr;
}

void display(Dino* MyDinoPtr) {
    system("cls");

    printf("\n\n\t");
    for (int i = 0; i < ROAD_LENGTH; i++) {
        if (i == DINO_PLACE && MyDinoPtr->jump_Time_Left > 0)
            printf("o");
        else
            printf(" ");
    }
    printf("\n\t");

    //地面
    for (int i = 0; i < ROAD_LENGTH; i++) {
        if (i == DINO_PLACE && MyDinoPtr->jump_Time_Left == 0)
            printf("o");
        else
            printf("%c", MyDinoPtr->road[i]);
    }

    printf("\n\n\n");
    printf("\t\tyour score is: %d", MyDinoPtr->score);
    return;
}

void move(Dino* MyDinoPtr) {
    for (int i = 0; i < ROAD_LENGTH - 1; i++) {
        MyDinoPtr->road[i] = MyDinoPtr->road[i + 1];
    }
    MyDinoPtr->road[ROAD_LENGTH - 1] = '_';
}

bool space_pressed(void) {
    return _kbhit() != 0 && _getch() == 32;
}

bool is_bumped(Dino* MyDinoPtr) {
    return MyDinoPtr->jump_Time_Left == 0 && MyDinoPtr->road[DINO_PLACE] == 'x';
}

int main() {
    Dino* MyDinoPtr = init();
    display(MyDinoPtr);
    while (true) {
        if (space_pressed() && MyDinoPtr->jump_Time_Left == 0)
            MyDinoPtr->jump_Time_Left = 7;
        move(MyDinoPtr);
        if (MyDinoPtr->jump_Time_Left > 0)
            MyDinoPtr->jump_Time_Left -= 1;

        if (is_bumped(MyDino(MyDinoPtr))) {
            display(MyDinoPtr);
            break;
        }
        display(MyDinoPtr);

        Sleep(MyDinoPtr->wait_Time);
    }
    return 0;
}