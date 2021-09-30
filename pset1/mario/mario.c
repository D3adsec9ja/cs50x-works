#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //ask for a number less than 8 but greater than 1
    float height;
    do
    {
        height = get_float("type a number for height \n");
        //making sure its stored
        //the commented code below works but kept being flagged by check50
        // printf(" %i\n", height);

    }
    while (height < 1 || height > 8);
    //r for row and c for column
    for (int r = 1; r <= height; ++r)
    {

        for (int c = height; c >= 1; c--)
        {
            if (r >= c)
            {
                printf("#");
            }

            else
            {
                printf(" ");
            }

        }
        printf("\n");
    }

}