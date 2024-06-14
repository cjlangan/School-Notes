#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "zones.h"

#define PASS "\033[0;32mPASS\033[0m: " // ANSI colour codes for green
#define FAIL "\033[0;31mFAIL\033[0m: " // ANSI colour codes for red

int tests_total = 0;
int tests_passed = 0;

void require(bool value, const char *message)
{
    if (value)
    {
        printf(PASS "%s\n", message);
        tests_passed++;
    }
    else
    {
        printf(FAIL "%s\n", message);
    }

    tests_total++;
}

void test_zone_creation(void)
{
    // Test case to ensure zone creation works
    zone *z = make_zone(1024);
    require(z != NULL, "should be able to create a zone.");
    require(zone_size(z) == 1024, "new zone size should be full size");
    destroy_zone(z);

    // Test case to ensure multiple zone creations work
    zone *z1 = make_zone(1024);
    zone *z2 = make_zone(128);
    require(z2 != NULL, "should be able to create a second zone.");
    destroy_zone(z1);
    destroy_zone(z2);

    // Test that we can create a zone that isn't divisible by 8
    zone *z3 = make_zone(17);
    require(z3 != NULL, "should be able to create a zone with an not divisible by 8 input");
    destroy_zone(z3);

    // Edge test that we can create a zone of one byte in size
    zone *z4 = make_zone(1);
    require(z4 != NULL, "should be able to create a zone of one byte in size");
    destroy_zone(z4);
}

void test_zone_allocation(void)
{
    // Ensure we can allocate all memory within the zone
    zone *z = make_zone(1024);
    void *ptr1 = zalloc(z, 256);
    void *ptr2 = zalloc(z, 256);
    void *ptr3 = zalloc(z, 256);
    void *ptr4 = zalloc(z, 256);
    require(ptr1 != NULL, "should be able to allocate memory within the zone.");
    require(ptr2 != NULL, "should be able to allocate multiple blocks within the zone.");
    require(ptr3 != NULL, "should be able to allocate even more within the zone.");
    require(ptr4 != NULL, "should be able to allocate maximum zone size."); 
    destroy_zone(z);

    // Edge case to ensure too large of an allocation returns NULL
    zone *z2 = make_zone(128);
    void *ptr5 = zalloc(z2, 129);
    require(ptr5 == NULL, "should not be able to allocate memory larger than zone.");
    destroy_zone(z2);

    // Test case to see if we can allocate a singular byte within the zone
    zone *z3 = make_zone(16);
    void *ptr6 = zalloc(z3, 1);
    require(ptr6 != NULL, "should be able to allocate a single byte within the zone.");
    destroy_zone(z3);

    // Test case to ensure that we can use allocated memory
    zone *z4 = make_zone(64);
    char *letters = zalloc(z4, 11);
    for(int i = 0; i < 10; i++)
    {
        if(i % 2 == 0)
        {
            letters[i] = 'C';
        }
        else
        {
            letters[i] = 'J';
        }
    }
    letters[11] = '\0';
    require(strcmp(letters, "CJCJCJCJCJ") == 0, "should find 'CJCJCJCJCJ' in the zone");

    char *name = zalloc(z4, 13);
    for(int i = 0; i < 12; i++)
    {
        if(i % 2 == 0)
        {
            name[i] = 'R';
        }
        else
        {
            name[i] = 'T';
        }
    }
    name[13] = '\0';
    require(strcmp(name, "RTRTRTRTRTRT") == 0, "should find 'RTRTRTRTRTRT' in the zone");
    require(strcmp(letters, "CJCJCJCJCJ") == 0, "'CJCJCJCJCJ' should still be in the zone");
    destroy_zone(z4);

    // Test that memory allocation zeroes out the memory that will be used.
    zone *z5 = make_zone(64);
    char *stuff = zalloc(z5, 8);
    for(int i = 0; i < 7; i++)
    {
        if(i % 3 == 0)
        {
            stuff[i] = 'Y';
        }
        else
        {
            stuff[i] = 'N';
        }
    }
    stuff[8] = '\0';

    unsigned char *test = zalloc(z5, 32);
    *test = 44;
    zfree(z5, stuff);
    char *more_stuff = zalloc(z5, 5);
    for(int i = 0; i < 5; i++)
    {
        require(more_stuff[i] == 0, "Allocated memory should be zeroed out.");
    }
    destroy_zone(z5);
}

void test_zone_free(void)
{
    // Test case to ensure freeing allocated memory within a zone works
    zone *z2 = make_zone(1024);
    void *ptr2 = zalloc(z2, 128);
    void *ptr3 = zalloc(z2, 128);
    void *ptr4 = zalloc(z2, 768);
    require(zfree(z2, ptr2), "should be able to free allocated memory within the zone.");
    require(zfree(z2, ptr3), "should be able to free multiple blocks within the zone.");
    require(zfree(z2, ptr4), "should be able to free all blocks within the zone.");
    destroy_zone(z2);

    // Test that we can allocate after freeing space
    zone *z3 = make_zone(128);
    void *ptr5 = zalloc(z3, 128);
    zfree(z3, ptr5);
    void *ptr6 = zalloc(z3, 128);
    require(ptr6 != NULL, "should be able to use memory within a zone after freeing");
    destroy_zone(z3);

    // Test that zfree does not zero out memory
    zone *z5 = make_zone(64);
    char *stuff = zalloc(z5, 8);
    for(int i = 0; i < 7; i++)
    {
        if(i % 3 == 0)
        {
            stuff[i] = 'Y';
        }
        else
        {
            stuff[i] = 'N';
        }
    }
    stuff[8] = '\0';
    require(strcmp(stuff, "YNNYNNY") == 0, "String should be 'YNNYNNY' before freeing");
    zfree(z5, stuff);
    require(strcmp(stuff, "YNNYNNY") == 0, "Memory should be 'YNNYNNY' after freeing");
    destroy_zone(z5);

    // Test that we do not free an invalid pointer within the zone.
    zone *z4 = make_zone(100);
    char *pointer = zalloc(z4, 50);
    require(!zfree(z4, pointer + 1), "should not be able to free an invalid pointer within the zone.");
    destroy_zone(z4);

    // Test that we can reuse a freed pointer
    zone *z6 = make_zone(300);
    unsigned char *pointer2 = zalloc(z6, 200);
    for(int i = 0; i < 200; i++)
    {
        pointer2[i] = 9;
    }
    zfree(z6, pointer2);
    pointer2 = zalloc(z6, 100);
    require(pointer2 != NULL, "should be able to reallocate a previously freed pointer.");
    require(block_size(z6, pointer2) == 100, "reallocation of a previously freed pointer"
                            " should have the new size 100 and not 200.");
    destroy_zone(z6);

    // Test that freeing a pointer twice is not possible
    zone *z7 = make_zone(9001);
    unsigned char *nums = zalloc(z7, 888);
    for(int i = 0; i < 888; i++)
    {
        nums[i] = 3;
    }
    require(zfree(z7, nums), "freeing pointer first time should work.");
    require(!zfree(z7, nums), "freeing pointer second time should NOT work.");
    destroy_zone(z7);
}

void test_first_fit(void)
{
    // Test that first fit identifies space at beginning of the zone
    zone *z1 = make_zone(64);
    void *ptr1 = zalloc(z1, 16);
    char *ptr2 = zalloc(z1, 40);
    require(ptr2 != NULL, "should be able to have a character pointer.");
    *ptr2 = 'c';
    zfree(z1, ptr1);
    void *ptr3 = zalloc(z1, 16);
    require(ptr3 != NULL, "should be able to allocate memory after freeing initial allocation.");
    require(ptr3 == ptr1, "allocation after freeing first should be same address as original");
    destroy_zone(z1);

    // Test that first fit identifies space in the middle of the zone
    zone *z2 = make_zone(48);
    char *ptr4 = zalloc(z2, 16);
    char *ptr5 = zalloc(z2, 16);
    unsigned char *ptr6 = zalloc(z2, 16);
    require(ptr6 != NULL, "should be able to have an integer pointer.");
    *ptr4 = 'a';
    *ptr6 = 1;
    zfree(z2, ptr5);
    char *ptr7 = zalloc(z2, 16);
    require(ptr7 != NULL, "should be able to allocate memory after freeing middle allocation.");
    require(ptr7 == ptr5, "allocation after freeing middle should be same address as previous middle");
    destroy_zone(z2);

    // Test that first fit identifies last space of the zone
    zone *z3 = make_zone(48);
    char *ptr8 = zalloc(z3, 16);
    char *ptr9 = zalloc(z3, 16);
    char *ptr10 = zalloc(z3, 16);
    *ptr8 = 'a';
    *ptr9 = 'b';
    zfree(z3, ptr10);
    char *ptr11 = zalloc(z3, 16);
    require(ptr11 != NULL, "should be able to allocate memory after freeing last allocation.");
    require(ptr11 == ptr10, "allocation after freeing last should be same address as previous last");
    destroy_zone(z3);

    // Test that first fit identifies that there is not enough contiguous space.
    zone *z4 = make_zone(64);
    char *pointer1 = zalloc(z4, 8);
    char *pointer2 = zalloc(z4, 8);
    char *pointer3 = zalloc(z4, 8);
    char *pointer4 = zalloc(z4, 8);
    char *pointer5 = zalloc(z4, 8);
    char *pointer6 = zalloc(z4, 8);
    char *pointer7 = zalloc(z4, 8);
    char *pointer8 = zalloc(z4, 8);
    *pointer2 = 'a';
    *pointer4 = 'b';
    *pointer6 = 'c';
    *pointer8 = 'd';
    zfree(z4, pointer1);
    zfree(z4, pointer3);
    zfree(z4, pointer5);
    zfree(z4, pointer7);
    char *new_pointer = zalloc(z4, 16);
    require (new_pointer == NULL, "should not allocate memory for new pointer despite its"
                " size being less than the available free space. (not enough contiguous memory).");
    destroy_zone(z4);
}

void test_block_size(void)
{
    // Test case to check if proper block size is returned.
    zone *z = make_zone(1024);
    void *ptr = zalloc(z, 128);
    require(block_size(z, ptr) == 128, "block size should be equal to the allocated size.");
    void *ptr2 = zalloc(z, 256);
    require(block_size(z, ptr2) == 256, "second block size should be equal to the allocated size.");
    require(block_size(z, ptr) == 128, "initial block size should not have changed.");
    destroy_zone(z);

    // Test that invalid pointer within the zone returns 0
    zone *z2 = make_zone(256);
    unsigned char *ptr3 = zalloc(z2, 128);
    *ptr3 = 18;
    require(block_size(z2, ptr3 + 1) == 0, "block size of invalid pointer in zone should return zero");
    destroy_zone(z2);
}

void test_zone_size(void)
{
    // Test case to check if zone size returned is correct.
    zone *z = make_zone(1024);
    require(zone_size(z) == 1024, "zone size should match the size passed to make_zone.");
    destroy_zone(z);

    // Test case to check that zone size is rouned up to nearest multiple of 8
    zone *z2 = make_zone(57);
    require(zone_size(z2) == 64, "zone size should be rounded up to nearest multiple of 8.");
    destroy_zone(z2);

    // Test that allocating memory within the zone does not affect zone size.
    zone *z3 = make_zone(128);
    char *ptr1 = zalloc(z3, 64);
    *ptr1 = 't';
    require(zone_size(z3) == 128, "zone size should stay the same after one allocation.");
    char *ptr2 = zalloc(z3, 64);
    *ptr2 = 'r';
    require(zone_size(z3) == 128, "zone size should stay the same after all allocations.");
    destroy_zone(z3);
}

void test_large(void)
{
    // Test case if all memory can be freed and reused multiple times and in large quantities
    zone *z = make_zone(64000);
    char *ptr1 = zalloc(z, 20000);
    char *ptr2 = zalloc(z, 20000);
    char *ptr3 = zalloc(z, 10000);
    char *ptr4 = zalloc(z, 14000);
    require(ptr1 != NULL, "should be able to allocate lots of memory within the zone.");
    require(ptr2 != NULL, "should be able to allocate lots more memory within the zone.");
    require(ptr3 != NULL, "should be able to allocate lots more memory within the zone.");
    require(ptr4 != NULL, "should be able to allocate lots more memory within the zone.");

    for(int i = 0; i < 20000; i++)
    {
        ptr1[i] = 'a';
        ptr2[i] = 'b';
    }
    for(int i = 0; i < 10000; i++)
    {
        ptr3[i] = 'c';
    }
    for(int i = 0; i < 14000; i++)
    {
        ptr4[i] = 'd';
    }
    
    require(zfree(z, ptr2), "should be able to free a large memory allocation.");
    void *new_pointer = zalloc(z, 2000);
    require(new_pointer != NULL, "should be able to allocate after freeing large amount of memory.");
    require(zfree(z, ptr1), "should be able to free a large memory allocation.");
    require(zfree(z, ptr4), "should be able to free a large memory allocation.");
    require(zfree(z, ptr3), "should be able to free a large memory allocation.");
    require(zfree(z, new_pointer), "should be able to free a large memory allocation.");

    unsigned char *nums = zalloc(z, 64000);
    require(nums != NULL, "should be able to allocate after freeing entire large zone of memory.");
    for(int i = 0; i < 63999; i++)
    {
        nums[i] = 21;
    }
    nums[63999] = '\0';

    destroy_zone(z);
}

int main(void)
{
    test_zone_creation();
    test_zone_allocation();
    test_zone_free();
    test_first_fit();
    test_block_size();
    test_zone_size();
    test_large();

    printf("\nEnd of processing.\n"
           "Total tests: %d\n"
           "Passed tests: %d\n"
           "Failed tests: %d\n", tests_total, tests_passed, tests_total - tests_passed);

    return EXIT_SUCCESS;
}

