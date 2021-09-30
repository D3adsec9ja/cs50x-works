#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//PSEUDOCODE
//get a main thatll take two arguments, the first being one thatll take the nuber of argumnts
//and the second being one thatll take an array of strings
//then reprompt the user if he enters more than or less than 2 arguments
//then we are gong to check if the argument is alpha if not, then the user will be reprompted
//then use atoi to transform thr string to an integer
//lastly, use the formula that given to us to know the index of the letter cipher that we want




//code for two arguments in main
int main(int argc, string argv[])
{
    while (argc < 2 || argc > 2)
    {
        printf("Usage: ./ceasar k");
        return 1;
    }

    // to check for alpha
    for (int key = 0; key < strlen(argv[1]); key++)
    {
        while (isalpha(argv[1][key]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //use atoi to convert from string to int
    int keys = atoi(argv[1]) % 26;

    // prompting the user for plaintext
    string text = get_string("plaintext: ");

    //print cipher
    printf("ciphertext: ");

    for (int a = 0, n = strlen(text) ; a < n; a++)
    {

        if (text[a] >= 'a' && text[a] <= 'z')
        {
            printf("%c", (((text[a] - 'a') + keys) % 26) + 'a');
        }
        else if (text[a] >= 'A' && text[a] <= 'Z')
        {
            printf("%c", (((text[a] - 'A') + keys) % 26) + 'A');
        }

        else

        {
            printf("%c", text[a]);
        }
    }

    printf("\n");
    return 0;

}




