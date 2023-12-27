#include "data.h"
#include "filling_data.h"


void fill_data_into_matrices(char values[])
{
    if(values[0] == values[1])
    {
        if(values[2] < values[3])
        {
            horizontal_line[values[0]][values[2]] = turn;
            i_1 = values[0];
            j_1 = values[2];
        }
        else
        {
            horizontal_line[values[0]][values[3]] = turn;
            i_1 = values[0];
            j_1 = values[3];
        }
    }
    else if(values[2] == values[3])
    {
        if(values[0] < values[1])
        {
            vertical_line[values[0]][values[2]] = turn;
            i_1 = values[0];
            j_1 = values[2];
        }
        else
        {
            vertical_line[values[1]][values[2]] = turn;
            i_1 = values[1];
            j_1 = values[2];
        }
        
    }
} // use part of this to indicate that line horizontal or vertical

char vertical_or_horizontal(char values[])
{
    if(values[0] == values[1])
    {
        return 1; // mean horizontal line
    }
    else
    {
        return 2; // mean vertical line
        
    }
} // use part of this to indicate that line horizontal or vertical

void print_matrices(void)
{
    printf("horizontal line matrix : \n");
    for(int i = 0; i < game_height + 1; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            printf("%i\t", horizontal_line[i][j]);
        }
        printf("\n");
    }
    printf("\n");
      printf("vertical line matrix : \n");
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width +1; j++)
        {
            printf("%i\t", vertical_line[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


///////////////////////////////////////////////

char * scan_validity (void)
{
    char input [15];
    strcpy(input,scan_string(6));
    input [0] -= 48;
    input [1] -= 48;
    input [2] -= 48;
    input [3] -= 48;

    if ( input [0] ==input [1] & input [0] ==0  || input[2] ==input[3] && input[2] == 0 || strlen(input)!=4)
    {
        printf(ANSI_COLOR_CYAN"Wrong Input\n"ANSI_RESET_ALL);
        return scan_validity();
    }
    else if (!( (input [0] ==input [1]) ^ (input[2] ==input[3]) ))
    {
        printf(ANSI_COLOR_CYAN"Wrong Input\n"ANSI_RESET_ALL);
        return scan_validity();
    }
    else if ((input [0]  > game_height+1) ||(input [1] > game_height + 1) ||(input[2]  > game_width + 1)||(input[3] > game_width + 1) )
    {
        printf(ANSI_COLOR_CYAN"Wrong Input\n"ANSI_RESET_ALL);
        return scan_validity(); 
    }
    else if ((input [0] ==input [1] & abs(input[2] -input[3])!=1) || (input[2] ==input[3]  & abs(input [0] -input [1])!=1))
    {
        printf(ANSI_COLOR_CYAN"Wrong Input\n"ANSI_RESET_ALL);
        return scan_validity(); 
    }
    
    else
    {
        char *s = malloc(4 * sizeof(char));
        s[0]=input [0] -1;
        s[1]=input [1]-1;
        s[2]=input[2] -1;
        s[3]=input[3]-1;
        return s;
    }  
}


char * check_if_line_exist (char values[])
// check if the valid index is not played before during the game and force player to input valid cell
{
    if(values[0] == values[1])
    {
        if(values[2] < values[3] & horizontal_line[values[0]][values[2]] !=0 )
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity());   
        }
        else if (values[2] > values[3] & horizontal_line[values[0]][values[3]] !=0 )
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity());
            // double call because if user insert repeated place then insert another repeated one 
        }
        else
        {
            return values;
        }
    }
    else if(values[2] == values[3])
    {
        if(values[0] < values[1] & vertical_line[values[0]][values[2]] != 0)
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity());
        }
        else if (values[0] > values[1] & vertical_line[values[1]][values[2]] != 0)
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity());
        }
        else
        {
            return values;
        }
        
    }
    else
    {
        return values;
    }
}


char chain (int i, int j,char h_v,char l_r,char turn,char is_plus)
{
    // h_v = 1 mean horizontal, 2 vertical line 
    // l_r = 1 mean left or up l_r = 2 mean right or down


    if( h_v == 1 && l_r == 2 ) // under horizontal line
    {
        if (!vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i+1][j] )
        {
            return 1; // important for uncompleted +
        }
        else if (i + 1 < game_height && box[i+1][j] == 0 ) // there it's box below me so check possible cases
        {
            if (vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+2][j] != 0) 
            {
                box [i+1][j] = turn;
                push_move(i+1,j,i+1,j,1,1);
                return 1;
            }
            else if(vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+1][j] == 0)// | |
            {
                if(turn !=0 && chain(i+1,j,1,2,turn,is_plus)) // check chain for box below me
                {
            
                    horizontal_line[i+2][j] = turn;
                    box [i+1][j] = turn;
                    push_move(i+2,j,i+1,j,1,1);
                    return 1;
                }
                else if(turn == 0 && (chain(i+1,j,1,2,0,is_plus) ))// mean dry searching
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                
            }

            else if (horizontal_line[i+2][j] && vertical_line[i+1][j]) // |_
            {
                if( turn !=0 && chain(i+1,j,2,2,turn,is_plus))
                {
                vertical_line[i+1][j+1] = turn;
                box[i+1][j] =turn;
                push_move(i+1,j+1,i+1,j,1,2);
                return 1; 
                }
                else if(turn == 0 && chain(i+1,j,2,2,0,is_plus)) //dry searching
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                

            }
            else if (horizontal_line[i+2][j] && vertical_line[i+1][j+1]) // _|
            {
                if(turn !=0 && chain(i+1,j,2,1,turn,is_plus))
                {
                vertical_line[i+1][j] = turn;
                box[i+1][j] = turn;
                push_move(i+1,j,i+1,j,1,2);
                return 1;
                }
                else if(turn == 0 && chain(i+1,j,2,1,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(is_plus && chain(i+1,j,1,2,0,1) && chain(i+1,j,2,2,0,0)&&chain(i+1,j,2,1,0,0))
            {// + like chain
    
                chain(i+1,j,1,2,turn,1);
                chain(i+1,j,2,1,turn,0);
                chain(i+1,j,2,2,turn,0);
                if(!vertical_line[i+1][j])
                {
                    vertical_line[i+1][j]=turn;
                    push_move(i+1,j,i+1,j,1,2);
                }
                if(!vertical_line[i+1][j+1])
                {
                    vertical_line[i+1][j+1]=turn;
                    push_move(i+1,j+1,i+1,j,1,2);
                }
                if(!horizontal_line[i+2][j])
                {
                    horizontal_line[i+2][j]=turn;
                    push_move(i+2,j,i+1,j,1,1);
                }
                box[i+1][j]=turn;
                return 1;
            }
            else {return 0;}
        }
        else // mean no box below me 
        {
            if(horizontal_line[i+1][j] == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        
    }    

    else if( h_v == 1 && l_r == 1 )
    { 
        if (!vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i][j] )
        {
            return 1; // important for uncompleted +
        }   
        else if(i-1 >= 0 && box[i-1][j]==0) // above horizontal line
        {
            if (vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i-1][j] != 0)
            {
                box[i-1][j]=turn;
                push_move(i,j,i-1,j,1,1);
                return 1;
            }

            else if(vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i][j] == 0)
            {
                if(turn != 0 && chain(i-1,j,1,1,turn,is_plus))
                {
                
                    horizontal_line[i-1][j] = turn;
                    box[i-1][j] = turn;
                    push_move(i-1,j,i-1,j,1,1);
                    return 1;
                }
                else if (turn == 0 && chain(i-1,j,1,1,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }    
            }

            else if (horizontal_line[i-1][j] && vertical_line[i-1][j])
            {
                if(turn !=0 && chain(i-1,j,2,2,turn,is_plus))
                {
                vertical_line [i-1][j+1] = turn;
                box[i-1][j] = turn;
                push_move(i-1,j+1,i-1,j,1,2);
                return 1;
                }
                else if (turn == 0 && chain(i-1,j,2,2,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

            }
            else if (horizontal_line[i-1][j] && vertical_line [i-1][j+1])
            {
                if(turn !=0 && chain(i-1,j,2,1,turn,is_plus))
                {
                vertical_line[i-1][j] = turn;
                box[i-1][j] = turn;
                push_move(i-1,j,i-1,j,1,2);
                return 1;
                }
                else if (turn ==0 && chain(i-1,j,2,1,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(is_plus && chain(i-1,j,1,1,0,1)&&chain(i-1,j,2,1,0,0)&&chain(i-1,j,2,2,0,0))
            {
                chain(i-1,j,1,1,turn,1);
                chain(i-1,j,2,1,turn,0);
                chain(i-1,j,2,2,turn,0);
                if(!vertical_line[i-1][j])
                {
                    vertical_line[i-1][j]=turn;
                    push_move(i-1,j,i-1,j,1,2);
                }
                if(!vertical_line[i-1][j+1])
                {
                    vertical_line[i-1][j+1]=turn;
                    push_move(i-1,j+1,i-1,j,1,2);
                }
                if(!horizontal_line[i-1][j])
                {
                    horizontal_line[i-1][j]=turn;
                    push_move(i-1,j,i-1,j,1,1);
                }
                box[i-1][j]=turn;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else 
        {
            if (horizontal_line[i][j] == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }

        }
       
       
    }

    else if (h_v == 2 && l_r == 2) // right vertical line 
    {
        if (!horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j+1] )
        {
            return 1; // important for uncompleted +
        }
        else if (j+1 < game_width && box[i][j+1] == 0)
        {
            if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+2] != 0 )
            {
                box[i][j+1] = turn;
                push_move(i,j+1,i,j+1,1,2);
                return 1;
            }
            else if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+1] == 0 )
            {
                if(turn !=0 && chain(i,j+1,2,2,turn,is_plus))
                {
                   
                    vertical_line[i][j+2] = turn;
                    push_move(i,j+2,i,j+1,1,2);
                    box[i][j+1] = turn;
                    return 1;
                }
                else if (turn ==0 && chain(i,j+1,2,2,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                
                
            }

            else if (horizontal_line[i][j+1] && vertical_line[i][j+2])
            {
                if (turn != 0 && chain(i,j+1,1,2,turn,is_plus))
                {
                    horizontal_line[i+1][j+1] = turn;
                    box[i][j+1] = turn;
                    push_move(i+1,j+1,i,j+1,1,1);
                    return 1;
                }
                else if (turn == 0 && chain(i,j+1,1,2,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (horizontal_line[i+1][j+1] && vertical_line[i][j+2])
            {
                if(turn !=0 && chain(i,j+1,1,1,turn,is_plus)){

                horizontal_line[i][j+1] = turn;
                box[i][j+1] = turn;
                push_move(i,j+1,i,j+1,1,1);
                return 1 ;}
                else if (turn ==0 && chain(i,j+1,1,1,0,is_plus))
                {
                    return 1;
                }
                
                else
                {
                    return 0;
                }
                
            }
            else if(is_plus && chain(i,j+1,2,2,0,1)&&chain(i,j+1,1,2,0,0) && chain(i,j+1,1,1,0,0))
            {
                chain(i,j+1,1,1,turn,0);
                chain(i,j+1,1,2,turn,0);
                chain(i,j+1,2,2,turn,1);
                if(!vertical_line[i][j+2])
                {
                    vertical_line[i][j+2]=turn;
                    push_move(i,j+2,i,j+1,1,2);
                }
                if(!horizontal_line[i][j+1])
                {
                    horizontal_line[i][j+1]=turn;
                    push_move(i,j+1,i,j+1,1,1);
                }
                if(!horizontal_line[i+1][j+1])
                {
                    horizontal_line[i+1][j+1]=turn;
                    push_move(i+1,j+1,i,j+1,1,1);
                }
                box[i][j+1]=turn;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else // mean i am on last box in the chain ckeck if it opened or not
        {
            if( vertical_line[i][j+1] == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }

        }
      
    }
    else // h_v == 2 l_r == 1 // vertical line to left
    {
        if (!horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j] )
        {
            return 1; // important for uncompleted +
        }
        else if(j-1 >= 0 && box[i][j-1] == 0)
        {

            if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j-1] != 0)
            {
                box[i][j-1]=turn;
                push_move(i,j,i,j-1,1,2);
                return 1;
            }
            else if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j] == 0 )
            {
                if( turn !=0 && chain(i,j-1,2,1,turn,is_plus))
                {
                
                    vertical_line[i][j-1]= turn;
                    box[i][j-1]=turn;
                    push_move(i,j-1,i,j-1,1,2);
                    return 1;
                }
                else if (turn ==0 && chain(i,j-1,2,1,0,is_plus))
                {
                    return 1;
                }
                else{
                    return 0;
                }
            }

            else if (horizontal_line[i][j-1] && vertical_line[i][j-1])
            {
                if(turn !=0 && chain(i,j-1,1,2,turn,is_plus))
                {
                horizontal_line[i+1][j-1]= turn;
                box[i][j-1]=turn;
                push_move(i+1,j-1,i,j-1,1,1);
                return 1;
                }
                else if (turn ==0 && chain(i,j-1,1,2,0,is_plus))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
        
            }
            else if (horizontal_line [i+1][j-1] && vertical_line[i][j-1])
            {
                if(turn !=0 && chain(i,j-1,1,1,turn,is_plus))
                {
                horizontal_line[i][j-1] = turn;
                box[i][j-1] = turn;
                push_move(i,j-1,i,j-1,1,1);
                return 1;
                }
                else if (turn ==0 && chain(i,j-1,1,2,0,is_plus))
                {
                    return 1;
                }
                else{
                    return 0;
                }

         
            }
            else if(is_plus &&chain(i,j-1,2,1,0,1)&&chain(i,j-1,1,1,0,0)&&chain(i,j-1,1,2,0,0))
            {
                chain(i,j-1,1,1,turn,0);
                chain(i,j-1,1,2,turn,0);
                chain(i,j-1,2,1,turn,1);
                if(!vertical_line[i][j-1])
                {
                    vertical_line[i][j-1]=turn;
                    push_move(i,j-1,i,j-1,1,2);
                }
                if(!horizontal_line[i][j-1])
                {
                    horizontal_line[i][j-1]=turn;
                    push_move(i,j-1,i,j-1,1,1);}
                if(!horizontal_line[i+1][j-1])
                {
                    horizontal_line[i+1][j-1]=turn;
                    push_move(i+1,j-1,i,j-1,1,1);
                }
                box[i][j-1]=turn;
                return 1;
            }
            else 
            {
                return 0;
            }
        }
        else 
        {
            if(vertical_line[i][j] == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            } 

        }

        
    }
    
}

void check_boxes (void)
{
    int i,j;
    for (int i = 0; i < game_height;i++)
    {
        for (int j = 0; j < game_width; j++)
        {
            if(horizontal_line[i][j] && horizontal_line[i+1][j])
            {
                if(vertical_line[i][j] && vertical_line[i][j+1])
                {
                    if(box[i][j]==0)
                    {
                        if(h_v == 1)
                        {
                            horizontal_line[i_1][j_1]=0;
                        }
                        else
                        {
                            vertical_line[i_1][j_1]=0;
                        }
                        if(i == i_1 && j == j_1)
                        {
                            push_move(i_1,j_1,i,j,chain(i, j, h_v, 1, turn,1),h_v);
                        }
                        else
                        {
                           push_move(i_1,j_1,i,j,chain(i, j, h_v, 2, turn,1),h_v);

                        }
                        box[i][j]=turn;
                        if(h_v == 1)
                        {
                            horizontal_line[i_1][j_1]=turn;
                        }
                        else
                        {
                            vertical_line[i_1][j_1]=turn;
                        }


                    }
                   
            
                }
            }
        }
    }
}

char number_of_closed_boxes()
{
    char sum = 0;
    char p1 = 0, p2 = 0;
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            if(box[i][j] == 1)
            {
                p1++;
                sum++;
            }
            else if(box[i][j] == 2)
            {
                p2++;
                sum++;
            }
        }
    }
    n_player1 = p1;
    n_player2 = p2;
    return sum;
}

void print_box_matrix()
{
    for (int i = 0; i < game_height; i++)
    {
        for (int j=0; j < game_width; j++)
        {
            printf("%d\t",box_edges[i][j]);

        }
        printf("\n");
    }
}
void zero_edges (void)
{
    for (int i = 0; i < game_height; i++)
    {
        for (int j=0; j < game_width; j++)
        {
            box_edges[i][j]=0;

        }
    }
}

///////////////////////////////////////////