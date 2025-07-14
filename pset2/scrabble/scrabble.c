#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototypes
int compute_score(string word);

// Global variables
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt for players words
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    // Compute the score of each word
    int player1_score = compute_score(player1_word);
    int player2_score = compute_score(player2_word);

    // print winner
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Compute word score
int compute_score(string word)
{
    int score = 0;

    for (int i = 0, l = strlen(word); i < l; i++)
    {
        // uppercase letters
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - (int) 'A'];
        }
        // lowercase letters
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - (int) 'a'];
        }
    }
    return score;
}