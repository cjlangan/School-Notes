#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_INPUT_LENGTH 50
#define NUM_GUESSES 14855

#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define NORMAL "\033[0m"

// This struct will hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

void get_current_date(char *buffer, size_t buffer_size);

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

void printColouredArray(char *arr, int length);

bool arrContainsWord(char arr[NUM_GUESSES][WORD_LENGTH + 1], char *word);

int numChars(char *word, char c, int length);

int getInputLength(char line[]);

int main(int argc, char **argv)
{
    FILE *guesses = fopen("valid-guesses.txt", "r");

    if(guesses != NULL)
    {
        // Get Today's wordle from an API
        CURL *curl_handle;
        CURLcode res;

        struct MemoryStruct chunk;

        // Will be grown as needed by the realloc in WriteMemoryCallback
        chunk.memory = malloc(1);          
        chunk.size = 0;    // No data at this point

        curl_global_init(CURL_GLOBAL_ALL);

        // Initialize a curl session
        curl_handle = curl_easy_init();

        // Get the current date
        char date[11];  // YYYY-MM-DD is 10 characters + null terminator
        get_current_date(date, sizeof(date));

        // Construct the URL using the current date
        char url[100];
        snprintf(url, sizeof(url), "https://www.nytimes.com/svc/wordle/v2/%s.json", date);

        // Set the URL of the API
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);

        // Send all data to this function
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        // Pass the chunk struct to the callback function
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

        // Some servers don't like requests that are made without a user-agent field, 
        // so we provide one
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        // Perform the request
        res = curl_easy_perform(curl_handle);

        char word[WORD_LENGTH + 1]; // Holds the wordle answer from NYT
        
        // Check for errors
        if (res != CURLE_OK) 
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } 
        else 
        {
            // Parse the JSON response
            struct json_object *parsed_json;
            struct json_object *solution;

            parsed_json = json_tokener_parse(chunk.memory);
            json_object_object_get_ex(parsed_json, "solution", &solution);

            // Get the Wordle answer
            strcpy(word, json_object_get_string(solution));

            // Free the parsed JSON object
            json_object_put(parsed_json);
        }

        // Clean up
        curl_easy_cleanup(curl_handle);
        free(chunk.memory);
        curl_global_cleanup();

        // Setup -- My Code
        char final_result[WORD_LENGTH * MAX_ATTEMPTS] = {0};
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
                    // Add attempt result to final result
                    for(int i = 0; i < WORD_LENGTH; i++)
                    {
                        final_result[attempts * WORD_LENGTH + i] = colourArr[i];
                    }

                    // Print Results of Colour Array and attempts thus far
                    printColouredArray(colourArr, WORD_LENGTH);
                    attempts++;
                    printf("\t%d/%d\n", attempts, MAX_ATTEMPTS);

                    // Check for win or fail
                    if(charsCorrect == WORD_LENGTH || attempts == MAX_ATTEMPTS)
                    {
                        gameOn = false;
                        int result_length = attempts * WORD_LENGTH;
                        final_result[result_length] = '\0';
                        
                        if(charsCorrect == WORD_LENGTH)
                        {
                            printf("YOU WON!\n");
                        }
                        else
                        {
                            printf("You Failed. The word was %s\n", word);
                        }

                        printf("Final Results:\n");
                        printColouredArray(final_result, result_length);
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
        fclose(guesses);
    }
    else
    {
        printf("Failed to open one or more files.\n");
    }

    return EXIT_SUCCESS;
}

// Callback function to write data into our struct
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) 
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to get the current date in YYYY-MM-DD format
void get_current_date(char *buffer, size_t buffer_size) 
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, buffer_size, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void printColouredArray(char *arr, int length)
{
    for(int i = 0; i < length; i++)
    {
        // Check if need to print new attempt
        if(i % WORD_LENGTH == 0 && i != 0)
        {
            printf("\n");
        }

        // Print coloured square for each attempt's characters
        if(arr[i] == 'N')
        {
            printf("■");
        }
        else if(arr[i] == 'Y')
        {
            printf("%s■%s", YELLOW, NORMAL);
        }
        else
        {
            printf("%s■%s", GREEN, NORMAL);
        }
    }
    printf("\n");
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
