#include "lib_func.h"
#include "define.h"
#include "make_func.h"

extern int best_score, clear_1, clear_2, key, food_x, food_y, dir1, dir2, speed, length1, length2, stage, result;
extern int score[100], x[100], y[100], x2[100], y2[100], hurdle_x[1000], hurdle_y[1000];
int i, j;

void draw_map(void) { //�� �׵θ� �׸��� �Լ� 
	for (i = 0; i < MAP_X; i++) {
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y, "��");
	}
	for (i = MAP_ADJ_Y + 1; i < MAP_ADJ_Y + MAP_Y - 1; i++) {
		gotoxy(MAP_ADJ_X, i, "��");
		gotoxy(MAP_ADJ_X + MAP_X - 1, i, "��");
	}
	for (i = 0; i < MAP_X; i++) {
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y + MAP_Y - 1, "��");
	}
	if (stage > 1) { /* ��ֹ� �׸��� (20 ~ 24 �߰�) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			gotoxy(MAP_ADJ_X + hurdle_x[i], MAP_ADJ_Y + hurdle_y[i], "��");
		}
	}
}

void reset(void) {
	Sleep(200);
	while (1) {
		if (_kbhit()) { //Ű�Է¹��� 
			key = _getch();
			if (key == ESC) exit(0); // ESCŰ�� ���� 
			else break; //�ƴϸ� �׳� ��� ���� 
		}
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 15, "	   STAGE  :  ");
		printf("%d", stage);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "                            ");
		Sleep(400);
	}

	system("cls"); //ȭ���� ���� 
	draw_map(); //�� �׵θ��� �׸� 
	while (_kbhit()) _getch(); //���ۿ� �ִ� Ű���� ���� 

	dir1 = LEFT; // ���� �ʱ�ȭ
	dir2 = D;
	speed = 100; // �ӵ� �ʱ�ȭ 
	length1 = 5;//�� ���� �ʱ�ȭ
	length2 = 5;/* 2��° ��Ʈ�ѷ� ���� �ʱ�ȭ (�߰�) */
	clear_1 = 1;/* 1��° ��Ʈ�ѷ��� Ŭ���� ���� �ʱ�ȭ (�߰�) */
	clear_2 = 1;/* 2��° ��Ʈ�ѷ��� Ŭ���� ���� �ʱ�ȭ (�߰�) */
	for (i = 0; i < 100; i++) { /* ��Ʈ�ѷ� ��ǥ�� �ʱ�ȭ (54 ~ 59 �߰�) */
		x[i] = 0;
		x2[i] = 0;
		y[i] = 0;
		y2[i] = 0;
	}
	for (i = 0; i < 5; i++) { //�� ���밪 �Է� 
		x2[i] = MAP_X / 2 - i;
		y2[i] = MAP_Y / 2 + 2;
		gotoxy(MAP_ADJ_X + x2[i], MAP_ADJ_Y + y2[i], "��");
		x[i] = MAP_X / 2 + i;
		y[i] = MAP_Y / 2 - 2;
		gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], "��");
	}
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "��");
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "��"); //�� �Ӹ� �׸� 
	food(); // food ����  
}

void title(void) {
	stage = 1; /* �������� �ʱ�ȭ (�߰�) */
	result = 0; /* �������� �� �� ���� �ʱ�ȭ (�߰�) */
	for (i = 0; i < 100 - 1; i++) {
		score[i] = 0; //���� �ʱ�ȭ
	}

	while (_kbhit()) _getch(); //���ۿ� �ִ� Ű���� ���� 

	draw_map();    //�� �׵θ��� �׸� 
	for (i = MAP_ADJ_Y + 1; i < MAP_ADJ_Y + MAP_Y - 1; i++) { // �� �׵θ� ������ ��ĭ���� ä�� 
		for (j = MAP_ADJ_X + 1; j < MAP_ADJ_X + MAP_X - 1; j++) gotoxy(j, i, "  ");
	}

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|    S N A K E (D U A L)   |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11, "   �� ��,��,��,�� : Move    ");
	// gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, "   �� P : Pause             "); (�Ͻ����� ��� ����)
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 13, "   �� ESC : Quit              ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 17, "  BLOG.NAVER.COM/AZURE0777 ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 18, "       SNAKE GAME          ");

	reset(); // ������ �ʱ�ȭ  
}

void game_over(void) { //�������� �Լ� 
	for (i = 0; i < 1000; i++) {
		hurdle_x[i] = 0;
		hurdle_y[i] = 0;
	}
	for (i = 0; i < 100; i++) { /* ���� ���� ��� (�߰�) */
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
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 4, MAP_ADJ_Y + 10, "�� BEST SCORE ��");
	}
	Sleep(500);
	while (_kbhit()) _getch();
	_getch();
	title();
}