#include "data.h"
play * undo_temp = NULL;
play * redo_temp = NULL;
void free_undo_stack() // ..
{
    if(undo_stack != NULL)
    {
        play *temp;
        while(undo_stack != NULL)
        {
            temp = undo_stack->next;
            free(undo_stack);
            undo_stack = temp;
        }
    }
}// at the end the value of stack = NULL

void free_redo_stack() // ..
{
    if(redo_stack != NULL)
    {
        play *temp;
        while(redo_stack != NULL)
        {
            temp = redo_stack->next;
            free(redo_stack);
            redo_stack = temp;
        }
    }
}// at the end the value of stack = NULL

play * create_play_node(char i_1,char j_1,char box_i, char box_j, char is_chain, char h_v_)
{
    play * new = malloc(1 * sizeof(play)); // creeating a node in the heep
    new->h_v = h_v_;
    new->i_1 = i_1;
    new->j_1 = j_1;
    new->box_i = box_i;
    new->box_j = box_j;
    new->is_chain = is_chain;
    new->turn = turn;
    return new;
}

void push_move(char i_1, char j_1, char box_i, char box_j, char is_chain, char h_v_)//true
{
    if(redo_stack != NULL) // freeing the redo if it is not empty
    {
        free_redo_stack();
    }

    play *new = create_play_node(i_1,j_1,box_i, box_j, is_chain, h_v_); //initializing a node

    if(undo_stack != NULL)
    {
        if(undo_stack->turn != turn) // freeing the undo stack if the turn has changed
        {
            free_undo_stack();
        }
    }

    new->next = undo_stack; // which is equal to NULL if the turn changed
    undo_stack = new; // add the node to the stack
}
void print_stack(play * stack) // true
{
    play *temp = stack;
    int i = 0;
    while(temp != NULL)
    {
        printf("node[%i] : ", i);
        printf("h_v = %i, i_1 = %i, is_chain = %i, box_i = %i, j_1 = %i, box_j = %i, turn = %i\n", temp->h_v, temp->i_1, temp->is_chain, temp->box_i, temp->j_1, temp->box_j, temp->turn);
        printf("\n");
        temp = temp->next;
        i++;
    }
    printf("done\n");
}

void undo(void) //..
{
    
    if(undo_stack == NULL || undo_stack->turn != turn)//the last condition was added for a single non handeled condition
    {
        printf("There are no moves to undo !\n");
        return ;
    }

    if(undo_stack != NULL)
    {
        if(undo_stack->h_v == 1)
        {
            horizontal_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
        }
        else
        {
            vertical_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
        }
        box[undo_stack->box_i][undo_stack->box_j] = 0;
    }

    if(undo_stack->is_chain == 0)
    {
        if(undo_stack != NULL)
        {
            if(undo_stack->h_v == 1)
            {
                horizontal_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
            }
            else
            {
                vertical_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
            }
            box[undo_stack->box_i][undo_stack->box_j] = 0;
        }

        redo_temp = redo_stack; //redo [^redo_stack and ^redo_temp, ____,  ....] e.i redo temp points at the first node in redo stack
        redo_stack = undo_stack; // makes the redo_stack pointer points at the first node in the undo stack
        undo_temp = undo_stack->next; // making a temp pointer point at the second node of the undo stack (to not to lose the rest of undo_stack)
        undo_stack->next = redo_temp;  // linking the added node to the redo stack
        undo_stack = undo_temp; // remove the node from the stack by putting the undo_stack pointer to point at the next node
    }
    else
    {
        while(undo_stack->is_chain == 1)
        {
            if(undo_stack != NULL)
            {
                if(undo_stack->h_v == 1)
                {
                    horizontal_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
                }
                else
                {
                    vertical_line[(int)undo_stack->i_1][(int)undo_stack->j_1] = 0;
                }
                box[undo_stack->box_i][undo_stack->box_j] = 0;
            }
            
            redo_temp = redo_stack; //redo [^redo_stack and ^redo_temp, ____,  ....] e.i redo temp points at the first node in redo stack
            redo_stack = undo_stack; // makes the redo_stack pointer points at the first node in the undo stack
            undo_temp = undo_stack->next; // making a temp pointer point at the second node of the undo stack (to not to lose the rest of undo_stack)
            undo_stack->next = redo_temp;  // linking the added node to the redo stack
            undo_stack = undo_temp; // remove the node from the stack by putting the undo_stack pointer to point at the next node
            if(undo_stack == NULL)
            {
                break;
            }
        }
    }
}

void redo(void) //..
{
    if(redo_stack == NULL || redo_stack->turn != turn)//the last condition was added for a single non handeled condition
    {
        printf("There are no moves to redo !\n");
        return ;
    }

    if(redo_stack->is_chain == 0)
    {
        if(redo_stack != NULL)
        {
            if(redo_stack->h_v == 1)
            {
                horizontal_line[redo_stack->i_1][redo_stack->j_1] = redo_stack->turn;
            }
            else
            {
                vertical_line[redo_stack->i_1][redo_stack->j_1] = redo_stack->turn;
            }
            box[redo_stack->box_i][redo_stack->box_j] = redo_stack->turn;
        }
        


        undo_temp = undo_stack; //redo [^redo_stack and ^redo_temp, ____,  ....] e.i redo temp points at the first node in redo stack
        undo_stack = redo_stack; // makes the redo_stack pointer points at the first node in the undo stack
        redo_temp = redo_stack->next; // making a temp pointer point at the second node of the undo stack (to not to lose the rest of undo_stack)
        redo_stack->next = undo_temp;  // linking the added node to the redo stack
        redo_stack = redo_temp; // remove the node from the stack by putting the undo_stack pointer to point at the next node
    }
    else
    {
        while(redo_stack->is_chain == 1)
        {
            if(redo_stack != NULL)
            {
                if(redo_stack->h_v == 1)
                {
                    horizontal_line[redo_stack->i_1][redo_stack->j_1] = redo_stack->turn;
                }
                else
                {
                    vertical_line[redo_stack->i_1][redo_stack->j_1] = redo_stack->turn;
                }
                box[redo_stack->box_i][redo_stack->box_j] = redo_stack->turn;
            }
            
            undo_temp = undo_stack; //redo [^redo_stack and ^redo_temp, ____,  ....] e.i redo temp points at the first node in redo stack
            undo_stack = redo_stack; // makes the redo_stack pointer points at the first node in the undo stack
            redo_temp = redo_stack->next; // making a temp pointer point at the second node of the undo stack (to not to lose the rest of undo_stack)
            redo_stack->next = undo_temp;  // linking the added node to the redo stack
            redo_stack = redo_temp; // remove the node from the stack by putting the undo_stack pointer to point at the next node
            if(redo_stack == NULL)
            {
                break;
            }
        }
    }
}