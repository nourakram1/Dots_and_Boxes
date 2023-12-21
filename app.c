#include "filling_data.h"

int main(void)
{
    char * values;
    Zeroing_matrices(horizontal_line, vertical_line);
    print_matrices(horizontal_line, vertical_line);
    // the index of line played
    while(number_of_closed_boxes(box, &n_player1, &n_player2) != game_height * game_width)
    {
        printf("player %d turn\n", turn);
        values = scan_validity();
        values = check_if_line_exist(values,horizontal_line,vertical_line);
        fill_data_into_matrices(values, horizontal_line, vertical_line, turn, &i_1, &j_1);
        
        check_boxes(horizontal_line,vertical_line,box,turn,vertical_or_horizontal(values), i_1, j_1);
        print_matrices(horizontal_line, vertical_line);
        print_box_matrix(box);
        char nubmer_of_closed_boxes = number_of_closed_boxes(box, &n_player1, &n_player2);
        printf("player 1 score %d \nplayer 2 score %d\n", n_player1, n_player2);
        if(temp == nubmer_of_closed_boxes && mode ==1)
        {
            if(turn==1)
            {
                turn=2;
            }
            else
            {
                turn=1;
            }
        }
        else if (temp == nubmer_of_closed_boxes && mode == 2)
        {
            // computer to play
            temp = number_of_closed_boxes(box,&n_player1,&n_player2);
            continue;
            // mean loop will not print for computer to play and any thing her will have turn ==2
        }
        else
        {
            temp = nubmer_of_closed_boxes;

        }
    }
}