// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

unsigned int words_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get word hash in the hash table
    unsigned int hash_num = hash(word);

    // Iterate through hash table to find the word
    for (node *n = table[hash_num]; n != NULL; n = n->next)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // djb2 algorithm hash function
    // hash = (hash * 33) + c
    unsigned long hash = 5381; // Initial value
    int c;
    
    // Update the hash for each ASCII char
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dic = fopen(dictionary, "r");
    
    if (dic == NULL)
    {
        return false;
    }

    // Read each word in the file
    char *word = malloc((LENGTH + 1) * sizeof(char));
    if (word == NULL)
    {
        fclose(dic);
        return false;
    }

    while (fscanf(dic, "%s", word) != EOF)
    {
        // New node 
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dic);
            free(word);
            return false;
        }

        // Copy word to node
        strcpy(n->word, word);

        // Hash word
        int hash_num = hash(word);

        // Check if there is no node in this hash table position
        if (table[hash_num] == NULL)
        {
            n->next = NULL;
        }
        // Has nodes
        else
        {
            n->next = table[hash_num];
        }

        table[hash_num] = n;
        words_count++;
    }

    // Close the dictionary file
    fclose(dic);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the hash table 
    for (int i = 0; i < N; i++)
    {
        // Check if empty
        if (table[i] == NULL)
        {
            continue;
        }

        node *n = table[i];

        while (n != NULL)
        {
            node *next = n->next;
            free(n);
            n = next;
        }   
    }
    return true;
}
