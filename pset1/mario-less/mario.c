#include <cs50.h>
#include <stdio.h>

// Prototypes
void print_row(int n, char s);

int main(void)
{
    // Prompt the user for a positive height
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Draw right-aligned pyramid
    for (int i = 0; i < height; i++)
    {
        // Draw a row of white spaces
        print_row(height - i - 2, ' ');

        // Draw a row of bricks of size i
        print_row(i, '#');

        // new row
        printf("\n");
    }   
}

// print a row of specific symbol
void print_row(int n, char s)
{
    for (int i = 0; i <= n; i++)
    {
        printf("%c", s);
    }
}