#include <stdo.h>
#include <cs50.h>

const int TOTAL = 3;
int main (void)
{
    //without arrays. heres how wed code it
    // int score1 = 72;
    // int score2 = 33;
    // int score3 = 34;
   // int TOTAL = get_int(" number of scores?: ");
   // int scores[TOTAL];

   // for(int a=0; a<3; a++)
   // {
         scores[a] = get_int("score: ");
  //  }

    printf("average: %f\n", average(TOTAL, scores));
}

float average(int lenght, int array[])
{
   int sum = 0;
   for (int a = 0; a < lenght; a++)
   {
       sum += array[a];
   }
   return sum/(float) lenght;
}