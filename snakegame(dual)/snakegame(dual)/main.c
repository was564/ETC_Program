// 김홍준
// 출처 : https://blog.naver.com/azure0777/220282982693
// azure77님의 코드
// main(약 200줄) + add_func(약 122줄) + often_func(약 122줄) = 444줄
// 271줄 -> 444줄

#include "lib_func.h"
#include "define.h"

int stage; /* 스테이지 수 저장 (추가) */
int result = 0; /* 스테이지 총 합 점수 (추가) */
int score[100]; //점수 저장  --reset함수에 의해 초기화됨 /* 스코어를 스테이지별로 저장 (배열로 수정) */
int x[100], y[100]; //x,y 좌표값을 저장 총 100개 
int food_x, food_y; //food의 좌표값을 저장 
int speed; //게임 속도 
int best_score = 0; //최고 점수 저장 --reset함수에 의해 초기화 되지 않음 
int dir1, dir2; //이동방향 저장 
int key; //입력받은 키 저장 
int status_on = 0; // 개발자용 status 표시활성화 변수.. 게임중에 S키를 누르면 활성 
int length1, length2; //몸길이를 기억 (컨트롤러의 각자 길이 (추가))
int x2[100], y2[100]; /* 2번째 컨트롤러의 좌표값 저장 (추가) */
int hurdle_x[1000], hurdle_y[1000]; /* 장애물의 좌표값 저장 (추가)*/
int clear_1, clear_2; /* 통과한 컨트롤러를 저장 (추가) */
int i, j;

void gotoxy(int x, int y, char* s) { //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입  
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

void title(void); //게임 시작화면 
void reset(void); //게임을 초기화 
void draw_map(void); // 게임판 테두리를 그림 
void move_1(int dir);//뱀머리를 이동 
void game_over(void); //게임 오버를 확인 
void food(void); // 음식 생성 
void status(void); // 개발자용 status표시  
void move_2(int dir); /* 2번째 컨트롤러 이동 (추가한 함수)*/
void draw_door(); /* 문 그리기 (추가한 함수) */
void stage_up(); /* 다음 스테이지 만들기 (추가한 함수) */
/* void pause(void); //일시정지 (삭제) */

int check_1(); /* 충돌 체크 (추가) */
int check_2();

////////////////////////////MAIN START//////////////////////////////
int main() {
	title();

	while (1) {
		if (_kbhit()) do { key = _getch(); } while (key == 224); //키 입력받음
		Sleep(speed);

		switch (key) { //입력받은 키를 파악하고 실행  
		case A: // 컨트롤러 2 키 (50 ~ 58 추가)
		case D:
		case W:
		case S:
			if ((dir2 == A && key != D) || (dir2 == D && key != A) || (dir2 == W && key != S) ||
				(dir2 == S && key != W))//180회전이동을 방지하기 위해 필요. 
				dir2 = key;
			key = 0; // 키값을 저장하는 함수를 reset 
				break;
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir1 == LEFT && key != RIGHT) || (dir1 == RIGHT && key != LEFT) || (dir1 == UP && key != DOWN) ||
				(dir1 == DOWN && key != UP))//180회전이동을 방지하기 위해 필요. 
				dir1 = key;
			key = 0; // 키값을 저장하는 함수를 reset 
			break;
			/* case PAUSE: // P키를 누르면 일시정지 (삭제)
				pause();
				break; */
		case 111://o키를 누르면 개발자용 status를 활성화 시킴  
			if (status_on == 0) status_on = 1;
			key = 0;
			break;
		case ESC: //ESC키를 누르면 프로그램 종료 
			exit(0);
		}
		if (clear_2) { /* 컨트롤러의 움직임과 클리어 여부 (78 ~ 83 수정)*/
			move_2(dir2);
		}
		if (clear_1) {
			move_1(dir1);
		}
	}
}

///////////////////////////MAIN END////////////////////////////////
void move_1(int dir) { /* 컨트롤러 1의 움직임 함수 (92~95 수정) */
	if (check_1()) { // 충돌 여부 함수를 추가시켜 코드 간결화
		return;
	}
	gotoxy(MAP_ADJ_X + x[length1 - 1], MAP_ADJ_Y + y[length1 - 1], "  "); //몸통 마지막을 지움 
	for (i = length1 - 1; i > 0; i--) { //몸통좌표를 한칸씩 옮김 
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "ㅇ"); //머리가 있던곳을 몸통으로 고침 
	if (dir == LEFT) --x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
	if (dir == RIGHT) ++x[0];
	if (dir == UP) --y[0];
	if (dir == DOWN) ++y[0];
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "ㅎ"); //새로운 머리좌표값에 머리를 그림 
}

void move_2(int dir) { /* 컨트롤러 2의 움직임 함수 (109 ~ 125 추가) cf) move_1 함수 복사 */
	if (check_2()) {
		return;
	}

	gotoxy(MAP_ADJ_X + x2[length2 - 1], MAP_ADJ_Y + y2[length2 - 1], "  "); //몸통 마지막을 지움 
	for (i = length2 - 1; i > 0; i--) { //몸통좌표를 한칸씩 옮김 
		x2[i] = x2[i - 1];
		y2[i] = y2[i - 1];
	}
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "ㅁ"); //머리가 있던곳을 몸통으로 고침 
	if (dir == A) --x2[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
	if (dir == D) ++x2[0];
	if (dir == W) --y2[0];
	if (dir == S) ++y2[0];
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "▣"); //새로운 머리좌표값에 머리를 그림 
}

/* void pause(void) { // p키를 눌렀을 경우 게임을 일시 정지
	while (1) {
		if (key == PAUSE) {
			gotoxy(MAP_ADJ_X + (MAP_X / 2) - 9, MAP_ADJ_Y, "< PAUSE : PRESS ANY KEY TO RESUME > ");
			Sleep(400);
			gotoxy(MAP_ADJ_X + (MAP_X / 2) - 9, MAP_ADJ_Y, "                                    ");
			Sleep(400);
		}
		else {
			draw_map();
			return;
		}
		if (_kbhit()) {

			do {
				key = _getch();
			} while (key == 224);
		}

	}
}					(삭제)					*/

void food(void) { /* 컨트롤러 마다의 길이 조정 (161 ~ 184 수정) */
	int food_crush_on = 0;//food가 뱀 몸통좌표에 생길 경우 on 
	int r = 0; //난수 생성에 사동되는 변수 
	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: "); //점수표시 
	printf("%-3d \t  \t BEST SCORE: %-3d", score[stage], best_score);

	while (1) {
		food_crush_on = 0;
		srand((unsigned)time(NULL) + r); //난수표생성 
		food_x = (rand() % (MAP_X - 2)) + 1;    //난수를 좌표값에 넣음 
		food_y = (rand() % (MAP_Y - 2)) + 1;

		for (i = 0; i < length1; i++) { //food가 뱀 몸통과 겹치는지 확인  
			if (food_x == x[i] && food_y == y[i]) {
				food_crush_on = 1; //겹치면 food_crush_on 를 on 
				r++;
				break;
			}
			else if (stage > 1 && food_x == hurdle_x[i] && food_y == hurdle_y[i]) {
				food_crush_on = 1;
				r++;
				break;
			}
		}
		for (i = 0; i < length2; i++) {
			if (food_x == x2[i] && food_y == y2[i]) {
				food_crush_on = 1; //겹치면 food_crush_on 를 on 
				r++;
				break;
			}
			else if (stage > 1 && food_x == hurdle_x[i] && food_y == hurdle_y[i]) {
				food_crush_on = 1;
				r++;
				break;
			}
		}

		if (food_crush_on == 1) continue; //겹쳤을 경우 while문을 다시 시작 

		gotoxy(MAP_ADJ_X + food_x, MAP_ADJ_Y + food_y, "♪"); //안겹쳤을 경우 좌표값에 food를 찍고 
		speed -= 3; //속도 증가 
		break;

	}
}

void status(void) { //각종 스텟을 볼수 있는 함수 
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y, "head= ");
	printf("%2d,%2d", x[0], y[0]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "food= ");
	printf("%2d,%2d", food_x, food_y);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 2, "leng= ");
	printf("%2d, %2d", length1, length2);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 3, "key= ");
	printf("%3d", key);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 4, "spd= ");
	printf("%3d", speed);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 6, "score= ");
	printf("%3d", score[stage]);
}