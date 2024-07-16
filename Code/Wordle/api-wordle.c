#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <json-c/json.h>

// This struct will hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to write data into our struct
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
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
void get_current_date(char *buffer, size_t buffer_size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, buffer_size, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int main(void) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // Will be grown as needed by the realloc in WriteMemoryCallback
    chunk.size = 0;            // No data at this point

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

    // Some servers don't like requests that are made without a user-agent field, so we provide one
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    // Perform the request
    res = curl_easy_perform(curl_handle);

    // Check for errors
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // Parse the JSON response
        struct json_object *parsed_json;
        struct json_object *solution;

        parsed_json = json_tokener_parse(chunk.memory);
        json_object_object_get_ex(parsed_json, "solution", &solution);

        // Print the Wordle answer
        printf("Wordle answer: %s\n", json_object_get_string(solution));

        // Free the parsed JSON object
        json_object_put(parsed_json);
    }

    // Clean up
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();

    return 0;
}

