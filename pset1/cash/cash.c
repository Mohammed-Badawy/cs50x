#include <cs50.h>
#include <stdio.h>

// Prototypes
int count_coins(int cents);

int main(void)
{
    // Prompt user for integer greater than 0
    int cents = 0;

    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents <= 0);

    // Print number of owed coins
    printf("%i\n", count_coins(cents));
}

// Count coins
int count_coins(int cents)
{
    // valid coin types 
    int quarters = 0, dimes = 0, nickles = 0, pennies = 0;

    // Count quarters
    quarters = cents / 25;
    cents %= 25;

    // Count dimes
    dimes = cents / 10;
    cents %= 10;

    // Count nickles
    nickles = cents / 5;
    cents %= 5;

    // Count pennies
    pennies = cents / 1;

    return (quarters + dimes + nickles + pennies);
}