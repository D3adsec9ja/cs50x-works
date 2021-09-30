#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //ln = letter number
    //wn = word number
    //sn = sentence number
    //chars = characters for the words
    string chars = get_string("Text: ");
    int ln = 0;
    int wn = 1;
    int sn = 0;

    //in order to count the number of words
    for (int i = 0; i < strlen(chars); i++)
    {
        if ((chars[i] >= 'a' && chars[i] <= 'z') || (chars[i] >= 'A' && chars[i] <= 'Z'))
        {
            ln++;
        }
        else if (chars[i] == ' ')
        {
            wn++;
        }
        else if (chars[i] == '.' || chars[i] == '!' || chars[i] == '?')
        {
            sn++;
        }
    }

    //computing the  Coleman-Liau index
    //using( index = 0.0588 * L - 0.296 * S - 15.8) as the framework
    //it is multiplied by 100 for eery 100 words.
    float grade = 0.0588 * (100 * ln / (float) wn) - 0.296 * (100 * sn / (float) wn) - 15.8;
    if (grade < 16 && grade >= 0)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

}