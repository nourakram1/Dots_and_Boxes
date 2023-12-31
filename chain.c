#include "data.h"
#include "game.h"


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
    printf("Play or Enter E For Exit, R For Redo, U For Undo, S For Save, M For Menu : ");
    char *input = malloc(10);
    strcpy(input,scan_string(9));
    if(input[0] >= 65 && input[0] <= 90)
    {
        input[0] = input[0] - 65 + 97;
    }
    if(input [0] == 'e' || input [0] == 's' && strlen(input) == 1 )
    {
        return input;
    }
    if(input [0] == 'm' && strlen(input) == 1 )
    {
        return input;
    }

    if(input [0] == 'r' || input [0] == 'u' && strlen(input) == 1 )
    {
        return input;
    }


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
    input [0]--;
    input [1]--;
    input [2]--;
    input [3]--;

    if(check_if_line_exist(input))
    {
        return scan_validity();
    }
    else
    {
        fill_data_into_matrices(input);
        return input;
    }
 
}


char check_if_line_exist (char values[])
// check if the valid index is not played before during the game and force player to input valid cell
{
    if(values[0] == values[1])
    {
        if(values[2] < values[3] & horizontal_line[values[0]][values[2]] !=0 )
        {
            printf("choose empty cell\n");
            return 1 ;   
        }
        else if (values[2] > values[3] & horizontal_line[values[0]][values[3]] !=0 )
        {
            printf("choose empty cell\n");
            return 1;
            // double call because if user insert repeated place then insert another repeated one 
        }
        else
        {
            return 0 ;
        }
    }
    else if(values[2] == values[3])
    {
        if(values[0] < values[1] & vertical_line[values[0]][values[2]] != 0)
        {
            printf("choose empty cell\n");
            return 1;
        }
        else if (values[0] > values[1] & vertical_line[values[1]][values[2]] != 0)
        {
            printf("choose empty cell\n");
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return 0;
    }
}


char chain (int i, int j,char h_v,char l_r,char turn)
{
    // h_v = 1 mean horizontal, 2 vertical line 
    // l_r = 1 mean left or up l_r = 2 mean right or down

    if( h_v == 1 && l_r == 2 ) // under horizontal line
    {
        if (i + 1 < game_height ) // there it's box below me so check possible cases
        {
            if (vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+2][j] != 0) 
            {
                box [i+1][j] = turn;
                push_move(i+1,j,i+1,j,1,1);
                
                return 1;
            }
            else if(vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+1][j] == 0)// | |
            {
                if(chain(i+1,j,1,2,turn)) // check chain for box below me
                {
                    horizontal_line[i+2][j] = turn;
                    box [i+1][j] = turn;
                    push_move(i+2,j,i+1,j,1,1);
                    
                    return 1;
                }
                else
                {
                    return 0;
                }
                
            }

            else if (horizontal_line[i+2][j] && vertical_line[i+1][j]) // |_
            {
                if(chain(i+1,j,2,2,turn))
                {
                vertical_line[i+1][j+1] = turn;
                box[i+1][j] =turn;
                push_move(i+1,j+1,i+1,j,1,2);
                
                return 1; 
                }
                else
                {
                    return 0;
                }
                

            }
            else if (horizontal_line[i+2][j] && vertical_line[i+1][j+1]) // _|
            {
                if(chain(i+1,j,2,1,turn))
                {
                vertical_line[i+1][j] = turn;
                box[i+1][j] = turn;
                push_move(i+1,j,i+1,j,1,2);
                
                return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(dry_chain(i+1,j,1,2) && dry_chain(i+1,j,2,2)&&dry_chain(i+1,j,2,1))
            {// + like chain
    
                chain(i+1,j,1,2,turn);
                chain(i+1,j,2,1,turn);
                chain(i+1,j,2,2,turn);
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
            else if (!vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i+1][j])
            {
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
       
        if(i-1 >= 0) // above horizontal line
        {
            if (vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i-1][j] != 0)
            {
                box[i-1][j]=turn;
                push_move(i,j,i-1,j,1,1);
                
                return 1;
            }

            else if(vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i][j] == 0)
            {
                if(chain(i-1,j,1,1,turn))
                {
                
                    horizontal_line[i-1][j] = turn;
                    box[i-1][j] = turn;
                    push_move(i-1,j,i-1,j,1,1);
                    
                    return 1;
                }
                else
                {
                    return 0;
                }    
            }

            else if (horizontal_line[i-1][j] && vertical_line[i-1][j])
            {
                if(chain(i-1,j,2,2,turn))
                {
                vertical_line [i-1][j+1] = turn;
                box[i-1][j] = turn;
                push_move(i-1,j+1,i-1,j,1,2);
                
                return 1;
                }
               
                else
                {
                    return 0;
                }

            }
            else if (horizontal_line[i-1][j] && vertical_line [i-1][j+1])
            {
                if(chain(i-1,j,2,1,turn))
                {
                vertical_line[i-1][j] = turn;
                box[i-1][j] = turn;
                push_move(i-1,j,i-1,j,1,2);
                
                return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(dry_chain(i-1,j,1,1)&&dry_chain(i-1,j,2,1)&&dry_chain(i-1,j,2,2))
            {
                chain(i-1,j,1,1,turn);
                chain(i-1,j,2,1,turn);
                chain(i-1,j,2,2,turn);
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
            else if (!vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i][j])
            {
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
        if (j+1 < game_width)
        {
            if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+2] != 0 )
            {
                box[i][j+1] = turn;
                push_move(i,j+1,i,j+1,1,2);
                return 1;
            }
            else if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+1] == 0 )
            {
                if(chain(i,j+1,2,2,turn))
                {
                   
                    vertical_line[i][j+2] = turn;
                    push_move(i,j+2,i,j+1,1,2);
                    box[i][j+1] = turn;

                    return 1;
                }
                else
                {
                    return 0;
                }
                
                
            }

            else if (horizontal_line[i][j+1] && vertical_line[i][j+2])
            {
                if (chain(i,j+1,1,2,turn))
                {
                    horizontal_line[i+1][j+1] = turn;
                    box[i][j+1] = turn;
                    push_move(i+1,j+1,i,j+1,1,1);

                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (horizontal_line[i+1][j+1] && vertical_line[i][j+2])
            {
                if(chain(i,j+1,1,1,turn)){

                horizontal_line[i][j+1] = turn;
                box[i][j+1] = turn;
                push_move(i,j+1,i,j+1,1,1);
                return 1 ;}
                else
                {
                    return 0;
                }
                
            }
            else if(dry_chain(i,j+1,2,2)&&dry_chain(i,j+1,1,2) && dry_chain(i,j+1,1,1))
            {
                chain(i,j+1,2,2,turn);
                chain(i,j+1,1,1,turn);
                chain(i,j+1,1,2,turn);

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
            else if (!horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j+1])
            {
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
       
        if(j-1 >= 0)
        {

            if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j-1] != 0)
            {
                box[i][j-1]=turn;
                push_move(i,j,i,j-1,1,2);
                return 1;
            }
            else if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j] == 0 )
            {
                if(chain(i,j-1,2,1,turn))
                {
                
                    vertical_line[i][j-1]= turn;
                    box[i][j-1]=turn;
                    push_move(i,j-1,i,j-1,1,2);

                    return 1;
                }
                else{
                    return 0;
                }
            }

            else if (horizontal_line[i][j-1] && vertical_line[i][j-1])
            {
                if(chain(i,j-1,1,2,turn))
                {
                horizontal_line[i+1][j-1]= turn;
                box[i][j-1]=turn;
                push_move(i+1,j-1,i,j-1,1,1);
                return 1;
                }
                else
                {
                    return 0;
                }
        
            }
            else if (horizontal_line [i+1][j-1] && vertical_line[i][j-1])
            {
                if(chain(i,j-1,1,1,turn))
                {
                horizontal_line[i][j-1] = turn;
                box[i][j-1] = turn;
                push_move(i,j-1,i,j-1,1,1);
                return 1;
                }
                else{
                    return 0;
                }

         
            }
            else if(dry_chain(i,j-1,2,1)&&dry_chain(i,j-1,1,1)&&dry_chain(i,j-1,1,2))
            {
                chain(i,j-1,2,1,turn);
                chain(i,j-1,1,1,turn);
                chain(i,j-1,1,2,turn);
                
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
            else if(!horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j])
            {
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


char dry_chain (int i, int j,char h_v,char l_r)
{
    // h_v = 1 mean horizontal, 2 vertical line 
    // l_r = 1 mean left or up l_r = 2 mean right or down

    dfs[i][j] = 1;
    if( h_v == 1 && l_r == 2 ) // under horizontal line
    {
        if (i + 1 < game_height ) // there it's box below me so check possible cases
        {
            if (vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+2][j] != 0) 
            {
                dfs[i+1][j]=1;
                return 1;
            }
            else if(vertical_line[i+1][j] && vertical_line[i+1][j+1] && horizontal_line[i+1][j] == 0)// | |
            {
                if((dry_chain(i+1,j,1,2) ))// mean dry searching
                {
                    dfs[i+1][j]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
                
            }

            else if (horizontal_line[i+2][j] && vertical_line[i+1][j]) // |_
            {
                if(dry_chain(i+1,j,2,2)) //dry searching
                {
                    dfs[i+1][j]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
                

            }
            else if (horizontal_line[i+2][j] && vertical_line[i+1][j+1]) // _|
            {
                
                if(dry_chain(i+1,j,2,1))
                {
                    dfs[i+1][j] = 1;
                    return 1;
                }
                else
                {
                    return 0; 
                }
            }
            else if(dfs[i+1][j] == 0 && dry_chain(i+1,j,1,2) && dry_chain(i+1,j,2,2)&&dry_chain(i+1,j,2,1))
            {// + like chain
                dfs[i+1][j]=1;
                return 1;
            }
            else if (i-1>=0)
            {
                if (vertical_line[i-1][j] && vertical_line[i-1][j+1] && !vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i+1][j])
                {
                    return 1;
                }
                else 
                {
                    return 0;
                }
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
        if(i-1 >= 0 ) // above horizontal line
        {
            if (vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i-1][j] != 0)
            {
                dfs[i-1][j]=1;
                return 1;
            }

            else if(vertical_line[i-1][j] && vertical_line[i-1][j+1] && horizontal_line[i][j] == 0)
            {

                if (dry_chain(i-1,j,1,1))
                {
                    dfs[i-1][j]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }    
            }

            else if (horizontal_line[i-1][j] && vertical_line[i-1][j])
            {
        
                if (dry_chain(i-1,j,2,2))
                {
                    dfs[i-1][j]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }

            }
            else if (horizontal_line[i-1][j] && vertical_line [i-1][j+1])
            {
                if (dry_chain(i-1,j,2,1))
                {
                    dfs[i-1][j]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(dfs[i-1][j] == 0 && dry_chain(i-1,j,1,1)&&dry_chain(i-1,j,2,1)&&dry_chain(i-1,j,2,2))
            {
                dfs[i-1][j]=1;
                return 1;
            }
            else if (i+1 < game_height)
            {
                if (vertical_line[i+1][j] && vertical_line[i+1][j+1] && !vertical_line[i][j] && !vertical_line[i][j+1] && horizontal_line[i][j])
                {
                return 1;
                }
                else 
                {
                    return 0;
                }
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
     
        if (j+1 < game_width)
        {
            if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+2] != 0 )
            {
                dfs[i][j+1]=1;
                return 1;
            }
            else if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && vertical_line[i][j+1] == 0 )
            {
                
                if (dry_chain(i,j+1,2,2))
                {
                    dfs[i][j+1]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
                
                
            }

            else if (horizontal_line[i][j+1] && vertical_line[i][j+2])
            {
            
                if (dry_chain(i,j+1,1,2))
                {
                    dfs[i][j+1]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if (horizontal_line[i+1][j+1] && vertical_line[i][j+2])
            {
                
                if (dry_chain(i,j+1,1,1))
                {
                    dfs[i][j+1]=1;
                    return 1;
                }
                
                else
                {
                    return 0;
                }
                
            }
            else if(dfs[i][j+1] == 0 && dry_chain(i,j+1,2,2) && dry_chain(i,j+1,1,2) && dry_chain(i,j+1,1,1))
            {
                dfs[i][j+1]=1;
                return 1;
            }
            else if(j-1>=0)
            {
                if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && !horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j+1])
                {
                return 1;
                }
                else
                {
                    return 0;
                }
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
        if(j-1 >= 0)
        {

            if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j-1] != 0)
            {
                dfs[i][j-1]=1;
                return 1;
            }
            else if (horizontal_line[i][j-1] && horizontal_line[i+1][j-1] && vertical_line[i][j] == 0 )
            {
                
                if (dry_chain(i,j-1,2,1))
                {
                    dfs[i][j-1]=1;
                    return 1;
                }
                else{
                    return 0;
                }
            }

            else if (horizontal_line[i][j-1] && vertical_line[i][j-1])
            {
                if (dry_chain(i,j-1,1,2))
                {
                    dfs[i][j-1]=1;
                    return 1;
                }
                else
                {
                    return 0;
                }
        
            }
            else if (horizontal_line [i+1][j-1] && vertical_line[i][j-1])
            {
               if (dry_chain(i,j-1,1,1))
                {
                    dfs[i][j-1]=1;
                    return 1;
                }
                else{
                    return 0;
                }

         
            }
            else if(dfs[i][j-1] == 0 && dry_chain(i,j-1,2,1)&&dry_chain(i,j-1,1,1)&&dry_chain(i,j-1,1,2))
            {
                dfs[i][j-1]=1;
                return 1;
            }
            else if (j+1<game_width)
            {
                if(horizontal_line[i][j+1] && horizontal_line[i+1][j+1] && !horizontal_line[i][j] && !horizontal_line[i+1][j] && vertical_line[i][j])
                {
                return 1;
                }
                else
                {
                    return 0;
                }
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
                            zero_visited();
                            push_move(i_1,j_1,i,j,chain(i, j, h_v, 1, turn),h_v);
                        }
                        else
                        {
                           zero_visited();
                           push_move(i_1,j_1,i,j,chain(i, j, h_v, 2, turn),h_v);

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

void zero_visited (void)
{
    for (int i = 0; i < game_height; i++)
    {
        for (int j=0; j < game_width; j++)
        {
            dfs[i][j]=0;
            


        }
    }
}

///////////////////////////////////////////