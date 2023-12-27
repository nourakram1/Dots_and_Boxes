#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_RESET_ALL          "\x1b[0m"

#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"

#define ANSI_STYLE_BOLD         "\x1b[1m"
#define ANSI_STYLE_ITALIC       "\x1b[3m"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m"

#define max_game_height 10 // we support from 2*2 till 9*9 and support rectangular game
#define max__game_width 10
typedef char* string;

typedef struct play{
    char turn; //takes the value of the player 1 or 2
    char h_v;
    char i_1;
    char j_1;
    char box_i;
    char box_j;
    char is_chain; // an indicator that indicates that move done by dfs or not
    struct play *next; // a pointer to the next move in the stack
} play;

extern play * undo_stack;
extern play * redo_stack;

extern char game_height;
extern char game_width;

extern char vertical_line[max_game_height][max__game_width];
extern char horizontal_line[max_game_height][max__game_width];
extern char box [max_game_height][max__game_width];
extern char box_edges [max_game_height][max__game_width];

extern char n_player1;
extern char n_player2;
extern char player_1_name[31]; // assume max size is  30
extern char player_2_name[31]; 
extern char turn;
extern char temp;
extern char mode;
extern char i_1,j_1; 
extern char h_v;


extern time_t player_2_time;
extern time_t player_1_time;
extern time_t temp_begin;
extern time_t temp_end;
typedef struct{
char game_height;
char game_width;
char vertical_line[max_game_height][max__game_width];
char horizontal_line[max_game_height][max__game_width];
char box [max_game_height][max__game_width];
char n_player1;
char n_player2;
char player_1_name[30];
char player_2_name[30];
char turn;
char temp;
char mode;
} game_data;

#endif