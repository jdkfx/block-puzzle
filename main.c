#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

#define FIELD_HEIGHT 23
#define FIELD_WIDTH 18

void my_init_var(void);
void my_make_block(void);
void my_get_key(void);
void my_collision_left(void);
void my_collision_right(void);
void my_make_field(void);
void my_draw_field(void);
void my_clear_field(void);
void my_fall_block(void);
void my_timer(void);

int block[BLOCK_HEIGHT][BLOCK_WIDTH];
int stage[FIELD_HEIGHT][FIELD_WIDTH];
int field[FIELD_HEIGHT][FIELD_WIDTH];

int blocks[BLOCK_HEIGHT][BLOCK_WIDTH] = {
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}
};

int block_x;
int block_y;
int collision_flag;

int main(){
	my_init_var();

	while(1){
		my_clear_field();
		my_make_block();
		my_get_key();
		my_make_field();
		my_draw_field();
		my_timer();
		my_fall_block();

		if(block_y > 17)break;
	}
		
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
}

void my_make_block(){
	int x,y;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			block[y][x] = blocks[y][x];
		}
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

void my_draw_field(){
	int i,j;

	system("cls");

	for(i=0;i<FIELD_HEIGHT - 2;i++){
		for(j=2;j<FIELD_WIDTH - 2;j++){
			if(field[i][j] == 9)printf("■");
			else if(field[i][j] == 1)printf("□");
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
	block_y++;
}

void my_timer(){
	int x,y;
	
	for(y=0;y<10000;y++){
		for(x=0;x<10000;x++){
		}
	}
}