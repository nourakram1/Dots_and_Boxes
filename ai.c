#include "data.h"
#include "game.h"

char is_chain (char i, char j) // take a box has three edges to check with ai is it chain or not
{
    if(!horizontal_line[i][j]) // horizontal line from up
    {
        return dry_chain(i,j,1,1);
    }
    else if(!horizontal_line[i+1][j]) // horezontal line from down
    {
        return dry_chain(i,j,1,2);
    }
    else if(!vertical_line[i][j]) // vertical left
    {
        return dry_chain(i,j,2,1);
    }
    else
    {
        return dry_chain(i,j,2,2); // vertival right
    }

}
void AI_play (int i, int j)
{
    if(!horizontal_line[i][j]) // horizontal line from up
    {
        horizontal_line[i][j] = 2;
        i_1 = i;
        j_1 = j;
        h_v = 1;
        return;
    }
    else if(!horizontal_line[i+1][j]) // horezontal line from down
    {
        horizontal_line[i+1][j] = 2;
        i_1 = i+1;
        j_1 = j;
        h_v = 1;
        return;
    }
    else if(!vertical_line[i][j]) // vertical left
    {
        vertical_line[i][j] = 2;
        i_1 = i;
        j_1 = j;
        h_v = 2;
        return;
                

    }
    else
    {
        vertical_line[i][j+1] = 2;
        i_1 = i;
        j_1 = j+1;
        h_v = 2;
    }

}
void AI_play_2 (int i, int j)
{
    if(!vertical_line[i][j]) // vertical left
    {
        vertical_line[i][j] = 2;
        i_1 = i;
        j_1 = j;
        h_v = 2;
        return;
        

    }
    else if(!horizontal_line[i][j]) // horizontal line from up
    {
        horizontal_line[i][j] = 2;
        i_1 = i;
        j_1 = j;
        h_v = 1;
        return;
    }
    else if(!vertical_line[i][j+1]) // vertical right
    {
        vertical_line[i][j+1] = 2;
        i_1 = i;
        j_1 = j+1;
        h_v = 2;
        return;
    }
    else// horezontal line from down
    {
        horizontal_line[i+1][j] = 2;
        i_1 = i+1;
        j_1 = j;
        h_v = 1;
    } 

}

typedef struct box_node{
    int i;
    int j;
    int num_lines;
    struct box_node * next;
}box_node;

box_node * box_stack = NULL;

int box_stack_length()
{
    if(box_stack == NULL)
    {
        return 0;
    }
    box_node *temp = box_stack;
    int i = 1;
    while(temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    return i;
}

void free_box_stack()
{
    if(box_stack != NULL)
    {
        box_node *temp;
        while(box_stack != NULL)
        {
            temp = box_stack->next;
            free(box_stack);
            box_stack = temp;
        }
    }
}// at the end the value of stack = NULL

box_node * create_node(int i, int j, int num_lines)
{
    box_node * new = malloc(1 * sizeof(box_node)); // creeating a node in the heep
    new->i = i;
    new->j = j;
    new->num_lines = num_lines;
    return new;
}


void add_node(int i, int j, int num_lines)
{
    box_node * new = create_node(i, j, num_lines);
    box_node * temp = box_stack;
    box_stack = new;
    new->next = temp;
}


void search_for_three_and_chain()
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if(box_edges[i][j] == 3 && is_chain(i, j) == 1)
            {
                add_node(i, j, 3);
            }
        }
    }
}

void search_for_three_and_not_chain()
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if(box_edges[i][j] == 3)
            {
                add_node(i, j, 3);
            }
        }
    }
}

void search_for_one()
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if (box_edges[i][j] == 1)
            {
                add_node(i, j, 1);
            }
        }
    }
}

void search_for_zero()
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if(box_edges[i][j] == 0)
            {
                add_node(i, j, 0);
            }
        }
    }
}

void search_for_two()
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if(box_edges[i][j] == 2)
            {
                add_node(i, j, 2);
            }
        }
    }
}

box_node * get_node_from_stack(int index)
{
    box_node * temp = box_stack;
    for(int i = 1; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

void computer_play()
{
    if(box_stack != NULL)
    {
        free_box_stack();
    }
    srand( time(NULL) );
    box_node * play;
    int index;
    search_for_three_and_chain();
    if(box_stack != NULL)
    {
        srand( time(NULL) );
        play = get_node_from_stack(rand() % box_stack_length());
        if(rand() % 2 == 0)
        {
            AI_play (play->i, play->j);
        }
        else
        {
            AI_play_2 (play->i, play->j);
        }
        free_box_stack();
        return;
    }
    search_for_three_and_not_chain();
    if(box_stack != NULL)
    {
        srand( time(NULL) );
        play = get_node_from_stack(rand() % box_stack_length());
        if(rand() % 2 == 0)
        {
            AI_play (play->i, play->j);
        }
        else
        {
            AI_play_2 (play->i, play->j);
        }
        free_box_stack();
        return;
    }
    search_for_zero();
    if(box_stack != NULL)
    {
        srand( time(NULL) );
        play = get_node_from_stack(rand() % box_stack_length());
        if(rand() % 2 == 0)
        {
            AI_play (play->i, play->j);
        }
        else
        {
            AI_play_2 (play->i, play->j);
        }
        free_box_stack();
        return;
    }
    search_for_one();
    if(box_stack != NULL)
    {
        srand( time(NULL) );
        play = get_node_from_stack(rand() % box_stack_length());
        if(rand() % 2 == 0)
        {
            AI_play (play->i, play->j);
        }
        else
        {
            AI_play_2 (play->i, play->j);
        }
        free_box_stack();
        return;
    }
    search_for_two();
    if(box_stack != NULL)
    {
        srand( time(NULL) );
        play = get_node_from_stack(rand() % box_stack_length());
        if(rand() % 2 == 0)
        {
            AI_play (play->i, play->j);
        }
        else
        {
            AI_play_2 (play->i, play->j);
        }
        free_box_stack();
        return;
    }
}