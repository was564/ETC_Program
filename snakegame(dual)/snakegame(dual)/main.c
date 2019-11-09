// ��ȫ��
// ��ó : https://blog.naver.com/azure0777/220282982693
// azure77���� �ڵ�
// main(�� 200��) + add_func(�� 122��) + often_func(�� 122��) = 444��
// 271�� -> 444��

#include "lib_func.h"
#include "define.h"

int stage; /* �������� �� ���� (�߰�) */
int result = 0; /* �������� �� �� ���� (�߰�) */
int score[100]; //���� ����  --reset�Լ��� ���� �ʱ�ȭ�� /* ���ھ ������������ ���� (�迭�� ����) */
int x[100], y[100]; //x,y ��ǥ���� ���� �� 100�� 
int food_x, food_y; //food�� ��ǥ���� ���� 
int speed; //���� �ӵ� 
int best_score = 0; //�ְ� ���� ���� --reset�Լ��� ���� �ʱ�ȭ ���� ���� 
int dir1, dir2; //�̵����� ���� 
int key; //�Է¹��� Ű ���� 
int status_on = 0; // �����ڿ� status ǥ��Ȱ��ȭ ����.. �����߿� SŰ�� ������ Ȱ�� 
int length1, length2; //�����̸� ��� (��Ʈ�ѷ��� ���� ���� (�߰�))
int x2[100], y2[100]; /* 2��° ��Ʈ�ѷ��� ��ǥ�� ���� (�߰�) */
int hurdle_x[1000], hurdle_y[1000]; /* ��ֹ��� ��ǥ�� ���� (�߰�)*/
int clear_1, clear_2; /* ����� ��Ʈ�ѷ��� ���� (�߰�) */
int i, j;

void gotoxy(int x, int y, char* s) { //x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����  
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

void title(void); //���� ����ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void draw_map(void); // ������ �׵θ��� �׸� 
void move_1(int dir);//��Ӹ��� �̵� 
void game_over(void); //���� ������ Ȯ�� 
void food(void); // ���� ���� 
void status(void); // �����ڿ� statusǥ��  
void move_2(int dir); /* 2��° ��Ʈ�ѷ� �̵� (�߰��� �Լ�)*/
void draw_door(); /* �� �׸��� (�߰��� �Լ�) */
void stage_up(); /* ���� �������� ����� (�߰��� �Լ�) */
/* void pause(void); //�Ͻ����� (����) */

int check_1(); /* �浹 üũ (�߰�) */
int check_2();

////////////////////////////MAIN START//////////////////////////////
int main() {
	title();

	while (1) {
		if (_kbhit()) do { key = _getch(); } while (key == 224); //Ű �Է¹���
		Sleep(speed);

		switch (key) { //�Է¹��� Ű�� �ľ��ϰ� ����  
		case A: // ��Ʈ�ѷ� 2 Ű (50 ~ 58 �߰�)
		case D:
		case W:
		case S:
			if ((dir2 == A && key != D) || (dir2 == D && key != A) || (dir2 == W && key != S) ||
				(dir2 == S && key != W))//180ȸ���̵��� �����ϱ� ���� �ʿ�. 
				dir2 = key;
			key = 0; // Ű���� �����ϴ� �Լ��� reset 
				break;
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir1 == LEFT && key != RIGHT) || (dir1 == RIGHT && key != LEFT) || (dir1 == UP && key != DOWN) ||
				(dir1 == DOWN && key != UP))//180ȸ���̵��� �����ϱ� ���� �ʿ�. 
				dir1 = key;
			key = 0; // Ű���� �����ϴ� �Լ��� reset 
			break;
			/* case PAUSE: // PŰ�� ������ �Ͻ����� (����)
				pause();
				break; */
		case 111://oŰ�� ������ �����ڿ� status�� Ȱ��ȭ ��Ŵ  
			if (status_on == 0) status_on = 1;
			key = 0;
			break;
		case ESC: //ESCŰ�� ������ ���α׷� ���� 
			exit(0);
		}
		if (clear_2) { /* ��Ʈ�ѷ��� �����Ӱ� Ŭ���� ���� (78 ~ 83 ����)*/
			move_2(dir2);
		}
		if (clear_1) {
			move_1(dir1);
		}
	}
}

///////////////////////////MAIN END////////////////////////////////
void move_1(int dir) { /* ��Ʈ�ѷ� 1�� ������ �Լ� (92~95 ����) */
	if (check_1()) { // �浹 ���� �Լ��� �߰����� �ڵ� ����ȭ
		return;
	}
	gotoxy(MAP_ADJ_X + x[length1 - 1], MAP_ADJ_Y + y[length1 - 1], "  "); //���� �������� ���� 
	for (i = length1 - 1; i > 0; i--) { //������ǥ�� ��ĭ�� �ű� 
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "��"); //�Ӹ��� �ִ����� �������� ��ħ 
	if (dir == LEFT) --x[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
	if (dir == RIGHT) ++x[0];
	if (dir == UP) --y[0];
	if (dir == DOWN) ++y[0];
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "��"); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸� 
}

void move_2(int dir) { /* ��Ʈ�ѷ� 2�� ������ �Լ� (109 ~ 125 �߰�) cf) move_1 �Լ� ���� */
	if (check_2()) {
		return;
	}

	gotoxy(MAP_ADJ_X + x2[length2 - 1], MAP_ADJ_Y + y2[length2 - 1], "  "); //���� �������� ���� 
	for (i = length2 - 1; i > 0; i--) { //������ǥ�� ��ĭ�� �ű� 
		x2[i] = x2[i - 1];
		y2[i] = y2[i - 1];
	}
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "��"); //�Ӹ��� �ִ����� �������� ��ħ 
	if (dir == A) --x2[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
	if (dir == D) ++x2[0];
	if (dir == W) --y2[0];
	if (dir == S) ++y2[0];
	gotoxy(MAP_ADJ_X + x2[0], MAP_ADJ_Y + y2[0], "��"); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸� 
}

/* void pause(void) { // pŰ�� ������ ��� ������ �Ͻ� ����
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
}					(����)					*/

void food(void) { /* ��Ʈ�ѷ� ������ ���� ���� (161 ~ 184 ����) */
	int food_crush_on = 0;//food�� �� ������ǥ�� ���� ��� on 
	int r = 0; //���� ������ �絿�Ǵ� ���� 
	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: "); //����ǥ�� 
	printf("%-3d \t  \t BEST SCORE: %-3d", score[stage], best_score);

	while (1) {
		food_crush_on = 0;
		srand((unsigned)time(NULL) + r); //����ǥ���� 
		food_x = (rand() % (MAP_X - 2)) + 1;    //������ ��ǥ���� ���� 
		food_y = (rand() % (MAP_Y - 2)) + 1;

		for (i = 0; i < length1; i++) { //food�� �� ����� ��ġ���� Ȯ��  
			if (food_x == x[i] && food_y == y[i]) {
				food_crush_on = 1; //��ġ�� food_crush_on �� on 
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
				food_crush_on = 1; //��ġ�� food_crush_on �� on 
				r++;
				break;
			}
			else if (stage > 1 && food_x == hurdle_x[i] && food_y == hurdle_y[i]) {
				food_crush_on = 1;
				r++;
				break;
			}
		}

		if (food_crush_on == 1) continue; //������ ��� while���� �ٽ� ���� 

		gotoxy(MAP_ADJ_X + food_x, MAP_ADJ_Y + food_y, "��"); //�Ȱ����� ��� ��ǥ���� food�� ��� 
		speed -= 3; //�ӵ� ���� 
		break;

	}
}

void status(void) { //���� ������ ���� �ִ� �Լ� 
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