#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Prototypes
int get_card_digits(long credit);
int calculate_checksum(long credit);
int get_first_digits(long credit, int n);

// Global variables
const int AMEX = 15;
const int MASTERCARD = 16;
const int VISA1 = 13;
const int VISA2 = 16;

int main(void)
{
    // Prompt user for credit card number
    long card = get_long("Number: ");

    // Get number of card's digits
    int digits = get_card_digits(card);

    // Calculate checksum formula
    int checksum_value = calculate_checksum(card);

    // Check card type
    if (checksum_value != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int first_two_digits = get_first_digits(card, digits - 2);

        // check if AMEX
        if ((first_two_digits == 34 || first_two_digits == 37) && digits == AMEX)
        {
            printf("AMEX\n");
        }
        // Check if mastercard
        else if ((first_two_digits >= 51 && first_two_digits <= 55) && digits == MASTERCARD) 
        {
            printf("MASTERCARD\n");
        }
        // Check Visa
        else if ((first_two_digits / 10 == 4) && (digits == VISA1 || digits == VISA2))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

// Get digits number
int get_card_digits(long credit)
{
    int digits = 0;

    while (credit > 0)
    {
        digits++;
        credit /= 10;
    }
    return digits;
}

// Calculate checksum
int calculate_checksum(long credit)
{
    int last2second = 0, last = 0;
    bool is_second_to_last = false;

    while (credit > 0)
    {
        int last_digit = credit % 10;

        // Get second to last digit
        if (is_second_to_last)
        {
            // Calculate the product
            last_digit *= 2;

            // has two digits
            if (last_digit > 9)
            {
                last2second += (last_digit % 10);
                last2second += (last_digit / 10);
            }
            // one digit
            else
            {
                last2second += last_digit;
            }
        }
        // Get last digit sum
        else
        {
            last += last_digit;
        }
        
        // Switch label
        is_second_to_last = !is_second_to_last;

        // update card last digit
        credit /= 10;
    }
    return (last2second + last) % 10;
}

// Get first digits
int get_first_digits(long credit, int n)
{
    return (credit / pow(10, n));
}