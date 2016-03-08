#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
  
  int bullety,bulletx;
  initscr();
  char bflag;
  int enemynum = 63;
  struct Enemy{
    int enemyx;
    int enemyy;
    int aliveflag;
  };
  struct Enemy enemy[64];
  struct ebullet{
    int ebx;
    int eby;
    int innerflag;
  };
  struct ebullet eb[8];
  int by;
  for(int i = 0;i<8;i++){
  eb[i].innerflag=1;
  }
  int numOfEnemy = 63;
  srand(time(NULL));
  for(int i = 0;i < 63;i++){
    enemy[i].enemyx = (rand() % 22)+2;
    enemy[i].enemyy = (rand() % 10)+1;
    enemy[i].aliveflag = 1;
  }
  unsigned long long timescore = 0;
  WINDOW *gamemain = subwin(stdscr,24,40,0,0);
  WINDOW *info = subwin(stdscr,24,30,0,42);
  cbreak();
  noecho();
  int x=20,y=22;
  short int mov=1;
  int score = 0;
  box(gamemain,'|','-');
  box(info,'|','-');
  addch('A');
  struct timespec req;
  req.tv_sec = 0;
  req.tv_nsec = 40000000;
  nodelay(stdscr,1);
  
  enum{GAME_CLEAR,GAME_OVER,GAME_PLAY}GAME_STATE;
  char game_clear[] = "GAME CLEAR!!";
  char game_over[] = "GAME_OVER...";
  GAME_STATE=GAME_PLAY;
  for(;;){
    nanosleep(&req,NULL);
    if(mov == 'h'){
      if(x <= 2){
	x = 2;
      }else{
	x--;
      }
    }else if(mov == 'j'){
      if(y >= 22){
	y = 22;
      }else{
	y++;
      }
    }else if(mov == 'k'){
      if(y <= 1){
	y = 1;
      }else{
	y--;
      }
    }else if(mov == 'l'){
      if(x >= 38){
	x = 38;
      }else{
	x++;
      }
    }else if(mov == 'a'){
      bulletx = x;
      bullety = y;
      bflag = 1;
    }
    else if(mov == 'Q'){
      break;
    }
    move(y,x);
    refresh();
    erase();
    move(y,x);
    box(gamemain,'|','-');
    box(info,'|','-');
    addch('A');
    if(bflag){
      bullety--;
      move(bullety,bulletx);
      printw("^");
      if(bullety < 1){
	bflag = 0;
      }
    }
    for(int i = 0;i < enemynum;i++){
      move(enemy[i].enemyy,enemy[i].enemyx);
      if(enemy[i].aliveflag){
      addch('$');
      }
    }
    for(int i = 0; i < enemynum;i++){
      if(enemy[i].enemyy == bullety && enemy[i].enemyx == bulletx && enemy[i].aliveflag){
	enemy[i].aliveflag=0;
	bullety = 0;
	score++;
	numOfEnemy--;
      }
    }
    for(int i = 0;i < 7;i++){
      
      if(!eb[i].innerflag){
	eb[i].ebx = (rand() % 35) + 2;
	by = rand() % 20;
	by >>= by;
	eb[i].eby = -by;
	eb[i].innerflag = 1;
      }
      if(eb[i].innerflag){
	eb[i].eby++;
	if(eb[i].eby > 40){
	eb[i].innerflag = 0;
	}
	move(eb[i].eby,eb[i].ebx);
	printw("8");
	if((eb[i].ebx == x) && (eb[i].eby == y)){
	  GAME_STATE = GAME_OVER;
	}
      }
    }
    wmove(stdscr,3,45);
    printw("SCORE %d",score);
    wmove(stdscr,15,45);
    printw("TIME %lld",timescore);
    mov = getch();
    timescore++;
    if(numOfEnemy <= 0){
      GAME_STATE = GAME_CLEAR;
      break;
    }
    if(GAME_STATE == GAME_OVER){
      break;
    }
  }
  refresh();
  erase();
  if(GAME_STATE == GAME_CLEAR){
    wmove(stdscr,20,35);
    printw("%s",game_clear);
  }
  if(GAME_STATE == GAME_OVER){
    wmove(stdscr,20,35);
    printw("%s",game_over);
  }
  wmove(stdscr,10,25);
  printw("SCORE:%ld",score);
  nodelay(stdscr,0);
  getch();
  endwin();
  return 0;
}
