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

int numChars(char *word, char c, int length);

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

        // printf("%s\n", word); // Word to guess

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
                        char colourArr[WORD_LENGTH] = {0};

                        // Initialise all entries to NORMAL
                        for(int i = 0; i < WORD_LENGTH; i++)
                        {
                            colourArr[i] = 'N';
                        }

                        charsCorrect = 0;

                        // Determine correctness of each character
                        for(int i = 0; i < WORD_LENGTH; i++)
                        {
                            int numCharAnswer = numChars(word, guess[i], WORD_LENGTH);
                            int currCharGuess = numChars(guess, guess[i], i + 1);
                            
                            if(guess[i] == word[i])
                            {
                                colourArr[i] = 'G';
                                charsCorrect++;

                                // If too many colour chars and have green
                                // then remove a yellow
                                if(currCharGuess > numCharAnswer)
                                {
                                    bool removed_yellow = false;

                                    for(int j = i - 1; j >= 0 && !removed_yellow; j--)
                                    {
                                        if(guess[j] == guess[i] && colourArr[j] == 'Y')
                                        {
                                            colourArr[j] = 'N';
                                            removed_yellow = true;
                                        }
                                    }
                                }
                            }
                            else if(numChars(word, guess[i], WORD_LENGTH))
                            {
                                // only colour yellow if we need more yellow.
                                if(currCharGuess <= numCharAnswer)
                                {
                                    colourArr[i] = 'Y';
                                }
                            }
                        }
                        attempts++;

                        // Print Results of Colour Array
                        for(int i = 0; i < WORD_LENGTH; i++)
                        {
                            if(colourArr[i] == 'N')
                            {
                                printf("■");
                            }
                            else if(colourArr[i] == 'Y')
                            {
                                printf("%s■%s", YELLOW, NORMAL);
                            }
                            else
                            {
                                printf("%s■%s", GREEN, NORMAL);
                            }
                        }
                        // Print Attemp Number
                        printf("\t%d/%d\n", attempts, MAX_ATTEMPTS);

                        // Check for win or fail
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

        fclose(answers);
        fclose(guesses);
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

int numChars(char *word, char c, int length)
{
    int numChars = 0;

    for(int i = 0; i < length; i++)
    {
        if(word[i] == c)
        {
            numChars++;
        }
    }

    return numChars;
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