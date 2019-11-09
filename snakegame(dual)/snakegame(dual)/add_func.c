#include "lib_func.h"
#include "define.h"
#include "make_func.h"

extern int best_score, key, food_x, food_y, dir1, dir2, speed, length1, length2, stage, result, clear_1, clear_2;
extern int score[100], x[100], y[100], x2[100], y2[100], hurdle_x[1000], hurdle_y[1000];
int i;

void draw_door() { /* 나가는 문 만들기 (9~ 11 추가) */
	gotoxy(MAP_X / 2 + MAP_ADJ_X, MAP_ADJ_Y, "  ");
}

int check_1() { /* 1번째 컨트롤러 충돌 여부 함수 (13 ~ 65 추가) */
	if (x[0] == food_x && y[0] == food_y) { //food와 충돌했을 경우 
		score[stage] += 10; //점수 증가 
		food(); //새로운 food 추가 
		length1++; //길이증가 
		x[length1 - 1] = x[length1 - 2]; //새로만든 몸통에 값 입력 
		y[length1 - 1] = y[length1 - 2];

		if (score[stage] == EXIT_SCORE) { /* EXIT_SCORE 점일때 나가는 문 생성 (21 ~ 23 추가) */
			draw_door();
		}
		return 0;
	}
	if (score[stage] >= EXIT_SCORE && x[0] == MAP_X / 2 && y[0] == 0) {/* 1번째 컨트롤러가 클리어했는지 검사 (26 ~ 37 추가)*/
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
	else if (x[0] == 0 || x[0] == MAP_X - 1 || y[0] == 0 || y[0] == MAP_Y - 1) { //벽과 충돌했을 경우 
		game_over();
		return 1; //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복되므로 
				//return을 사용하여 move의 나머지 부분이 실행되지 않도록 합니다. 
	}
	else {
		for (i = 1; i < length1; i++) {  
			if (x[0] == x[i] && y[0] == y[i]) { //자기몸과 충돌했는지 검사
				game_over();
				return 1;
			}
			else if (x[0] == x2[i] && y[0] == y2[i]) { /* 다른 컨트롤의 몸과 충돌했는지 검사 (추가) */
				game_over();
				return 1;
			}
		}
	}
	if (stage > 1) { /* 1번째 컨트롤러가 장애물에 충돌했는지 검사 (55 ~ 61 추가) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			if (x[0] == hurdle_x[i] && y[0] == hurdle_y[i]) {
				game_over();
				return 1;
			}
		}
	}

	return 0;
}

int check_2() { /* 2번째 컨트롤러 충돌 여부 (67 ~ 119 추가) */
	if (x2[0] == food_x && y2[0] == food_y) { //food와 충돌했을 경우 
		score[stage] += 10; //점수 증가 
		food(); //새로운 food 추가 
		length2++; //길이증가 
		x2[length2 - 1] = x2[length2 - 2]; //새로만든 몸통에 값 입력 
		y2[length2 - 1] = y2[length2 - 2];

		if (score[stage] == EXIT_SCORE) { /* EXIT_SCORE 점일때 나가는 문 생성 (75 ~ 77 추가) */
			draw_door();
		}
		return 0;
	}
	if (score[stage] >= EXIT_SCORE && x2[0] == MAP_X / 2 && y2[0] == 0) { /* 2번째 컨트롤러가 클리어했는지 검사 (80 ~ 91 추가) */
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
	else if (x2[0] == 0 || x2[0] == MAP_X - 1 || y2[0] == 0 || y2[0] == MAP_Y - 1) { //벽과 충돌했을 경우 
		game_over();
		return 1; //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복되므로 
				//return을 사용하여 move의 나머지 부분이 실행되지 않도록 합니다. 
	}
	else {
		for (i = 1; i < length2; i++) {  
			if (x2[0] == x2[i] && y2[0] == y2[i]) { //자기몸과 충돌했는지 검사
				game_over();
				return 1;
			}
			else if (x2[0] == x[i] && y2[0] == y[i]) { /* 다른 컨트롤러와 충돌했는지 검사 (추가) */
				game_over();
				return 1;
			}
		}
	}
	if (stage > 1) { /* 2번째 컨트롤러가 장애물에 충돌했는지 검사 (109 ~ 116 추가) */
		for (i = 1; i <= (stage - 1)*RATIO_H; i++) {
			if (x2[0] == hurdle_x[i] && y2[0] == hurdle_y[i]) {
				game_over();
				return 1;
			}
		}
	}

	return 0;
}

void stage_up() { /* 다음 스테이지로 넘어가기 (121 ~ 131 추가)*/
	stage++;
	for (i = 1; i <= (stage - 1)*RATIO_H; i++) { /* 장애물 생성 (추가) */
		hurdle_x[i] = rand() % (MAP_X - 2) + 1;
		hurdle_y[i] = rand() % (MAP_Y - 2) + 1;
		if (hurdle_y[i] == MAP_Y / 2 - 2 || hurdle_y[i] == MAP_Y / 2 + 2 || hurdle_x[i] == MAP_X / 2) { /* 탈출구를 막거나 시작하자마자 죽는 버그 방지 */
			i -= 1; /* 그 부분만 초기화 */
		}
	}
	reset();
}