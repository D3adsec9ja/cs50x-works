#include <cs50.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    //  Prompt for start size
    int pop;
    do
    {
        pop = get_int("whats your starting population? ");
    }
    while (pop < 9);

    //  Prompt for end size
    int end;
    do
    {
        end = get_int("whats your ending population? ");
    }
    while (end < pop);

    //  Calculate number of years until we reach threshold
    int amount = 0;
     while (pop < end )
     {
        pop = pop + (pop / 3) - (pop / 4);
        amount++;
     }

        printf("Years: %i\n", amount++);



}