#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_INPUT_LENGTH 50
#define NUM_ANSWERS 2309
#define NUM_GUESSES 14855

#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define NORMAL "\033[0m"

bool arrContainsWord(char arr[NUM_GUESSES][WORD_LENGTH + 1], char *word);

bool wordHasCharacter(char *word, char c, int length);

int getInputLength(char line[]);

int main(int argc, char **argv)
{
    FILE *answers = fopen("possible-answers.txt", "r");
    FILE *guesses = fopen("valid-guesses.txt", "r");

    if(answers != NULL && guesses != NULL)
    {
        // Choose a random word from the list
        srand(time(NULL));
        int word_line = 1 + rand() % (NUM_ANSWERS - 1);
        char word[WORD_LENGTH + 1] = {0};

        int len = 0;
        for(int i = 0; i < word_line - 1; i++)
        {
            len = fread(word, sizeof(char), WORD_LENGTH + 1, answers);
        }
        word[WORD_LENGTH] = '\0';

        // printf("%s\n", word) // Word to guess

        // Ensure that we read in 5 characters
        if(len - 1 == WORD_LENGTH)
        {
            char guess[MAX_INPUT_LENGTH] = {0};

            bool gameOn = true;
            int charsCorrect;
            int attempts = 0;

            // Add contents of guesses file to an array
            char guess_arr[NUM_GUESSES][WORD_LENGTH + 1] = {0};
            char temp[WORD_LENGTH + 1] = {0};

            for(int i = 0; i < NUM_GUESSES; i++)
            {
                fread(temp, sizeof(char), WORD_LENGTH + 1, guesses);
                temp[WORD_LENGTH] = '\0';
                strcpy(guess_arr[i], temp);
            }

            printf("Guess the word!\n");

            while(gameOn)
            {
                fgets(guess, MAX_INPUT_LENGTH, stdin); // Get input
                
                // Ensure user's guess has 5 characters
                if(getInputLength(guess) == WORD_LENGTH)
                {
                    
                    // Ensure the user's guess is valid
                    if(arrContainsWord(guess_arr, guess))
                    {
                        charsCorrect = 0;

                        for(int i = 0; i < WORD_LENGTH; i++)
                        {
                            if(guess[i] == word[i])
                            {
                                printf("%s■%s", GREEN, NORMAL);
                                charsCorrect++;
                            }
                            else if(wordHasCharacter(word, guess[i], WORD_LENGTH))
                            {
                                printf("%s■%s", YELLOW, NORMAL);
                            }
                            else
                            {
                                printf("■");
                            }
                        }
                        attempts++;
                        printf("\t%d/%d\n", attempts, MAX_ATTEMPTS);


                        if(charsCorrect == WORD_LENGTH)
                        {
                            gameOn = false;
                            printf("YOU WON!\n");
                        }
                        else if(attempts == MAX_ATTEMPTS)
                        {
                            gameOn = false;
                            printf("You Failed. The word was %s\n", word);
                        }
                    }
                    else
                    {
                        printf("Guess is not in word list.\n");
                    }
                }
                else
                {
                    printf("Word entered must have %d characters\n", WORD_LENGTH);
                }
            }
        }
        else
        {
            printf("Word read did not have %d characters\n", WORD_LENGTH);
        }
    }
    else
    {
        printf("Failed to open one or more files.\n");
    }

    return EXIT_SUCCESS;
}

// Binary Search
bool arrContainsWord(char arr[NUM_GUESSES][WORD_LENGTH + 1], char *word)
{
    bool hasWord = false;
    int start = 0;
    int end = NUM_GUESSES;
    int middle;

    while(!hasWord && start <= end)
    {
        middle = (start + end) / 2;

        int compare = strcmp(word, arr[middle]);

        if(compare < 0)
        {
            end = middle - 1;
        }
        else if(compare > 0)
        {
            start = middle + 1;
        }
        else
        {
            hasWord = true;
        }
    }
    return hasWord;
}

bool wordHasCharacter(char *word, char c, int length)
{
    bool hasChar = false;
    int idx = 0;

    while(!hasChar && idx < length)
    {
        if(word[idx] == c)
        {
            hasChar = true;
        }
        idx++;
    }

    return hasChar;
}

int getInputLength(char line[])
{
    int length = 0;
    
    while(line[length] != '\n')
    {
        length++;
    }
    line[length] = '\0';

    return length;
}
