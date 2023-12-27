#include "data.h"
#include "filling_data.h"

void save (game_data* game_data_ptr)
{
    game_data_ptr->game_height = game_height;
    game_data_ptr->game_width = game_width;
    game_data_ptr->n_player1 = n_player1;
    game_data_ptr->n_player2 = n_player2;
    game_data_ptr->mode = mode;
    game_data_ptr->temp = temp;
    game_data_ptr->turn = turn;
    strcpy(game_data_ptr->player_1_name, player_1_name);
    strcpy(game_data_ptr->player_2_name, player_2_name);
    for(int i = 0; i < max_game_height ;i++)
    {
        for(int j = 0; j < max__game_width; j++)
        {
            game_data_ptr->horizontal_line[i][j] = horizontal_line[i][j];
            game_data_ptr->vertical_line[i][j] = vertical_line[i][j];
            game_data_ptr->box[i][j] = box[i][j];
        }
    }
}

void load (game_data *game_data_ptr)
{
    game_height = game_data_ptr->game_height ;
    game_width = game_data_ptr->game_width;
    n_player1 = game_data_ptr->n_player1;
    n_player2 = game_data_ptr->n_player2;
    mode = game_data_ptr->mode; 
    temp = game_data_ptr->temp;
    turn = game_data_ptr->turn ;
    strcpy(player_1_name, game_data_ptr->player_1_name);
    strcpy(player_2_name, game_data_ptr->player_2_name);
    for(int i = 0; i < game_height + 1 ;i++)
    {
        for(int j = 0; j < game_width + 1; j++)
        {
            horizontal_line[i][j] = game_data_ptr->horizontal_line[i][j];
            vertical_line[i][j] = game_data_ptr->vertical_line[i][j];
            box[i][j] = game_data_ptr->box[i][j];
        }
    }  
}
void save_exit(void)
{
    printf("Enter S For Save, E for Exit,Else For Continue : ");
    char input [10] = "nn";
    strcpy(input,scan_string(5));
    if(input[0] >= 65 && input[0] <= 90)
    {
        input[0] = input[0] - 65 + 97;
    }
    if(input[0] == 'e' || input [0] =='E' && strlen(input)== 1)
    {
        free_redo_stack();
        free_undo_stack();
        printf(ANSI_COLOR_MAGENTA "game closed succesfully !\n" ANSI_RESET_ALL);
        exit(EXIT_SUCCESS);
    }
    else if (input[0] == 's' || input[0] == 'S' && strlen(input)== 1)
    {
        game_data save_1;
        save(&save_1);
        FILE * out;
        out = fopen("save_1.bin","wb");
        if (out == NULL)
        {
            printf("Save Failed\n");
            exit(EXIT_FAILURE);
        }
        int written = fwrite(&save_1, sizeof(game_data), 1, out);
        fclose(out);
        if(written == 0)
        {
            printf("Save Failed\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("save done\n");
            return;
        }
    }
    else
    {
        return;

    }
}
void load_game (void)
{
    game_data save_1;
    FILE * in;
    in = fopen("save_1.bin","rb");
    if(in == NULL)
    {
        printf("Load Failed");
        exit(EXIT_FAILURE);
    }
    int read = fread(&save_1,sizeof(game_data),1,in);
    fclose(in);
    if(read == 0)
    {
        printf("Load Failed");
        exit(EXIT_FAILURE);  
    }
    load(&save_1);
    printf("load done \n\n\n");
    game_flow();
}