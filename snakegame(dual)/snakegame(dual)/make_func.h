#pragma once

void gotoxy(int x, int y, char* s);
void title(void); //게임 시작화면 
void reset(void); //게임을 초기화 
void draw_map(void); // 게임판 테두리를 그림 
void move_1(int dir);//뱀머리를 이동 
void move_2(int dir);
void game_over(void); //게임 오버를 확인 
void food(void); // 음식 생성 
void status(void); // 개발자용 status표시  
void draw_door(); /* 문 그리기 (추가한 함수) */
void stage_up(); /* 다음 스테이지 만들기 (추가한 함수) */
/* void pause(void); //일시정지 (삭제) */

int check_1(); /* 1번째 컨트롤러 충돌 체크 (추가) */
int check_2(); /* 2번째 컨트롤러 충돌 체크 (추가) */