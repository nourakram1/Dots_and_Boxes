#include "filling_data.h"
#include "data.h"
#include "printing.h"

// menu
// zero or reset game parameter function
// no of edges for each box
void menu (void)
{
    char input[10];
    printf(ANSI_COLOR_MAGENTA ANSI_BACKGROUND_CYAN ANSI_STYLE_BOLD "\n \n \n \t \t \t \t \t \t Dots And Boxes\n\n" ANSI_RESET_ALL);
    printf("\n\n");
    do{
        printf(ANSI_COLOR_MAGENTA "Enter\n");
        printf("N: For New Game\nL: For Load Game\nR: For Players Rank\nE: For Exit\n" ANSI_RESET_ALL);
        printf("Input: ");
        strcpy(input,scan_string(9)); 
        if(input[0] >= 65 && input[0] <= 90)
        {
            input[0] = input[0] - 65 + 97;
        }
    }while (input[0] != 'r' && input[0] != 'e' && input[0] != 'n' && input[0] != 'l' || strlen(input) != 1);


    if(input[0] == 'e' || input[0] == 'E')
    {
        printf(ANSI_COLOR_MAGENTA "game closed succesfully !\n" ANSI_RESET_ALL);
        free_undo_stack();
        free_redo_stack();
        exit(EXIT_SUCCESS);
        
    }
    else if(input[0] == 'r'||  input[0] == 'R')
    {
        // load rank
        menu();
    }
    else if (input[0] == 'n' || input[0] == 'N')
    {
        reset ();
        char c;
        do
        {
            printf("Enter Game Size From 2 x 2 Till 9 x 9 In This Form (Row x Columbs)\n");
            strcpy(input,scan_string(9));
            game_height = input[0]-48;
            game_width = input[4]-48;
            c = input[2];


        }while(strlen(input) > 5 || game_height < 2 || game_height > 9 || game_width < 2 || game_width > 9 || c!='x' || input[1]!=' ' || input[3]!=' ');
        do
        {
            printf("Enter 1 : For 1 VS 1\nEnter 2 : For Computer Mode\n");
            printf("Input: ");
            strcpy(input,scan_string(9));
            mode = input [0]-48;

        }while (mode != 1 && mode != 2 || strlen(input)!=1);
        if(mode == 1)
        {
            printf("Enter Player 1 Name : ");
            strcpy(player_1_name,scan_string(30));
            printf("Enter Player 2 Name : ");
            strcpy(player_2_name,scan_string(30));
        }
        else
        {
            printf("Enter Player 1 Name : " ANSI_RESET_ALL);
            strcpy(player_1_name,scan_string(30));
            strcpy(player_2_name,"Computer");

        }
        printf(ANSI_RESET_ALL);
        game_flow();
        
    }
    else if (input[0] == 'l' || input[0] == 'L')
    {
        load_game();
    }
}

void game_flow(void)
{
    char * values;
    printf("\n\n");
    print_grid();
    printf("\n\n");
    while(number_of_closed_boxes() != game_height * game_width)
    {
        char input [10];
        if (mode == 1 || mode == 2 && turn == 1)
        {
            save_exit();
            if(undo_stack != NULL && redo_stack == NULL)
            {
                printf("Enter U For undo, else for continue : ");
                strcpy(input,scan_string(9));
                if(input[0] >= 65 && input[0] <= 90)
                {
                    input[0] = input[0] - 65 + 97;
                }
                if(input[0]=='u' || input[0]=='U' && strlen(input) == 1)
                {
                    undo();
                    print_grid();
                    temp = number_of_closed_boxes();
                    continue;
                }

            }
            else if (undo_stack == NULL && redo_stack != NULL)
            {
                printf("Enter R For REDO, Else For Continue : ");
                strcpy(input,scan_string(9));
                if(input[0] >= 65 && input[0] <= 90)
                {
                    input[0] = input[0] - 65 + 97;
                }
                if(input[0]=='r' || input[0]=='R' && strlen(input) == 1)
                {
                    redo();
                    print_grid();
                    temp = number_of_closed_boxes();
                    continue;
                }

            }
            else if(undo_stack != NULL && redo_stack != NULL)
            {
                printf("Enter U For Undo,Enter R For REDO, Else For Continue : ");
                strcpy(input,scan_string(9));
                if(input[0]=='r' || input[0]=='R' && strlen(input) == 1)
                {
                    redo();
                    print_grid();
                    temp = number_of_closed_boxes();
                    continue;
                }
                else if(input[0]=='U' || input[0]=='u' && strlen(input) == 1)
                {
                    undo();
                    print_grid();
                    temp = number_of_closed_boxes();
                    continue;
                }
            }
        }    


        if(turn == 1)
        {
            printf(ANSI_COLOR_RED "Player %d : %s's Turn : " ANSI_RESET_ALL , turn, player_1_name);
        }
        else if( mode == 1)
        {
            printf(ANSI_COLOR_BLUE "Player %d : %s's Turn : " ANSI_RESET_ALL, turn, player_2_name);
        }
        if(mode == 1 || mode == 2 && turn == 1 ){
        values = scan_validity();
        values = check_if_line_exist(values);
        fill_data_into_matrices(values);
        h_v = vertical_or_horizontal(values);
        }
        else // mode = 2 computer play
        {
            count_box_edges();
            computer_play();
        }
        check_boxes();
        printf("\n");
        print_grid();
        printf("\n");
        // redo 
        char nubmer_of_closed_boxes = number_of_closed_boxes();
        printf("%s's Score: %d \n%s's Score: %d\n", player_1_name, n_player1, player_2_name, n_player2);
        if(temp == nubmer_of_closed_boxes)
        {
            if(turn == 1)
            {
                turn = 2;
                free_undo_stack();
                free_redo_stack();
            }
            else
            {
                turn = 1;
                free_undo_stack();
                free_redo_stack();
            }
        }
        else
        {
            temp = nubmer_of_closed_boxes;

        }
    }


    if(n_player1 > n_player2)
    {
        printf(ANSI_COLOR_YELLOW"%s Win !!\n"ANSI_RESET_ALL,player_1_name);
    }
    else if (n_player1 < n_player2)
    {
        printf(ANSI_COLOR_YELLOW"%s Win !!\n"ANSI_RESET_ALL,player_2_name);
    }
    else
    {
        printf("Tie !!");
    }

    // update rank
    menu();
}

void reset (void)
{
    free_redo_stack();
    free_undo_stack();
    for(int i = 0; i < max_game_height ;i++)
    {
        for(int j = 0; j < max__game_width; j++)
        {
            horizontal_line[i][j]=0;
            vertical_line[i][j]=0;
            box[i][j]=0;
            box_edges[i][j]=0;
        }
    }
    turn = 1;
    temp = 0; 

}

char * scan_string(char length) // take actual char need to be readed and clear the buffer
{
    char c;
    string s = malloc (length+1);
    int i=0;
    scanf("%c",&c);
    while (c!=10 && i < length)
    {
        s[i]=c;
        i++;
        scanf("%c",&c);
    }
    s[i] = '\0';
    if(i==length)
    {
        while(getchar()!='\n');
    }
    return s;
}
void count_box_edges (void)
{
    zero_edges();
    for (int i = 0; i <= game_height ; i++)
    {
        for (int j = 0; j < game_width; j++)
        {
            if (i == 0)
            {
                if(horizontal_line[i][j])
                {
                    box_edges[i][j]++;
                }
            }
            else if (i == game_height)
            {
                if(horizontal_line[i][j])
                {
                    box_edges[i-1][j]++;
                }
            }
            else
            {
                if(horizontal_line[i][j])
                {
                    box_edges[i-1][j]++;
                    box_edges[i][j]++;
                }

            }
        }
    }
    for (int i = 0; i < game_height ; i++)
    {
        for (int j = 0; j <= game_width; j++)
        {
            if (j == 0)
            {
                if(vertical_line[i][j])
                {
                    box_edges[i][j]++;
                }
            }
            else if (j == game_width)
            {
                if(vertical_line[i][j])
                {
                    box_edges[i][j-1]++;
                }
            }
            else
            {
                if(vertical_line[i][j])
                {
                    box_edges[i][j]++;
                    box_edges[i][j-1]++;
                }

            }
        }
    }    
    
}