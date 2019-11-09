#include "lib_func.h"
#include "define.h"
#include "make_func.h"

extern int best_score, key, food_x, food_y, dir1, dir2, speed, length1, length2, stage, result, clear_1, clear_2;
extern int score[100], x[100], y[100], x2[100], y2[100], hurdle_x[1000], hurdle_y[1000];
int i;

void draw_door() { /* ������ �� ����� (9~ 11 �߰�) */
	gotoxy(MAP_X / 2 + MAP_ADJ_X, MAP_ADJ_Y, "  ");
}

int check_1() { /* 1��° ��Ʈ�ѷ� �浹 ���� �Լ� (13 ~ 65 �߰�) */
	if (x[0] == food_x && y[0] == food_y) { //food�� �浹���� ��� 
		score[stage] += 10; //���� ���� 
		food(); //���ο� food �߰� 
		length1++; //�������� 
		x[length1 - 1] = x[length1 - 2]; //���θ��� ���뿡 �� �Է� 
		y[length1 - 1] = y[length1 - 2];

		if (score[stage] == EXIT_SCORE) { /* EXIT_SCORE ���϶� ������ �� ���� (21 ~ 23 �߰�) */
			draw_door();
		}
		return 0;
	}
	if (score[stage] >= EXIT_SCORE && x[0] == MAP_X / 2 && y[0] == 0) {/* 1��° ��Ʈ�ѷ��� Ŭ�����ߴ��� �˻� (26 ~ 37 �߰�)*/
		clear_1 = 0;
		for (i = 0; i < length1; i++) {
			gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], "  ");
			x[i] = MAP_X / 2;
			y[i] = 0;
		}
		if (clear_2 == 0) {
			stage_up();
		}
		return 1;
	}
	else if (x[0] == 0 || x[0] == MAP_X - 1 || y[0] == 0 || y[0] == MAP_Y - 1) { //���� �浹���� ��� 
		game_over();
		return 1; //game_over���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ� 
				//return�� ����Ͽ� move�� ������ �κ��� ������� �ʵ��� �մϴ�. 
	}
	else {
		for (i = 1; i < length1; i++) {  
			if (x[0] == x[i] && y[0] == y[i]) { //�ڱ���� �浹�ߴ��� �˻�
				game_over();
				return 1;
			}
			else if (x[0] == x2[i] && y[0] == y2[i]) { /* �ٸ� ��Ʈ���� ���� �浹�ߴ��� �˻� (�߰�) */
				game_over();
				return 1;
			}
		}
	}
	if (stage > 1) { /* 1��° ��Ʈ�ѷ��� ��ֹ��� �浹�ߴ��� �˻� (55 ~ 61 �߰�) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			if (x[0] == hurdle_x[i] && y[0] == hurdle_y[i]) {
				game_over();
				return 1;
			}
		}
	}

	return 0;
}

int check_2() { /* 2��° ��Ʈ�ѷ� �浹 ���� (67 ~ 119 �߰�) */
	if (x2[0] == food_x && y2[0] == food_y) { //food�� �浹���� ��� 
		score[stage] += 10; //���� ���� 
		food(); //���ο� food �߰� 
		length2++; //�������� 
		x2[length2 - 1] = x2[length2 - 2]; //���θ��� ���뿡 �� �Է� 
		y2[length2 - 1] = y2[length2 - 2];

		if (score[stage] == EXIT_SCORE) { /* EXIT_SCORE ���϶� ������ �� ���� (75 ~ 77 �߰�) */
			draw_door();
		}
		return 0;
	}
	if (score[stage] >= EXIT_SCORE && x2[0] == MAP_X / 2 && y2[0] == 0) { /* 2��° ��Ʈ�ѷ��� Ŭ�����ߴ��� �˻� (80 ~ 91 �߰�) */
		clear_2 = 0;
		for (i = 0; i < length2; i++) {
			gotoxy(MAP_ADJ_X + x2[i], MAP_ADJ_Y + y2[i], "  ");
			x2[i] = MAP_X / 2;
			y2[i] = 0;
		}
		if (clear_1 == 0) {
			stage_up();
		}
		return 1;
	}
	else if (x2[0] == 0 || x2[0] == MAP_X - 1 || y2[0] == 0 || y2[0] == MAP_Y - 1) { //���� �浹���� ��� 
		game_over();
		return 1; //game_over���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ� 
				//return�� ����Ͽ� move�� ������ �κ��� ������� �ʵ��� �մϴ�. 
	}
	else {
		for (i = 1; i < length2; i++) {  
			if (x2[0] == x2[i] && y2[0] == y2[i]) { //�ڱ���� �浹�ߴ��� �˻�
				game_over();
				return 1;
			}
			else if (x2[0] == x[i] && y2[0] == y[i]) { /* �ٸ� ��Ʈ�ѷ��� �浹�ߴ��� �˻� (�߰�) */
				game_over();
				return 1;
			}
		}
	}
	if (stage > 1) { /* 2��° ��Ʈ�ѷ��� ��ֹ��� �浹�ߴ��� �˻� (109 ~ 116 �߰�) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			if (x2[0] == hurdle_x[i] && y2[0] == hurdle_y[i]) {
				game_over();
				return 1;
			}
		}
	}

	return 0;
}

void stage_up() { /* ���� ���������� �Ѿ�� (121 ~ 131 �߰�)*/
	stage++;
	for (i = 1; i <= (stage - 1)*RATIO_H; i++) { /* ��ֹ� ���� (�߰�) */
		hurdle_x[i] = rand() % (MAP_X - 2) + 1;
		hurdle_y[i] = rand() % (MAP_Y - 2) + 1;
		if (hurdle_y[i] == MAP_Y / 2 - 2 || hurdle_y[i] == MAP_Y / 2 + 2 || hurdle_x[i] == MAP_X / 2) { /* Ż�ⱸ�� ���ų� �������ڸ��� �״� ���� ���� */
			i -= 1; /* �� �κи� �ʱ�ȭ */
		}
	}
	reset();
}