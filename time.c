#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void* function(void* number)
{
    int *num = (int *) number;
    while(1)
    {
        sleep(5);
        if(*num == 1)
        {
            break;
        }
        printf("\nEnter x!!\nx = ");
    }
}

void *scaning(void* number)
{
    int *num = (int *) number;
    scanf("%i", num);
}

int main()
{
    pthread_t thread;
    pthread_t thread2;
    
    printf("x = ");
    int played = 0;
    if(pthread_create(&thread, NULL, function, (void *) &played) != 0)
    {
        printf("errror in threading!");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&thread2, NULL, scaning, (void *) &played) != 0)
    {
        printf("errror in threading!");
        exit(EXIT_FAILURE);
    }
 if(pthread_join(thread2, NULL) != 0)
    {
        printf("errror in threading!");
        exit(EXIT_FAILURE);
    }





    printf("x===%i", played);


    


    if(pthread_join(thread, NULL) != 0)
    {
        printf("errror in threading!");
        exit(EXIT_FAILURE);
    }
   
    
    
    
    

}