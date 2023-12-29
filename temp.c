#include "data.h"
#include "filling_data.h"
char name[30] = "   jkjkjk ADDDfhgg     ui  ";
void shift_n (char * name, int i, int n)
{
    int len =strlen(name);
    for(int j = i; j < len ; j++ )
    {
        name[j] = name [j+n];
    }
}
void name_format (char * name)
{
    int i = 0,j = 0;
    // capitilize each start of word and make else lower
    for(i = 0; i < strlen(name); i++)
    {
        if(i == 0 || isspace(name[i-1]))
        {
            name[i]=toupper(name[i]);
            j=i+1;
            while(!isspace(name[j]) && j < strlen(name))
            {
                name[j] = tolower(name[j]);
                j++;
                
            }
        }
    }
    // leave only on space between each word 

    i = 0;
    while(name[i]!='\0')
    {
        if(isspace(name[i]) && isspace(name[i+1]))
        {
            int count=0;
            j=i+1;
            while(isspace(name[j]))
            {
                count++;
                j++;
            }
            shift_n(name,i+1,count);
        }
        i++;
    }
    // previos loop will leave last space if some spaces are at the end and space at 1st char
    if(isspace(name[strlen(name)-1]))
    {
        name[strlen(name)-1]='\0';
    }
    if(isspace(name[0]))
    {
        shift_n(name,0,1);
    }


}



int main(void)
{
    name_format(name);
    strcat(name,"^");
    printf("%s\n",name);
}