#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int i=0;
    while (i<=50){
        printf("hello world %i\n", i);
        i++;
    }

    for (int j=0; j<3; j++) {
        printf("meow\n");
    }
}
