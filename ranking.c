#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//used_globals
//.....................................................

char n_player1  = 23;
char n_player2 = 12; 
char player_1_name[31] = "Nourtaha"; // assume max size is  30
char player_2_name[31] = "ahmedragy"; 

//.....................................................

//new_globals
//.....................................................
#define TOTAL_NUMBER_OF_PLAYERS 100
#define MAX_LENGTH_OF_NAME 31

typedef struct{
    char name[MAX_LENGTH_OF_NAME];
    int wins;
    int boxes;
} player;

player players[TOTAL_NUMBER_OF_PLAYERS];
int records = 0;
char is_player_1_new;
char is_player_2_new;
//.....................................................

void load_ranking_file(void)
{
    FILE * ranking_file = fopen("ranking.csv", "r");
    if (ranking_file == NULL)
    {
        printf("Rankings File Did Not Open!!\n");
        exit(EXIT_FAILURE);
    } 

    int read = 0;

    do
    {
        read = fscanf(ranking_file, "%30[^,],%d,%d\n", players[records].name, &players[records].wins, &players[records].boxes);
        //fscanf() returns the number of success reads
        // 49[^,] means read a string of 49 chars unless you found a beaking point which is comma
        if(read == 3) //checking the number of success reading
        {
            records++;
        }
        if(read != 3 && !feof(ranking_file))
        {
            printf("Error In Reading The Ranking file Or File Format Is Incorrect!!\n");
            exit(EXIT_FAILURE);
        }

        if (ferror(ranking_file))//checking if there is an error in reading the file
        {
            printf("Error reading file\n");
            exit(EXIT_FAILURE); 
        }
        
    }while(!feof(ranking_file)); // feof() 1 when we reached to the end of the file  
    
    fclose(ranking_file);//closing file
}

void printing_records(void)
{
    printf("Rankings:\n");
    printf("Name\t\tWins\tboxes\n");
    for(int i = 0; i < records; i++)
    {
        printf("%s\t\t%i\t%i\n", players[i].name, players[i].wins, players[i].boxes);
    }
    printf("\n");
}

void reload_ranking_file(void)//reload must be done after loading the ranking file!!! IMPORTANT
{
    FILE * new = fopen("temp.csv", "w");//creating a new file
    if (new == NULL)
    {
        printf("Rankings File Did Not Open!!\n");
        exit(EXIT_FAILURE);
    } 

    for(int i = 0; i < records; i++) //putting the modifyed data to the new file 
    {
        fprintf(new, "%s,%i,%i\n", players[i].name, players[i].wins, players[i].boxes);
        if(ferror(new))
        {
            printf("Error Writing To The File!!\n");
            exit(EXIT_FAILURE);
        }
    }
    remove("ranking.csv"); //removing the old file
    rename("temp.csv", "ranking.csv"); //renaming the new file to the old file's name
}

void check_if_player_new()
{

}

void put_palyer_if_exist()
{

}

void put_palyer_if_dosnt_exist()
{
    
}


int main(void)
{
    load_ranking_file();
    printing_records();
    reload_ranking_file();
    printing_records();
    return 0;
}

