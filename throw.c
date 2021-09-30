
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


node *table[N];


unsigned int dict = 0;

unsigned int hashCode = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    hCode = hash(word);
    node *cursor = table[hCode];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

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

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *dic = fopen(dictionary, "r");
    if (dic != NULL)
    {
        while (fscanf(dic, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n != NULL)
            {
                hCode = hash(word);
                strcpy(n->word, word);
                n->next = table[hCode];
                table[hCode] = n;
                // free(n);
                dict ++;
            }

        }
        fclose(dic);
    }
    else
    {
        return false;
    }
    return true;
}

unsigned int size(void)
{
    return dict;
}

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *pointer = table[i];

        while (pointer)
        {
            node *tmp = pointer;
            pointer = pointer->next;
            free(tmp);
        }

        if (i == N - 1 && pointer == NULL)
        {
            return true;
        }
    }
    return false;
}