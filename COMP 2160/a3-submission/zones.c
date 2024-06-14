#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "zones.h"

// The nodes will for a singly linked list, each pointing to a block, with a size.
typedef struct NODE node;
struct NODE
{
    z_size_t size;
    node *link;
    unsigned char *block;
};

// A zone has space, free space, an amount of blocks, a linked list of those blocks,
// and the actual data to hold memory on the heap.
struct ZONE
{
    z_size_t zone_size;
    z_size_t free_space;
    z_size_t num_blocks;
    node *head;
    unsigned char *data;
};

// Invariant to ensure that the linked list of nodes is valid. Takes a node as input.
static void check_blocks(node *n)
{
#ifndef NDEBUG
    node *curr = n;
    node *prev = NULL;
    
    // Each node's size must be > 0 and must point to an existing block.
    // Further, no node may point to any previous node.
    while(curr != NULL)
    {
        assert(curr->size > 0);
        assert(curr->block != NULL);
        
        prev = n;

        while(prev != curr)
        {
            assert(curr->link != prev);
            prev = prev->link;
        }

        curr = curr->link;
    }
#endif
}

// Invariant to ensure a zone is valid. Takes a zone as input.
static void check_zone(const zone *z)
{
#ifndef NDEBUG
    assert(z != NULL);
    assert(z->data != NULL);
    assert(z->zone_size > 0);
    assert(z->num_blocks >= 0);

    // free space must be between 0 and zone size
    assert(z->free_space >= 0 && z->free_space <= z->zone_size);

    check_blocks(z->head);

    z_size_t space_used = 0;
    z_size_t number_of_blocks = 0;

    node *curr = z->head;

    // Calculate running totals for space used and number of blocks
    while(curr != NULL)
    {
        number_of_blocks++;
        space_used += curr->size;
        curr = curr->link;
    }

    // Ensure num_blocks is correct. And that free space is correct.
    assert(z->num_blocks == number_of_blocks);
    assert(z->free_space == z->zone_size - space_used);
#endif
}

// See zones.h for usage
zone *make_zone(z_size_t zone_size)
{
#define CHUNK_SIZE 8
    assert(zone_size > 0);
    
    zone *z = NULL;

    // Ensure that the given size is bigger than zero
    if(zone_size > 0)
    {
        z = malloc(sizeof(zone));

        assert(z != NULL);

        // Ensure that we could allocate memory for the zone
        if(z != NULL)
        {
            // Round size to allocate up to nearest multiple of a chunk size
            if(zone_size % CHUNK_SIZE != 0)
            {
                z->zone_size = (zone_size / CHUNK_SIZE + 1) * CHUNK_SIZE; 
            }
            else
            {
                z->zone_size = zone_size;
            }

            // Initialise data within the zone.
            z->head = NULL;
            z->num_blocks = 0;
            z->free_space = z->zone_size;
            z->data = malloc(z->zone_size);

            assert(z->data != NULL);

            // If we failed to allocate memory for the data, free the memory
            if(z->data == NULL)
            {
                destroy_zone(z);
            }
        }
    }
    check_zone(z);

    return z;
}

// Gives address of first available memory for given size, or NULL if not enough space
// Also updates current and previous nodes to allow for subsequent node insertion
static void *firstFit(const zone *z, const z_size_t block_size, node **curr, node **prev)
{
    assert(z != NULL);
    assert(block_size > 0);
    assert(curr != NULL && prev != NULL);
    check_zone(z);

    bool found_space = false;
    void *mem_start = NULL;
    *curr = NULL;
    *prev = NULL;

    // Ensure zone exists and that requested size can fit in the zone.
    if(z != NULL && block_size > 0 && block_size <= z->free_space)
    {
        *curr = z->head;
        mem_start = z->data;

        // Search for a space of memory between blocks
        while(*curr != NULL && !found_space)
        {
            // Check difference between the next block's start and where we want to start
            if((*curr)->block - (unsigned char *)mem_start >= block_size)
            {
                found_space = true;
            }
            else
            {
                // Set mem_start to be just after the previously checked block
                mem_start = (*curr)->block + (*curr)->size;
                *prev = *curr;
                *curr = (*curr)->link;
            }
        }
        // If no next node, then check if not enough space from where we want to start
        // and the end of the zone.
        if(!found_space && z->zone_size - ((unsigned char *)mem_start - z->data) < block_size)
        {
            // So, no space has been found.
            mem_start = NULL;
        }
    }
    check_zone(z);

    return mem_start;
}

// See zones.h for usage
void *zalloc(zone *z, z_size_t block_size)
{
    assert(z != NULL);
    assert(block_size > 0);
    check_zone(z);

#ifndef NDEBUG
    z_size_t prev_num_blocks = z->num_blocks;
    z_size_t prev_free_space = z->free_space;
#endif

    void *mem_start = NULL;
    node *prev = NULL;
    node *curr = NULL;

    // Find first available memory address to fit specified number of bytes.
    mem_start = firstFit(z, block_size, &curr, &prev);

    if(mem_start != NULL)
    {
        // Create a block/node and insert it into the correct order.
        node *new_node = malloc(sizeof(node));

        assert(new_node != NULL);

        // Ensure that we could allocate memory for the new node.
        if(new_node != NULL)
        {
            // Set the new node's information
            new_node->block = mem_start;
            new_node->size = block_size;
            new_node->link = curr;

            // Check if node to insert is the first one
            if(prev == NULL)
            {
                z->head = new_node;
                check_blocks(z->head);
            }
            else
            {
                prev->link = new_node;
                check_blocks(prev);
            }

            // Update free space and numebr of blocks
            z->num_blocks++;
            z->free_space -= block_size;

            // Zero Out allocated memory
            for(unsigned char *i = new_node->block; i < new_node->block + new_node->size; i++)
            {
                *i = 0;
            }

            // Number of blocks must increase by one, and free space must decrease by allocated size
            assert(z->num_blocks == prev_num_blocks + 1);
            assert(z->free_space == prev_free_space - block_size);
        }
    }
    check_zone(z);

    return mem_start;
}

// See zones.h for usage
z_size_t block_size(const zone *z, void *block_ptr)
{
    assert(z != NULL);
    assert(block_ptr != NULL);
    check_zone(z);

    // Ensure pointer is within the range of the zone.
    assert((unsigned char *)block_ptr >= z->data && (unsigned char *)block_ptr < z->data + z->zone_size);

    z_size_t block_size = 0;
    node *curr;

    // Ensure the zone and block exist and that the block is within the zone
    if(z != NULL && block_ptr != NULL && (unsigned char *)block_ptr >= z->data 
                        && (unsigned char *)block_ptr < z->data + z->zone_size)
    {
        curr = z->head;

        // Iterate through nodes until found block, or until not found
        while(curr != NULL && curr->block != block_ptr)
        {
            curr = curr->link;
        }

        // If found the block, then extract the block size to return
        if(curr != NULL && curr->block == block_ptr)
        {
            block_size = curr->size;
            assert(block_size > 0);
        }
    }
    check_zone(z);

    return block_size;
}

// See zones.h for usage
z_size_t zone_size(const zone *z)
{
    assert(z != NULL);
    check_zone(z);
    
    z_size_t size = 0;

    // If zone exists, set the zone size to return
    if(z != NULL)
    {
        size = z->zone_size;
        assert(size > 0);
    }
    check_zone(z);

    return size;
}

// See zones.h for usage
bool zfree(zone *z, void *block_ptr)
{
    assert(z != NULL);
    assert(block_ptr != NULL);
    check_zone(z);

    // Ensure that the pointer is within the zone's range
    assert((unsigned char *)block_ptr >= z->data && (unsigned char *)block_ptr < z->data + z->zone_size);

#ifndef NDEBUG
    z_size_t prev_num_blocks = z->num_blocks;
    z_size_t prev_free_space = z->free_space;
#endif

    bool block_freed = false;
    node *curr;
    node *prev = NULL;

    // Ensure the zone and block exist and that the block is within the zone
    if(z != NULL && block_ptr != NULL && (unsigned char *)block_ptr >= z->data 
                        && (unsigned char *)block_ptr < z->data + z->zone_size)
    {
        curr = z->head;

        // Iterate through nodes until found block, or until not found
        while(curr != NULL && curr->block != block_ptr)
        {
            prev = curr;
            curr = curr->link;
        }

        // If found, free the current node
        if(curr != NULL && curr->block == block_ptr)
        {
            // Check if we are removing the first allocation. Restructure linking.
            if(prev == NULL)
            {
                z->head = curr->link;
            }
            else
            {
                prev->link = curr->link;
            }

            // Update free space and number of blocks
            z->num_blocks--;
            z->free_space += curr->size;
            
            // Ensure that num_blocks had decreased by one, and free space has increased
            assert(z->num_blocks == prev_num_blocks - 1);
            assert(z->free_space == prev_free_space + curr->size);

            free(curr);
            block_freed = true;
        }
    }
    check_zone(z);
 
    return block_freed;
}

// See zones.h for usage
void destroy_zone(zone *z)
{
    assert(z != NULL);
    check_zone(z);

    node *curr;
    node *next = NULL;

    if(z != NULL)
    {
        curr = z->head;

        // Iterate through and free all nodes.
        while(curr != NULL)
        {
            next = curr->link;
            free(curr);
            curr = next;
        }

        // Free the zone data and zone itself
        free(z->data);
        free(z);
        z = NULL;
    }
}

// See zones.h for usage
void zdump(const zone *z)
{
    assert(z != NULL);
    check_zone(z);

    node *curr;
    z_size_t counter = 0;

    if(z != NULL)
    {
        // Preliminary Information:
        printf("Zone data starts at (%p):\n"
                "-> zone_size: %d\n"
                "-> free_bytes: %d\n"
                "-> num_blocks: %d\n", 
                z->data, z->zone_size, z->free_space, z->num_blocks);

        curr = z->head;

        // Print data of each node. Address, Size.
        while(curr != NULL)
        {
            printf("---> block %d (%p): %d bytes\n", counter, curr->block, curr->size);

            counter++;
            curr = curr->link;
        }
    }
    check_zone(z);
}
