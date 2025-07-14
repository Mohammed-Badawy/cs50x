#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototypes
char rotate(char c, string k);
bool check_key(string k);

// Global variable
const int KEY_LENGTH = 26;

int main(int argc, string argv[])
{
    // Check cli arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Check if valid key
    bool is_valid = check_key(key);

    if (!is_valid) // Invalid key
    {
        return 1;
    }

    // Prompt for plaintext
    string plaintext = get_string("Plaintext:  ");

    // Cipher text char by char
    printf("ciphertext: ");

    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

char rotate(char c, string k)
{
    int index; 

    // Uppercase
    if (isupper(c))
    {
        index = (int) c - (int) 'A';
        return toupper(k[index]);
    }
    // Lowercase
    else if (islower(c))
    {
        index = (int) c - (int) 'a';
        return tolower(k[index]);
    }

    // other chars
    return c;
}

bool check_key(string k)
{
    // Key length
    if (strlen(k) != KEY_LENGTH)
    {
        printf("Key must contain %i characters.\n", KEY_LENGTH);
        return false;
    }

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        // Not alpha char
        if (!isalpha(k[i]))
        {
            printf("Key must contain only alphabetical characters.\n");
            return false;
        }

        // Duplicate chars
        for (int j = i + 1; j < KEY_LENGTH; j++)
        {
            if (toupper(k[i]) == toupper(k[j]))
            {
                printf("Key mustn't contain duplicate characters.\n");
                return false;
            }
        }
    }
    // Valid key
    return true;
}