#ifndef FILLING_DATA_H
#define FILLING_DATA_H

#include "data.h"

char * check_if_line_exist (char values[]);
char * scan_validity (void);
void print_matrices();
void fill_data_into_matrices(char values[]);
void check_boxes (void);
char vertical_or_horizontal(char values[]);
char chain (int i, int j,char h_v,char l_r,char turn, char is_plus);
char number_of_closed_boxes();
void print_box_matrix();
void menu (void);
void game_flow(void);
void reset (void);
void push_move(char i_1, char j_1, char box_i, char box_j, char is_chain, char h_v_);
void undo (void);
void redo (void);
void free_undo_stack(void);
void free_redo_stack(void);
char * scan_string(char length);
void count_box_edges (void);
void zero_edges (void);
char is_chain (char i, char j);
void computer_play();
void save_exit(char input);
void load_game (void);
void print_grid(void);
void undo_redo (char input);
void count_player_moves(char *player_1, char *player_2,char * remaining);

#endif