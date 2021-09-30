#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
// Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

// Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
     else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

// TODO: Print the winner
}

int compute_score(string word)
//seeing as 65 is the ASCII code for uppercase A
//seeing as 97 is the ASCII code for lowercase a
{
    int add = 0;
    int number;
    int a = strlen(word);
    for (int i = 0; i < a; i++)
    {
        if (isupper(word[i]))
        {
            number = word[i] - 65;
            number = POINTS[number];

        }
        if (islower(word[i]))
        {
            number = word[i] - 97;
            number = POINTS[number];
        }
        else
        {
            number = 0;
        }

        add = add + number;
    }
    return add;
}