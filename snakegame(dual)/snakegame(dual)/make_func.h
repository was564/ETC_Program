#pragma once

void gotoxy(int x, int y, char* s);
void title(void); //���� ����ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void draw_map(void); // ������ �׵θ��� �׸� 
void move_1(int dir);//��Ӹ��� �̵� 
void move_2(int dir);
void game_over(void); //���� ������ Ȯ�� 
void food(void); // ���� ���� 
void status(void); // �����ڿ� statusǥ��  
void draw_door(); /* �� �׸��� (�߰��� �Լ�) */
void stage_up(); /* ���� �������� ����� (�߰��� �Լ�) */
/* void pause(void); //�Ͻ����� (����) */

int check_1(); /* 1��° ��Ʈ�ѷ� �浹 üũ (�߰�) */
int check_2(); /* 2��° ��Ʈ�ѷ� �浹 üũ (�߰�) */