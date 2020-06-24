#include <stdio.h>
#include <stdlib.h>

#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

#define FIELD_HEIGHT 23
#define FIELD_WIDTH 18

void my_init_var(void);
void my_make_block(void);
void my_make_field(void);
void my_draw_field(void);

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

int main(){
    my_init_var();
    my_make_block();
    my_make_field();
    my_draw_field();
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
}

void my_make_block(){
    int x,y;
    for(y=0;y<BLOCK_HEIGHT;y++){
        for(x=0;x<BLOCK_WIDTH;x++){
            block[y][x] = block[y][x];
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
    system("/usr/bin/clear");
    for(i=0;i<FIELD_HEIGHT;i++){
        for(j=0;j<FIELD_WIDTH;j++){
            if(field[i][j] == 9)printf("¡");
            else if(field[i][j] == 1)printf(" ");
            else printf("@");
        }
        printf("\n");
    }
}
