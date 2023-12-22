#include "filling_data.h"

#define RESET_ALL           "\x1b[0m"
#define COLOR_RED           "\x1b[31m"
#define COLOR_BLUE          "\x1b[34m"
#define BACKGROUND_RED      "\x1b[41m"
#define BACKGROUND_BLUE     "\x1b[44m"
#define HORIZONTAL_LINE     "-------"
#define VERTICAL_LINE       "|"
#define SPACE               "       "
#define HEIGHT_OF_VERT_LINE 3
#define DOT                 "+"

void dot()
{
    printf(DOT);
}

void new_line(int number)
{
    for(int i = 0; i < number; i++)
    {
        printf("\n");
    }
}

void space(int number)
{
    for(int i = 0; i < number; i++)
    {
        printf(" ");
    }
}

void print_area(int i, int j)
{
    if(box[i][j] == 1)
    {
        printf(BACKGROUND_RED SPACE RESET_ALL);
    }
    else if (box[i][j] == 2)
    {
        printf(BACKGROUND_BLUE SPACE RESET_ALL);
    }
    else
    {
        printf(SPACE);
    }
}

void print_hor_line(int i, int j)
{
    if(horizontal_line[i][j] == 1)
    {
        printf(COLOR_RED HORIZONTAL_LINE RESET_ALL);
    }
    else if (horizontal_line[i][j] == 2)
    {
        printf(COLOR_BLUE HORIZONTAL_LINE RESET_ALL);
    }
    else
    {
        printf(SPACE);
    }
}

void print_vert_line(int i, int j)
{
    if(vertical_line[i][j] == 1)
    {
        printf(COLOR_RED VERTICAL_LINE RESET_ALL);
    }
    else if (vertical_line[i][j] == 2)
    {
        printf(COLOR_BLUE VERTICAL_LINE RESET_ALL);
    }
    else
    {
        space(1);
    }
}

void print_vert_line_indexes()
{
    space(3);
    for(int i = 1; i <= game_width + 1; i++)
    {
        printf("%i" SPACE, i);
    }
    new_line(1);
}

void print_row(int i)
{
    printf("%i", i + 1);
    space(2);
    dot();
    for(int j = 0; j < game_width; j++)
    {
        print_hor_line(i, j);
        dot();
    }
    new_line(1);
}

void print_coloum(int i)
{
    for(int h = 0; h < HEIGHT_OF_VERT_LINE; h++)
    {
        space(3);
        for(int j = 0; j < game_width; j++)
        {
            print_vert_line(i, j);
            print_area(i, j);
        }
        print_vert_line(i, game_width);
        new_line(1);
    }
}

void print_grid()
{
    print_vert_line_indexes();
    for(int i = 0; i < game_height; i++)
    {
        print_row(i);
        print_coloum(i);
    }
    print_row(game_height);
}
