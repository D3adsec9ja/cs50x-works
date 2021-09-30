#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //as for users name
    string name = get_string("whats your name?\n");
    printf("hello, %s\n", name);
}