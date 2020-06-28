#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

#define FIELD_HEIGHT 23
#define FIELD_WIDTH 18

void my_init_var(void);
void my_init_var2(void);
void my_make_block(void);
void my_gameover(void);
void my_get_key(void);
void my_collision_left(void);
void my_collision_right(void);
void my_collision_bottom(void);
void my_collision_center(void);
void my_fix_block(void);
void my_search_line(void);
void my_clear_line(void);
void my_make_field(void);
void my_make_field2(void);
void my_save_block(void);
void my_draw_field(void);
void my_clear_field(void);
void my_fall_block(void);
void my_timer(void);

int block[BLOCK_HEIGHT][BLOCK_WIDTH];
int stage[FIELD_HEIGHT][FIELD_WIDTH];
int field[FIELD_HEIGHT][FIELD_WIDTH];

int blocks[BLOCK_HEIGHT * 6][BLOCK_WIDTH * 4] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,0},
	{0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0,0,0,1,0,0,1,0,0},
	{0,1,0,0,0,0,1,0,0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,0,1,1,0,0,0,0,0,1,1,0},
	{0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0},
	{0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0},
	{0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0},

	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,1},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0}
};

int clear_line_point[FIELD_HEIGHT - 3];

int block_x;
int block_y;
int collision_flag;
int gameover_flag;
int make_block_flag;
int clear_flag;
int block_id;
int clear_count;

int main(){
	my_init_var();

	while(gameover_flag == 0){
		my_clear_field();

		if(clear_flag == 0){
			my_make_block();
			my_gameover();
			my_get_key();
			my_make_field();
			my_fix_block();
			my_fall_block();
		}else{
			my_clear_line();
			my_make_field2();
		}

		my_draw_field();
		my_timer();
	}

	printf("gamever\n");
		
	return 0;
}

void my_init_var(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT;i++){
		for(j=0;j<FIELD_WIDTH;j++){
			stage[i][0] = 9;
			stage[i][1] = 9;
			stage[i][2] = 9;
			stage[20][j] = 9;
			stage[21][j] = 9;
			stage[22][j] = 9;
			stage[i][15] = 9;
			stage[i][16] = 9;
			stage[i][17] = 9;		
		}
	}

	block_x = 7;
	block_y = 0;
	collision_flag = 0;
	gameover_flag = 0;
	make_block_flag = 1;
	clear_flag = 0;
	block_id = 0;
	clear_count = 0;

	srand((unsigned)time(NULL));
}

void my_init_var2(){
	block_x = 7;
	block_y = 0;
	make_block_flag = 1;
}

void my_make_block(){
	int x,y;

	if(make_block_flag == 1){
		block_id = (rand() % 6);
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				block[y][x] = blocks[(block_id * BLOCK_HEIGHT) + y][x];
			}
		}
		make_block_flag = 0;
	}
}

void my_gameover(){
	my_collision_center();

	if(collision_flag != 0){
		gameover_flag = 1;
	}
}

void my_get_key(){
	int key = 0;
	
	if(_kbhit()){
		key = _getch();
		if(key == 0 || key == 224)key = _getch();
		
		switch(key){
			case 0x4b:
				my_collision_left();
				if(collision_flag == 0){
					block_x--;
				}
				break;
			case 0x4d:
				my_collision_right();
				if(collision_flag == 0){
					block_x++;
				}
				break;
			case 0x50:
				my_collision_bottom();
				while(collision_flag == 0){
					block_y++;
					my_collision_bottom();
				}
				break;
			default:
				break;
		}
	}
}

void my_collision_left(){
	int x,y;
	
	collision_flag = 0;
	
	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			if(block[y][x] != 0){
				if(stage[block_y + y][block_x + (x - 1)] != 0){
					collision_flag = 1;
				}
			}
		}
	}
}

void my_collision_right(){
	int x,y;
	
	collision_flag = 0;
	
	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			if(block[y][x] != 0){
				if(stage[block_y + y][block_x + (x + 1)] != 0){
					collision_flag = 1;
				}
			}
		}
	}
}

void my_collision_bottom(){
	int x,y;

	collision_flag = 0;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			if(block[y][x] != 0){
				if(stage[block_y + (y + 1)][block_x + x] != 0){
					collision_flag = 1;
				}
			}
		}
	}
}

void my_collision_center(){
	int x,y;

	collision_flag = 0;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			if(block[y][x] != 0){
				if(stage[block_y + y][block_x + x] != 0){
					collision_flag = 1;
				}
			}
		}
	}
}

void my_fix_block(){
	int x,y;

	my_collision_bottom();

	if(collision_flag != 0){
		my_save_block();
		my_search_line();
		if(clear_flag == 0){
			my_init_var2();
		}
	}
}

void my_search_line(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		clear_line_point[i] = 0;
	}

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		for(j=3;j<FIELD_WIDTH - 3;j++){
			if(stage[i][j] == 0){
				clear_line_point[i] = 1;
				break;
			}
		}
	}

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		if(clear_line_point[i] == 0){
			clear_flag = 1;
			break;
		}
	}
}

void my_clear_line(){
	int i,j;
	int remain_line_point[20] = {0};
	int remain_line_index = 0;

	if(clear_count < 2){
		for(i=0;i<FIELD_HEIGHT - 3;i++){
			if(clear_line_point[i] == 0){
				for(j=3;j<FIELD_WIDTH - 3;j++){
					stage[i][j] = 0;
				}
			}
		}
		clear_count++;
	}else{
		for(i=FIELD_HEIGHT - 4;i>=0;i--){
			if(clear_line_point[i] != 0){
				remain_line_point[remain_line_index] = i;
				remain_line_index++;
			}
		}

		remain_line_index = 0;
		for(i=FIELD_HEIGHT - 4;i>=0;i--){
			for(j=3;j<FIELD_WIDTH - 3;j++){
				stage[i][j] = stage[remain_line_point[remain_line_index]][j];
			}
			remain_line_index++;
		}

		clear_flag = 0;
		clear_count = 0;
		my_init_var2();
	}
}

void my_make_field(){
	int i,j,x,y;

	for(i=0;i<FIELD_HEIGHT;i++){
		for(j=0;j<FIELD_WIDTH;j++){
			field[i][j] = stage[i][j];	
		}
	}

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			field[block_y + y][block_x + x] += block[y][x];
		}
	}	
}

void my_make_field2(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT;i++){
		for(j=0;j<FIELD_WIDTH;j++){
			field[i][j] = stage[i][j];
		}
	}
}

void my_save_block(){
	int x,y;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			stage[block_y + y][block_x + x] += block[y][x];
		}
	}
}

void my_draw_field(){
	int i,j;

	system("cls");

	for(i=0;i<FIELD_HEIGHT - 2;i++){
		for(j=2;j<FIELD_WIDTH - 2;j++){
			if(field[i][j] == 9)printf("■");
			else if(field[i][j] == 1)printf("□");
			else if(field[i][j] == 2)printf("■");
			else printf("　");
		}
		printf("\n");
	}
}

void my_clear_field(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT;i++){
		for(j=0;j<FIELD_WIDTH;j++){
			field[i][j] = 0;
		}
	}
}

void my_fall_block(){
	if(make_block_flag == 0){
		block_y++;
	}
}

void my_timer(){
	int x,y;
	
	for(y=0;y<10000;y++){
		for(x=0;x<10000;x++){
		}
	}
}