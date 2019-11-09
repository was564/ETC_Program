#include "lib_func.h"
#include "define.h"
#include "make_func.h"

extern int best_score, clear_1, clear_2, key, food_x, food_y, dir1, dir2, speed, length1, length2, stage, result;
extern int score[100], x[100], y[100], x2[100], y2[100], hurdle_x[1000], hurdle_y[1000];
int i, j;

void draw_map(void) { //맵 테두리 그리는 함수 
	for (i = 0; i < MAP_X; i++) {
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y, "■");
	}
	for (i = MAP_ADJ_Y + 1; i < MAP_ADJ_Y + MAP_Y - 1; i++) {
		gotoxy(MAP_ADJ_X, i, "■");
		gotoxy(MAP_ADJ_X + MAP_X - 1, i, "■");
	}
	for (i = 0; i < MAP_X; i++) {
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y + MAP_Y - 1, "■");
	}
	if (stage > 1) { /* 장애물 그리기 (20 ~ 24 추가) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			gotoxy(MAP_ADJ_X + hurdle_x[i], MAP_ADJ_Y + hurdle_y[i], "■");
		}
	}
}

void reset(void) {
	Sleep(200);
	while (1) {
		if (_kbhit()) { //키입력받음 
			key = _getch();
			if (key == ESC) exit(0); // ESC키면 종료 
			else break; //아니면 그냥 계속 진행 
		}
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 15, "	   STAGE  :  ");
		printf("%d", stage);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "                            ");
		Sleep(400);
	}

	system("cls"); //화면을 지움 
	draw_map(); //맵 테두리를 그림 
	while (_kbhit()) _getch(); //버퍼에 있는 키값을 버림 

	dir1 = LEFT; // 방향 초기화
	dir2 = D;
	speed = 100; // 속도 초기화 
	length1 = 5;//뱀 길이 초기화
	length2 = 5;/* 2번째 컨트롤러 길이 초기화 (추가) */
	clear_1 = 1;/* 1번째 컨트롤러의 클리어 여부 초기화 (추가) */
	clear_2 = 1;/* 2번째 컨트롤러의 클리어 여부 초기화 (추가) */
	for (i = 0; i < 100; i++) { /* 컨트롤러 좌표값 초기화 (54 ~ 59 추가) */
		x[i] = 0;
		x2[i] = 0;
		y[i] = 0;
		y2[i] = 0;
	}
	for (i = 0; i < 5; i++) { //뱀 몸통값 입력 
		x2[i] = MAP_X / 2 - i;
		y2[i] = MAP_Y / 2 + 2;
		gotoxy(MAP_ADJ_X + x2[i], MAP_ADJ_Y + y2[i], "ㅁ");
		x[i] = MAP_X / 2 + i;
		y[i] = MAP_Y / 2 - 2;
		gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], "ㅇ");
	}
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "▣");
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "ㅎ"); //뱀 머리 그림 
	food(); // food 생성  
}

void title(void) {
	stage = 1; /* 스테이지 초기화 (추가) */
	result = 0; /* 스테이지 총 합 점수 초기화 (추가) */
	for (i = 0; i < 100 - 1; i++) {
		score[i] = 0; //점수 초기화
	}

	while (_kbhit()) _getch(); //버퍼에 있는 키값을 버림 

	draw_map();    //맵 테두리를 그림 
	for (i = MAP_ADJ_Y + 1; i < MAP_ADJ_Y + MAP_Y - 1; i++) { // 맵 테두리 안쪽을 빈칸으로 채움 
		for (j = MAP_ADJ_X + 1; j < MAP_ADJ_X + MAP_X - 1; j++) gotoxy(j, i, "  ");
	}

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|    S N A K E (D U A L)   |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11, "   ◇ ←,→,↑,↓ : Move    ");
	// gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, "   ◇ P : Pause             "); (일시정지 기능 삭제)
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 13, "   ◇ ESC : Quit              ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 17, "  BLOG.NAVER.COM/AZURE0777 ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 18, "       SNAKE GAME          ");

	reset(); // 게임을 초기화  
}

void game_over(void) { //게임종료 함수 
	for (i = 0; i < 1000; i++) {
		hurdle_x[i] = 0;
		hurdle_y[i] = 0;
	}
	for (i = 0; i < 100; i++) { /* 총합 점수 계산 (추가) */
		result += score[i];
	}
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 5, "+----------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 6, "|      GAME OVER..     |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 7, "+----------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 8, " YOUR SCORE : ");
	printf("%d", result);

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, " Press any keys to restart.. ");

	if (result > best_score) {
		best_score = result;
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 4, MAP_ADJ_Y + 10, "☆ BEST SCORE ☆");
	}
	Sleep(500);
	while (_kbhit()) _getch();
	_getch();
	title();
}