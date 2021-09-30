// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];

unsigned int dwords = 0;

unsigned int hCode = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hCode = hash(word);
    node *pointer = table[hCode];

    while (pointer != NULL)
    {
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int a;

    while ((a = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + a; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    char word[LENGTH + 1];
    FILE *dword = fopen(dictionary, "r");
    if (dword != NULL)
    {
        while (fscanf(dword, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n != NULL)
            {
                hCode = hash(word);
                strcpy(n->word, word);
                n->next = table[hCode];
                table[hCode] = n;
                // free(n);
                dwords ++;
            }

        }
        fclose(dword);
    }
    else
    {
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  for (int b = 0; b < N; b++)
    {
        node *pointer = table[b];

        while (pointer)
        {
            node *temp = pointer;
            pointer = pointer->next;
            free(temp);
        }

        if (b == N - 1 && pointer == NULL)
        {
            return true;
        }
    }
    return false;
}
