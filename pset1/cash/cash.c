#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    int quater = 0;
    int dime = 0;
    int nickle = 0;
    int penny = 0;
    int count = 0;
    float owed;

    // asking the user for how much owed.
    do
    {
        owed = get_float("how much are you owed \n");
    }
    while(owed < 0);


    // changing cent to dollar.
    int cents = round(owed * 100);
    printf("Change in Cent: %i\n", cents);


    while (cents >= 25)
    {
        quater++;
        cents = cents - 25;
    }
    while (cents >= 10)
    {
        dime++;
        cents = cents - 10;
    }
    while (cents >= 5)
    {
        nickle++;
        cents = cents - 5;
    }
    while (cents >= 1)
    {
        penny++;
        cents = cents - 1;
    }
    //summing up the total coins
    count = quater + dime + nickle + penny;
    printf("Total amount of coins: %i\n", count);
}
