#include "minishell.h"

void ft_countdown(void)
{
    int i;

    i = 5;
    while (--i >= 1)
    {
        if (i%2 != 0)
        {
            printf("Are you ready: %d\r, i");
            fflush(STDOUT);
            sleep(1);
        }
        else 
            {
                printf("You're in hell son!");
                fflush(STDOUT);
                sleep(1);
            }
    }
    printf("Let's go my gigot d'agneau!\n");
    return (0);
}