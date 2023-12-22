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

char turn = 1;
char h_v = 1;
char i_1 = 1;
char j_1 = 2;

play * undo_stack = NULL;
play * redo_stack = NULL;

char vertical_line[game_height][game_width +1] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
char horizontal_line[game_height + 1][game_width] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};
char box [game_height][game_width]= {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};





play * create_play_node(char turn, char is_closed, char l_r, char is_chain)
{
    play * new = malloc(1 * sizeof(play)); // creeating a node in the heep
    new->h_v = h_v;
    new->i_1 = i_1;
    new->j_1 = j_1;
    new->is_closed = is_closed;
    new->l_r = l_r;
    new->is_chain = is_chain;
    new->turn = turn;
    return new;
}

void free_stack(play * stack)
{
    play *temp;
    while(stack != NULL)
    {
        temp = stack->next;
        free(stack);
        stack = temp;
    }
}// at the end the value of stack = NULL

void push_move(char is_closed, char l_r, char is_chain)
{
    if(redo_stack != NULL) // freeing the redo if it is not empty
    {
        free_stack(redo_stack);
    }

    play *new = create_play_node(turn, is_closed, l_r, is_chain); //initializing a node
    
    if(undo_stack->turn != new->turn) // freeing the undo stack if the turn has changed
    {
        free_stack(undo_stack);
    }

    new->next = undo_stack; // which is equal to NULL if the turn changed
    undo_stack = new; // add the node to the stack
}
void print_stack(play * stack)
{
    play *temp = stack;
    int i = 0;
    while(temp != NULL)
    {
        printf("node[%i] : ", i);
        printf("h_v = %i, i_1 = %i, is_chain = %i, is_closed = %i, j_1 = %i, l_r = %i, turn = %i\n", stack->h_v, stack->i_1, stack->is_chain, stack->is_closed, stack->j_1, stack->l_r, stack->turn);
        printf("\n");
        temp = temp->next;
        i++;
    }
    printf("done");
}

int main(void)
{
    push_move(1, 2, 2);
    print_stack(undo_stack);
    turn = 1;
    h_v = 1;
    i_1 = 1;
    j_1 = 2;
    free_stack(undo_stack);
    free_stack(redo_stack);
}