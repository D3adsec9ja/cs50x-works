#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    //check if vote is valid
    bool seen = false;
    for (int a = 0; candidate_count > a; a++)
    {
        if (strcmp(name, candidates[a].name) == 0)
        {
            // When valid record in preferences array
            preferences[voter][rank] = a;
            seen = true;
            break;
        }
    }
    return seen;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // if vote was wasnt valid,skip to next preference
    for (int b = 0; b < voter_count; b++)
    {
        for (int c = 0; c < candidate_count; c++)
        {
            int d = preferences[b][c];
            if (candidates[d].eliminated == false)
            {
                candidates[d].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Check if candidate vote is 50% or higher
    for (int d = 0; candidate_count > d; d++)
    {
        if (candidates[d].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[d].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //cof= count of votes
    int cof = voter_count;
    for (int d = 0; candidate_count > d; d++)
    {
        if (cof > candidates[d].votes && candidates[d].eliminated == false)
        {
            cof = candidates[d].votes;
        }
    }
    return cof;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //check to see if its a tie
    int tie = 0;
    int Runing = 0;

    for (int d = 0; candidate_count > d; d++)
    {
        if (candidates[d].eliminated == false && candidates[d].votes == min)
        {
            tie++;
            Runing++;
        }

        else if (candidates[d].eliminated == false)
        {
            Runing++;
        }
    }
    // last Check for tie
    if (tie == Runing)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// to eliminate the candidate in last place
void eliminate(int min)
{
    //eliminate all that have min vote count
    for (int d = 0; candidate_count > d; d++)
    {
        if (candidates[d].eliminated == false && candidates[d].votes == min)
        {
            candidates[d].eliminated = true;
        }
    }
}
