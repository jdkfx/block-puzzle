#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

#define FIELD_HEIGHT 23
#define FIELD_WIDTH 30

void my_init_var(void);
void my_init_var2(void);
void my_init_board(void);
void my_op(void);
void my_make_block(void);
void my_gameover(void);
void my_get_key(void);
void my_turn_right(void);
void my_turn_left(void);
void my_collision_left(void);
void my_collision_right(void);
void my_collision_bottom(void);
void my_collision_center(void);
void my_collision_turn(void);
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
void my_change_lv(void);

int next_block[BLOCK_HEIGHT][BLOCK_WIDTH];
int block[BLOCK_HEIGHT][BLOCK_WIDTH];
int hold_block[BLOCK_HEIGHT][BLOCK_WIDTH];
int turn_block[BLOCK_HEIGHT][BLOCK_WIDTH];
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
int block_y_point;
int collision_flag;
int gameover_flag;
int first_block_flag;
int make_block_flag;
int hold_block_flag;
int clear_flag;
int next_block_id;
int block_id;
int hold_block_id;
int clear_count;
int turn_point;
int hold_turn_point;
int score;
int lv;

int main(){

	my_init_var();
	my_make_field();
	my_draw_field();
	my_op();

	while(gameover_flag == 0){
		my_clear_field();

		if(clear_flag == 0){
			my_make_block();
			my_gameover();
			my_get_key();
			my_make_field();
			my_fix_block();
			my_fall_block();
		}
		else{
			my_clear_line();
			my_make_field2();
		}

		my_draw_field();
		my_timer();
	}

	printf("gameover\n");
		
	return 0;
}

/*スコアボックス用に「壁」・文字の部分を追加*/
void my_init_var(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT;i++){
		for(j=0;j<FIELD_WIDTH;j++){
			stage[i][0] = 9;
			stage[i][1] = 9;
			stage[i][2] = 9;
			stage[i][3] = 9;
			stage[i][4] = 9;
			stage[i][5] = 9;

			stage[i][6] = 9;
			stage[i][7] = 9;
			stage[i][8] = 9;
			
			stage[20][j] = 9;
			stage[21][j] = 9;
			stage[22][j] = 9;

			stage[i][21] = 9;
			stage[i][22] = 9;
			stage[i][23] = 9;

			stage[i][24] = 9;
			stage[i][25] = 9;
			stage[i][26] = 9;
			stage[i][27] = 9;
			stage[i][28] = 9;
			stage[i][29] = 9;		
		}
	}

	/*文字コード*/
	/*HOLD*/
	stage[1][1] = 72;
	stage[1][2] = 79;
	stage[1][3] = 76;
	stage[1][4] = 68;

	/*NEXT*/
	stage[1][25] = 78;
	stage[1][26] = 69;
	stage[1][27] = 88;
	stage[1][28] = 84;

	/*SC*/
	stage[8][25] = 0;
	stage[8][26] = 0;
	stage[8][27] = 83;
	stage[8][28] = 67;
	stage[9][25] = 0;
	stage[9][26] = 0;
	stage[9][27] = 0;
	stage[9][28] = 0;

	/*LV*/
	stage[11][25] = 0;
	stage[11][26] = 0;
	stage[11][27] = 76;
	stage[11][28] = 86;
	stage[12][25] = 0;
	stage[12][26] = 0;
	stage[12][27] = 0;
	stage[12][28] = 0;

	block_x = 13;
	block_y = 0;
	block_y_point = 0;
	collision_flag = 0;
	gameover_flag = 0;
	first_block_flag = 1;
	make_block_flag = 1;
	hold_block_flag = 0;
	clear_flag = 0;
	next_block_id = 0;
	block_id = 0;
	hold_block_id = 0;
	clear_count = 0;
	turn_point = 0;
	hold_turn_point = 0;
	score = 0;
	lv = 1;

	my_init_board();

	srand((unsigned)time(NULL));
}

/*スコアボード作成用関数*/
void my_init_board(){
	int x,y;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			stage[y+2][x+25] = next_block[y][x];
		}
	}

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			stage[y+2][x+1] = hold_block[y][x];
		}
	}

	if(score < 10){
		stage[9][28] = score;
	}
	else if(score < 100){
		stage[9][27] = score / 10;
		stage[9][28] = score - (score / 10) * 10;
	}
	else{
		stage[9][27] = 9;
		stage[9][28] = 9;
	}
	
	if(lv < 3){
		stage[12][28] = lv;
	}
	else{
		stage[12][28] = 3;
	}
}

void my_init_var2(){
	block_x = 13;
	block_y = 0;
	block_y_point = 0;
	make_block_flag = 1;
	turn_point = 0;
}

/*オープニング*/
void my_op(){
	int any_key;

	printf("BLOCK PUZZLE\n");
	printf("press any key to start");
	any_key = _getch();
	if(any_key == 0 || any_key == 224)any_key = _getch();
}

/*ブロック生成を２段階に*/
/*先に生成したブロックを「next_block_id」に保存*/
/*すぐに「block_id」に保存しなおして再び*/
/*ブロック生成処理を行い「next_block_id」に保存する*/
/*２回目以降はこれを繰り返す*/
void my_make_block(){
	int x,y;

	if(first_block_flag == 1){
		next_block_id = (rand() % 6);
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}
		first_block_flag = 0;
	}	

	if(make_block_flag == 1){
		block_id = next_block_id;
		next_block_id = (rand() % 6);
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				block[y][x] = next_block[y][x];
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}
		make_block_flag = 0;
	}	
}

/*ブロックホールド処理*/
/*初回ホールド時はそのまま「hold_block[4][4]」に*/
/*その時の「block_id」など共に保存、初期化の「my_init_var2()」を行う*/
/*２回目以降は先ほどの「hold_block[4][4]」との入れ替え処理を行い*/
/*そのままブロックの位置だけを元に戻す*/
void my_hold_block(){
	int x,y;
	
	int tmp_block[4][4] = {0};
	int tmp_block_id;
	int tmp_turn_point;

	if(hold_block_flag == 0){
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				hold_block[y][x] = block[y][x];
			}
		}
		hold_block_id = block_id;
		hold_turn_point = turn_point;
		my_init_var2();
		my_make_block();
		hold_block_flag = 1;
	}
	else{
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				tmp_block[y][x] = block[y][x];
				block[y][x] = hold_block[y][x];
				hold_block[y][x] = tmp_block[y][x];
			}
		}
		tmp_block_id = block_id;
		tmp_turn_point = turn_point;
		block_id = hold_block_id;
		turn_point = hold_turn_point;
		hold_block_id = tmp_block_id;
		hold_turn_point = tmp_turn_point;

		block_x = 13;
		block_y = 0;
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
		case 0x48:
			my_turn_right();
			break;
		case 'z':
			my_turn_left();
			break;
		case 'h':
			my_hold_block();
			break;
		default:
			break;
		}

	}
}

void my_turn_right(){
	int x,y;

	turn_point++;
	
	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			turn_block[y][x] = 
				blocks[(block_id * BLOCK_HEIGHT) + y][(turn_point % 4 * BLOCK_WIDTH) + x];
		}
	}

	my_collision_turn();

	if(collision_flag == 0){
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else{
		turn_point--;
	}
}

void my_turn_left(){
	int x,y;

	turn_point += 3;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			turn_block[y][x] = 
				blocks[(block_id * BLOCK_HEIGHT) + y][(turn_point % 4 * BLOCK_WIDTH) + x];
		}
	}

	my_collision_turn();

	if(collision_flag == 0){
		for(y=0;y<BLOCK_HEIGHT;y++){
			for(x=0;x<BLOCK_WIDTH;x++){
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else{
		turn_point -= 3;
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

void my_collision_turn(){
	int x,y;

	collision_flag = 0;

	for(y=0;y<BLOCK_HEIGHT;y++){
		for(x=0;x<BLOCK_WIDTH;x++){
			if(turn_block[y][x] != 0){
				if(stage[block_y + y][block_x + x] != 0){
					collision_flag = 1;
				}
			}
		}
	}
}

/*ブロック固定を２段階に*/
/*最初は固定せずにその時のブロックのy座標を保存*/
/*次も同じy座標にブロックがあった場合は固定*/
void my_fix_block(){
	int x,y;

	my_collision_bottom();

	if(collision_flag != 0){
		if(block_y_point == block_y){
			my_save_block();
			my_search_line();
			if(clear_flag == 0){
				my_init_var2();
			}
		}
		else{
			block_y_point = block_y;
			block_y--;
		}
	}
}

void my_search_line(){
	int i,j;

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		clear_line_point[i] = 0;
	}

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		for(j=9;j<FIELD_WIDTH - 9;j++){
			if(stage[i][j] == 0){
				clear_line_point[i] = 1;
				break;
			}
		}
	}

	for(i=0;i<FIELD_HEIGHT - 3;i++){
		if(clear_line_point[i] == 0){
			clear_flag = 1;
			score++;
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
				for(j=9;j<FIELD_WIDTH - 9;j++){
					stage[i][j] = 0;
				}
			}
		}
		clear_count++;
	}
	else{
		for(i=FIELD_HEIGHT - 4;i >= 0;i--){
			if(clear_line_point[i] != 0){
				remain_line_point[remain_line_index] = i;
				remain_line_index++;
			}
		}

		remain_line_index = 0;
		for(i=FIELD_HEIGHT - 4;i >= 0;i--){
			for(j=9;j<FIELD_WIDTH - 9;j++){
				stage[i][j] = stage[remain_line_point[remain_line_index]][j];
			}
			remain_line_index++;
		}

		clear_flag = 0;
		clear_count = 0;
		my_init_var2();
		my_change_lv();
	}
}

void my_make_field(){
	int i,j,x,y;

	my_init_board();

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

	my_init_board();

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

/*スコアボックスの表示をするべく*/
/*文字コードの部分は「%c」で表示*/
void my_draw_field(){
	int i,j;

	system("cls");

	for(i=0;i<FIELD_HEIGHT - 2;i++){
		for(j=0;j<6;j++){
			if(field[i][j] >= 65)printf(" %c",field[i][j]);
			else if(field[i][j] == 9)printf("■");
			else if(field[i][j] == 1)printf("□");
			else if(field[i][j] == 2)printf("■");
			else printf("　");
		}

		for(j=8;j<FIELD_WIDTH - 8;j++){
			if(field[i][j] == 9)printf("■");
			else if(field[i][j] == 1)printf("□");
			else if(field[i][j] == 2)printf("■");
			else printf("　");
		}

		for(j=24;j<FIELD_WIDTH;j++){
			if(i == 9 && j == 25)printf(" %d",field[i][j]);
			else if(i == 9 && j == 26)printf(" %d",field[i][j]);
			else if(i == 9 && j == 27)printf(" %d",field[i][j]);
			else if(i == 9 && j == 28)printf(" %d",field[i][j]);
			else if(i == 12 && j == 25)printf(" %d",field[i][j]);
			else if(i == 12 && j == 26)printf(" %d",field[i][j]);
			else if(i == 12 && j == 27)printf(" %d",field[i][j]);
			else if(i == 12 && j == 28)printf(" %d",field[i][j]);
			else if(field[i][j] >= 65)printf(" %c",field[i][j]);
			else if(field[i][j] == 9)printf("■");
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
	for(y=0;y<20000 - (lv * 5000);y++){
		for(x=0;x<20000 - (lv * 5000);x++){
		}
	}
}

void my_change_lv(){
	if(score < 10){
		lv = 1;
	}
	else if(score < 20){
		lv = 2;
	}
	else{
		lv = 3;
	}
}