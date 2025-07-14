#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
char rotate(char c, int k);

int main(int argc, string argv[])
{
    // Check cli arguments number
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if not digits
    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Prompt user for plaintext
    string plaintext = get_string("Plaintext:  ");

    // Convert to integer
    int key = atoi(argv[1]);

    // Cipher each character in plaintext
    printf("Ciphertext: ");

    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

// Cipher character with given key
char rotate(char c, int k)
{
    char t;

    // Alphabetical char
    if (isalpha(c))
    {
        // Uppercase
        if (isupper(c))
        {
            t = ((int) c - (int) 'A' + k) % 26;
            return t + (int) 'A';
        }
        // Lowercase
        else
        {
            t = ((int) c - (int) 'a' + k) % 26;
            return t + (int) 'a';
        }
    }
    // other chars
    return c; 
}