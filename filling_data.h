#ifndef FILLING_DATA_H
#define FILLING_DATA_H

#include <stdio.h>
#include <stdlib.h>

#define game_height 3 //the height of the game in boxes (number of rows of boxes)
#define game_width 3 //the width of the game in boxes (number of columns of boxes)

typedef struct play{
    char turn; //takes the value of the player 1 or 2
    char h_v;
    char i_1;
    char j_1;
    char is_closed;
    char l_r; 
    char is_chain; // an indicator that indicates that move done by dfs or not
    struct play *next; // a pointer to the next move in the stack
} play;

play * undo_stack = NULL;
play * redo_stack = NULL;

char vertical_line[game_height][game_width +1];
char horizontal_line[game_height + 1][game_width];
char box [game_height][game_width]= {{0}};

char n_player1 = 0;
char n_player1 = 0;
char n_player2 = 0;
char turn = 1;
char temp = 0;
char mode = 1;
char i_1 = 0,j_1 = 0; 
char h_v;

char * check_if_line_exist (char values[], char horizontal_line[game_height + 1][game_width], char vertical_line[game_height][game_width +1]);
char * scan_validity (void);
void print_matrices();
void Zeroing_matrices();
void fill_data_into_matrices(char values[]);
char chain (int i, int j,char h_v,char l_r,char horizontal_line [game_height+1][game_width], char vertical_line [game_height][game_width+1],char box[game_height][game_width],char turn);
char number_of_closed_boxes();
void print_box_matrix();
void push_move(char is_closed, char l_r, char is_chain);
void undo(void);
void redo(void);
void move_play_form_to(char turn, play * from_stack, play * to_stack);
void free_stack(play * stack);
void print_stack(play * stack);
play * create_play_node(char h_v, char i_1 , char j_1, char turn, char is_closed, char l_r, char is_chain);
void change_matrices(play *stack);
#endif