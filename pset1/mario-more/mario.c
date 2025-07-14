#include <cs50.h>
#include <stdio.h>

// Prototypes
void print_row(int n, char s);

int main(void)
{
    // Prompt user for integer between 1 & 8
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Draw pyramids of that height
    for (int i = 0; i < height; i++)
    {
        // Draw a row of right-aligned pyramid
        print_row(height - i - 2, ' '); // spaces
        print_row(i, '#');              // bricks

        // two spaces between pyramids
        printf("  ");

        // Draw a row if left-aligned pyramid
        print_row(i, '#');

        // New row
        printf("\n");
    }   
}

// Print a row of specific symbol
void print_row(int n, char s)
{
    for (int i = 0; i <= n; i++)
    {
        printf("%c", s);
    }
}