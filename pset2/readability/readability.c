#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Prototypes
int count_sentences(string t);
int count_words(string t);
int count_letters(string t);

int main(void)
{
    // Prompt for text
    string text = get_string("Text: ");

    // Count sentences, words, and letters
    int sentences = count_sentences(text);
    int words = count_words(text);
    int letters = count_letters(text);

    // Compute the Coleman-Liau index.
    // index = 0.0588 * L - 0.296 * S - 15.8

    float l_avg = (letters / (float) words) * 100;
    float s_avg = (sentences / (float) words) * 100;

    int index = round((0.0588 * l_avg) - (0.296 * s_avg) - 15.8);

    // Print grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Count sentences
int count_sentences(string t)
{
    int s = 0; // Sentences

    for (int i = 0, l = strlen(t); i < l; i++)
    {
        // Sentences end with {. || ! || ?}
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            s++;
        }
    }
    return s;
}

// Count words
int count_words(string t)
{
    int w = 0; // Words

    for (int i = 0, l = strlen(t); i < l; i++)
    {
        // Add new word if found space
        if (isspace(t[i]))
        {
            w++;
        }
    }
    return ++w;
}

// Count letters
int count_letters(string t)
{
    int lt = 0; // Letters

    for (int i = 0, l = strlen(t); i < l; i++)
    {
        // Alphabetical letters
        if (isalpha(t[i]))
        {
            lt++;
        }
    }
    return lt;
}