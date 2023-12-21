#include <stdio.h>
#include <stdlib.h>

#define game_height 3 //the height of the game in boxes (number of rows of boxes)
#define game_width 3 //the width of the game in boxes (number of columns of boxes)



void fill_data_into_matrices(char values[],char horizontal_line[game_height + 1][game_width], char vertical_line[game_height][game_width +1], char turn, char* i_1, char* j_1)
{
    if(values[0] == values[1])
    {
        if(values[2] < values[3])
        {
            horizontal_line[values[0]][values[2]] = turn;
            *i_1 = values[0];
            *j_1 = values[2];
        }
        else
        {
            horizontal_line[values[0]][values[3]] = turn;
            *i_1 = values[0];
            *j_1 = values[3];
        }
    }
    else if(values[2] == values[3])
    {
        if(values[0] < values[1])
        {
            vertical_line[values[0]][values[2]] = turn;
            *i_1 = values[0];
            *j_1 = values[2];
        }
        else
        {
            vertical_line[values[1]][values[2]] = turn;
            *i_1 = values[1];
            *j_1 = values[2];
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

void Zeroing_matrices(char horizontal_line[game_height + 1][game_width],char vertical_line[game_height][game_width + 1])
{
    for(int i = 0; i < game_height; i++)
    {
        for(int j = 0; j < game_width +1; j++)
        {
            vertical_line[i][j] = 0;
        }
    }
    for(int i = 0; i < game_height + 1; i++)
    {
        for(int j = 0; j < game_width; j++)
        {
            horizontal_line[i][j] = 0;
        }
    }
}

void print_matrices(char horizontal_line[game_height + 1][game_width],char vertical_line[game_height][game_width +1])
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
    int play,c;
    do {
        printf("Enter valid place: ");
        c = scanf("%d", &play);

        if (c != 1) {
            while (getchar() != '\n');  // clear the input buffer to avoid infinite loop
            // if input is not integer clear the buffer before entering new loop
        }

    } while (c != 1);
   
    char r1,r2,c1,c2;
    r1 = play / 1000;
    r2 = play % 1000 / 100;
    c1 = play %100 / 10;
    c2 = play % 10;
    if(play < 1000 || play > 10000)
    {
        while (getchar() != '\n'); 
        // clear buffer here because if user input 12355.8 or 23/78 or 12frff
        // scanf read till point and rest remain in buffer and lead to douple print
        return scan_validity();
    }
    else if ( r1==r2 & r1==0  | c1==c2 & c1==0 )
    {
        while (getchar() != '\n');
        return scan_validity();
    }
    else if (!( (r1==r2) ^ (c1==c2) ))
    {
        while (getchar() != '\n');
        return scan_validity();
    }
    else if ((r1 > game_height+1) ||(r2 > game_height + 1) ||(c1 > game_width + 1)||(c2 > game_width + 1) )
    {
        while (getchar() != '\n');
       return scan_validity(); 
    }
    else if ((r1==r2 & abs(c1-c2)!=1) || (c1==c2  & abs(r1-r2)!=1))
    {
        while (getchar() != '\n');
        return scan_validity(); 
    }
    
    else
    {  
        while (getchar() != '\n'); // clear buffer for the next input
        char *s = malloc(4 * sizeof(char));
        s[0]=r1-1;
        s[1]=r2-1;
        s[2]=c1-1;
        s[3]=c2-1;
        return s;
    }  
}


char * check_if_line_exist (char values[],char horizontal_line[game_height + 1][game_width],char vertical_line[game_height][game_width +1])
// check if the valid index is not played before during the game and force player to input valid cell
{
    if(values[0] == values[1])
    {
        if(values[2] < values[3] & horizontal_line[values[0]][values[2]] !=0 )
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity(),horizontal_line, vertical_line);   
        }
        else if (values[2] > values[3] & horizontal_line[values[0]][values[3]] !=0 )
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity(),horizontal_line,vertical_line);
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
            return check_if_line_exist(scan_validity(),horizontal_line,vertical_line);
        }
        else if (values[0] > values[1] & vertical_line[values[1]][values[2]] != 0)
        {
            printf("choose empty cell\n");
            return check_if_line_exist(scan_validity(), horizontal_line, vertical_line );
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


char chain (int i, int j,char h_v,char l_r,char horizontal_line [game_height+1][game_width], char vertical_line [game_height][game_width+1],char box[game_height][game_width],char turn)
{
    // h_v = 1 mean horizontal, 2 vertical line 
    // l_r = 1 mean left or up l_r = 2 mean right or down


    if( h_v == 1 && l_r == 2 ) // under horizontal line
    {
        if (i + 1 < game_height && box[i+1][j] == 0 ) // there it's box below me so check possible cases
        {
            if(vertical_line[i+1][j] && vertical_line[i+1][j+1])// | |
            {
                if(chain(i+1,j,1,2,horizontal_line,vertical_line,box,turn) &&  turn !=0 ) // check chain for box below me
                {
                horizontal_line[i+2][j] = turn;
                box [i+1][j] = turn;
                return 1;
                }
                else if((chain(i+1,j,1,2,horizontal_line,vertical_line,box,turn) &&  turn ==0 ))// mean dry searching
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
                if(chain(i+1,j,2,2,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                vertical_line[i+1][j+1] = turn;
                box[i+1][j] =turn;
                return 1; 
                }
                else if(chain(i+1,j,2,2,horizontal_line,vertical_line,box,turn) && turn ==0) //dry searching
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
                if(chain(i+1,j,2,1,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                vertical_line[i+1][j] = turn;
                box[i+1][j] = turn;
                return 1;
                }
                else if((chain(i+1,j,2,1,horizontal_line,vertical_line,box,turn) && turn ==0))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(chain(i+1,j,1,2,horizontal_line,vertical_line,box,0)&&chain(i+1,j,2,1,horizontal_line,vertical_line,box,0)&&chain(i+1,j,2,2,horizontal_line,vertical_line,box,0))
            {// + like chain
    
                chain(i+1,j,1,2,horizontal_line,vertical_line,box,turn);
                chain(i+1,j,2,1,horizontal_line,vertical_line,box,turn);
                chain(i+1,j,2,2,horizontal_line,vertical_line,box,turn);
                if(!vertical_line[i+1][j]){vertical_line[i+1][j]=turn;}
                if(!vertical_line[i+1][j+1]){vertical_line[i+1][j+1]=turn;}
                if(!horizontal_line[i+2][j]){horizontal_line[i+2][j]=turn;}
                box[i+1][j]=turn;
                return 1;
            }
            else if (vertical_line[i][j] && vertical_line[i][j+1]) // mean box below me and i closed chain or not 
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
        if(i-1 >= 0 && box[i-1][j]==0) // above horizontal line
        {
            if(vertical_line[i-1][j] && vertical_line[i-1][j+1])
            {
                if(chain(i-1,j,1,1,horizontal_line,vertical_line,box,turn) && turn != 0)
                {
                horizontal_line[i-1][j] = turn;
                box[i-1][j] = turn;
                return 1;
                }
                else if (chain(i-1,j,1,1,horizontal_line,vertical_line,box,turn) && turn == 0)
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
                if(chain(i-1,j,2,2,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                vertical_line [i-1][j+1] = turn;
                box[i-1][j] = turn;
                return 1;
                }
                else if (chain(i-1,j,2,2,horizontal_line,vertical_line,box,turn) && turn ==0)
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
                if(chain(i-1,j,2,1,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                vertical_line[i-1][j] = turn;
                box[i-1][j] = turn;
                return 1;
                }
                else if (chain(i-1,j,2,1,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(chain(i-1,j,1,1,horizontal_line,vertical_line,box,0)&&chain(i-1,j,2,1,horizontal_line,vertical_line,box,0)&&chain(i-1,j,2,2,horizontal_line,vertical_line,box,0))
            {
                chain(i-1,j,1,1,horizontal_line,vertical_line,box,turn);
                chain(i-1,j,2,1,horizontal_line,vertical_line,box,turn);
                chain(i-1,j,2,2,horizontal_line,vertical_line,box,turn);
                if(!vertical_line[i-1][j]){vertical_line[i-1][j]=turn;}
                if(!vertical_line[i-1][j+1]){vertical_line[i-1][j+1]=turn;}
                if(!horizontal_line[i-1][j]){horizontal_line[i-1][j]=turn;}
                box[i-1][j]=turn;
                return 1;
            }
            else if (vertical_line[i][j] && vertical_line[i][j+1])
            {
                if (horizontal_line[i][j] == 0)
                {
                    return 0;
                }
                else {
                    return 1;
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
                else {
                    return 1;
                }

        }
       
    }

    else if (h_v == 2 && l_r == 2) // right vertical line 
    {
        if (j+1 < game_width && box[i][j+1] == 0)
        {
            if (horizontal_line[i][j+1] && horizontal_line[i+1][j+1])
            {
                if(chain(i,j+1,2,2,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                vertical_line[i][j+2] = turn;
                box[i][j+1] = turn;
                return 1;
                }
                else if (chain(i,j+1,2,2,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                else{
                    return 0;
                }
                
                
            }

            else if (horizontal_line[i][j+1] && vertical_line[i][j+2])
            {
                if (chain(i,j+1,1,2,horizontal_line,vertical_line,box,turn) && turn != 0)
                {
                    horizontal_line[i+1][j+1] = turn;
                    box[i][j+1] = turn;
                    return 1;
                }
                else if (chain(i,j+1,1,2,horizontal_line,vertical_line,box,turn) && turn ==0)
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
                if(chain(i,j+1,1,1,horizontal_line,vertical_line,box,turn) && turn !=0){

                horizontal_line[i][j+1] = turn;
                box[i][j+1] = turn;
                return 1 ;}
                else if (chain(i,j+1,1,1,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                
                else
                {
                    return 0;
                }
                
            }
            else if(chain(i,j+1,1,1,horizontal_line,vertical_line,box,0)&&chain(i,j+1,1,2,horizontal_line,vertical_line,box,0)&&chain(i,j+1,2,2,horizontal_line,vertical_line,box,0))
            {
                chain(i,j+1,1,1,horizontal_line,vertical_line,box,turn);
                chain(i,j+1,1,2,horizontal_line,vertical_line,box,turn);
                chain(i,j+1,2,2,horizontal_line,vertical_line,box,turn);
                if(!vertical_line[i][j+2]){vertical_line[i][j+2]=turn;}
                if(!horizontal_line[i][j+1]){horizontal_line[i][j+1]=turn;}
                if(!horizontal_line[i+1][j+1]){horizontal_line[i+1][j+1]=turn;}
                box[i][j+1]=turn;
                return 1;
            }
            else if (horizontal_line[i][j] && horizontal_line[i+1][j])
            {
                if( vertical_line[i][j+1] == 0)
                {
                    return 0;
                }
                else {
                    return 1;
                } 
            }
            
            
            else{return 0;}
        }
        else // mean i am on last box in the chain ckeck if it opened or not
        {
            if( vertical_line[i][j+1] == 0)
                {
                    return 0;
                }
                else {
                    return 1;
                }

        }
    
    }
    else // h_v == 2 l_r == 1 // vertical line to left
    {

        if(j-1 >= 0 && box[i][j-1] == 0)
        {
            if(horizontal_line[i][j-1] && horizontal_line[i+1][j-1])
            {
                if(chain(i,j-1,2,1,horizontal_line,vertical_line,box,turn) && turn != 0){
                vertical_line[i][j-1]= turn;
                box[i][j-1]=turn;
                return 1;
                }
                else if (chain(i,j-1,2,1,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                else{
                    return 0;
                }
            }

            else if (horizontal_line[i][j-1] && vertical_line[i][j-1])
            {
                if(chain(i,j-1,1,2,horizontal_line,vertical_line,box,turn) && turn !=0)
                {
                horizontal_line[i+1][j-1]= turn;
                box[i][j-1]=turn;
                return 1;
                }
                else if (chain(i,j-1,1,2,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                else{
                    return 0;
                }
        
            }
            else if (horizontal_line [i+1][j-1] && vertical_line[i][j-1])
            {
                if(chain(i,j-1,1,2,horizontal_line,vertical_line,box,turn)&& turn !=0 )
                {
                horizontal_line[i][j-1] = turn;
                box[i][j-1] = turn;
                return 1;
                }
                else if (chain(i,j-1,1,2,horizontal_line,vertical_line,box,turn) && turn ==0)
                {
                    return 1;
                }
                else{
                    return 0;
                }

         
            }
            else if(chain(i,j-1,1,1,horizontal_line,vertical_line,box,0)&&chain(i,j-1,1,2,horizontal_line,vertical_line,box,0)&&chain(i,j-1,2,1,horizontal_line,vertical_line,box,0))
            {
                chain(i,j-1,1,1,horizontal_line,vertical_line,box,turn);
                chain(i,j-1,1,2,horizontal_line,vertical_line,box,turn);
                chain(i,j-1,2,1,horizontal_line,vertical_line,box,turn);
                if(!vertical_line[i][j-1]){vertical_line[i][j-1]=turn;}
                if(!horizontal_line[i][j-1]){horizontal_line[i][j-1]=turn;}
                if(!horizontal_line[i+1][j-1]){horizontal_line[i+1][j-1]=turn;}
                box[i][j-1]=turn;
                return 1;
            }
            else if (horizontal_line[i][j] && horizontal_line[i+1][j])
            {
                if(vertical_line[i][j] == 0)
                {
                    return 0;
                }
                else return 1;
            }
            else {return 0;}
        }
        else
        {
            if(vertical_line[i][j] == 0)
                {
                    return 0;
                }
                else return 1;

        }

        
    }
    
}

void check_boxes (char horizontal_line [game_height+1][game_width], char vertical_line [game_height][game_width+1],char box[game_height][game_width],char turn,char h_v,char i_1,char j_1)
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
                        box[i][j]=turn;
                        if(i == i_1 && j == j_1)
                        {
                            chain(i,j,h_v,1,horizontal_line,vertical_line,box,turn);
                        }
                        else
                        {
                            chain(i,j,h_v,2,horizontal_line,vertical_line,box,turn);

                        }
                    }
                }
            }
        }
    }
}

int number_of_closed_boxes(char box[game_height][game_width], char *n_player1, char *n_player2)
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
    *n_player1 = p1;
    *n_player2 = p2;
    return sum;
}

void print_box_matrix(char box[game_height][game_width])
{
    for (int i = 0; i < game_height; i++)
    {
        for (int j=0; j < game_width; j++)
        {
            printf("%d\t",box[i][j]);

        }
        printf("\n");
    }
}

///////////////////////////////////////////