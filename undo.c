#include "filling_data.h"

void push_move(char is_closed, char l_r, char is_chain)
{
    
    if(redo_stack != NULL) // freeing the redo if it is not empty
    {
        free_stack(redo_stack);
    }

    play *new = create_play_node(h_v, i_1, j_1,turn,is_closed, l_r, is_chain); //initializing a node
    
    if(undo_stack->turn != new->turn) // freeing the undo stack if the turn has changed
    {
        free_stack(undo_stack);
    }

    new->next = undo_stack; // which is equal to NULL if the turn changed
    undo_stack = new; // add the node to the stack
}

void undo(void)
{
    if(undo_stack == NULL || undo_stack->turn != turn)//the last condition was added for a single non handeled condition
    {
        printf("There are no moves to undo !\n");
        return ;
    }  
    change_matrices(undo_stack);
    move_play_form_to(turn, undo_stack, redo_stack); 
}

void redo(void)
{
    if(redo_stack == NULL || redo_stack->turn != turn)
    {
        printf("There are no moves to redo !\n");
        return ;
    }  
    change_matrices(redo_stack);
    move_play_form_to(turn, redo_stack, undo_stack);  
}

void move_play_form_to(char turn, play * from_stack, play * to_stack)
{
    do
    {
        play * to_temp = to_stack; //redo [^redo_stack and ^redo_temp, ____,  ....] e.i redo temp points at the first node in redo stack
        to_stack = from_stack; // makes the redo_stack pointer points at the first node in the undo stack
        play *from_temp = from_stack->next; // making a temp pointer point at the second node of the undo stack (to not to lose the rest of undo_stack)
        from_stack->next = to_temp;  // linking the added node to the redo stack
        from_stack = from_temp; // remove the node from the stack by putting the undo_stack pointer to point at the next node 
    }while(from_stack->is_chain == 1 && from_stack->turn == turn && to_stack->is_chain == 1);//third condition handles one case, the second condition is useless but it is for readablity
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
}

play * create_play_node(char h_v, char i_1 , char j_1, char turn, char is_closed, char l_r, char is_chain)
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

void change_matrices(play *stack)
{
    if(stack->h_v == 1)
    {
        horizontal_line[stack->i_1][stack->j_1] = stack->turn;
    }
    else
    {
        vertical_line[stack->i_1][stack->j_1] = stack->turn;

    }
    if(stack->is_closed == 1)
    {
       if (stack->h_v == 1 && stack->l_r == 2) // under horizontal line 
       {
           box[stack->i_1 +1 ][stack->j_1] = stack->turn; 

       }
       else if (stack->h_v == 1 && stack->l_r == 1 || stack->h_v == 2 && stack->l_r == 1) // above 
       {
            box[stack->i_1][stack->j_1] = stack->turn;

       }
       else 
       {
            box[stack->i_1][stack->j_1 + 1] = stack->turn;
       }
    }
}