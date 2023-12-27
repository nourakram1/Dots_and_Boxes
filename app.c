#include "filling_data.h"
#include "data.h"


play * undo_stack = NULL;
play * redo_stack = NULL;

char game_height;
char game_width;

char vertical_line[max_game_height][max__game_width];
char horizontal_line[max_game_height][max__game_width];
char box [max_game_height][max__game_width];
char box_edges [max_game_height][max__game_width];

char n_player1 = 0;
char n_player2 = 0;
char player_1_name[31];
char player_2_name[31];
char turn = 1;
char temp = 0;
char mode;
char i_1 = 0,j_1 = 0; 
char h_v;
game_data* ptr_game_data; // pointer for structure to use globally


int main(void)
{
    menu();
    return 0;
}