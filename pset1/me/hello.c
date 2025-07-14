#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for a name
    string name = get_string("What's is your name? ");

    // Print greeting message for the user
    printf("hello, %s\n", name);
}