#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "zones.h"

typedef struct PLAYER
{
    unsigned short x;    // the player's x position, where 0 is the left side of
                         // the terminal. Must not be greater than the player's
                         // room's width.

    unsigned short y;    // the player's y position, where 0 is the top of the 
                         // terminal. Must not be greater than the player's
                         // room's height.

    char name[10];       // the name of the player. Must not be NULL. Must be
                         // less than 10 characters.

    struct ROOM *room;   // the room the player is in. Must not be NULL.
    
    unsigned long score; // the player's current score.
} player;

typedef struct ITEM
{
    unsigned short x;     // The item's x position, where 0 is the left side of 
                          // the terminal. Must not be greater than the item's
                          // room's width.

    unsigned short y;     // the item's y position, where 0 is the top of the 
                          // terminal. Must not be greater than the item's room's
                          // height.

    unsigned short value; // the value of the item.

    struct ITEM *next;    // the next item in the list.

    struct ROOM *room;    // the room the item is in. Must not be NULL.
} item;

typedef struct ROOM
{
    unsigned short height; // the height of the room the player is in.

    unsigned short width;  // the width of the room the player is in.

    player *player;        // the player in the room. Must not be NULL.

    item *items;           // the items in the room. Must not be NULL if
                           // num_items is greater than zero, otherwise must be
                           // NULL.

    int num_items;         // the number of items in the room. Must be zero if
                           // items is NULL, otherwise must be greater than
                           // zero.

#define NUM_DOORS  4
#define NORTH_DOOR 0
#define EAST_DOOR  1
#define SOUTH_DOOR 2
#define WEST_DOOR  3

    unsigned short doors[NUM_DOORS];  // contains the location of doors in the 
                                      // room. north and south doors are less
                                      // than the room's width. east and west
                                      // doors are less than the room's height.
} room;

zone *z;
room *r;
player *p;
WINDOW *w;

bool running = true;
bool debug = false; // print extra debugging information

/**
 * Handle keyboard input. This function checks to see if any of the arrow keys
 * have been pressed. If any arrow keys have been pressed, we will begin to
 * change the state of the player by adjusting the player's position. This
 * function will always leave the player in a valid state. This function may
 * cause the room to be destroyed and recreated if the player moves to a
 * doorway.
 */
void handle_input(void);

/**
 * Display the room. This function expects that the player and room are both
 * valid. This function does not change the player and room, and will always
 * leave the player and room in a valid state.
 */
void display_room(void);

/**
 * Inspect the player's current state and decide if the player has picked up an
 * item. If the player has picked up an items, remove the item from the room 
 * and change the player's score. Both the room and player should be valid on
 * entering this function, and both the player and room will be valid on
 * leaving this function.
 */
void pickup_items(void);

/**
 * Apply an invariant to the player object.
 *
 * Args:
 *  p: the player to validate.
 * Returns: none, will fail on assert.
 */
static void validate_player(const player *p);

/**
 * Apply an invariant to the room object.
 *
 * Args:
 *  r: the room to validate.
 * Returns: none, will fail on assert.
 */
static void validate_room(const room *r);

/**
 * Initialize the state of the game. Will prompt for input for the player's
 * name. Allocates space for both the room and the player. This function will
 * end with both the player and room being valid.
 */
void initialize_game(void);

/**
 * Initialize a new room. This function will end with the room being a valid
 * room.
 */
static void initialize_room(void);

/**
 * Destroy the current room. The room to destroy must be valid, but it will be
 * invalid after being destroyed. 
 */
static void destroy_room(void);

/**
 * Get the item from the room at the current position. The room must be valid
 * on entering this function. This function will end with both the room being
 * valid.
 *
 * Args:
 *  x: the x coordinate to search. Must be less than the room's width.
 *  y: the y coordinate to search. Must be less than the room's height.
 * Returns: the item at the coordinate, or NULL if there is no item.
 */
item *item_at(unsigned short x, unsigned short y);

int main(void)
{
    initialize_game();

    initscr();              // initialize a curses screen
    cbreak();               // disable line buffering
    keypad(stdscr, TRUE);   // enable arrows
    noecho();               // don't reprint arrow key escape codes.
    
    if ( !has_colors() )
    {
        printf("Sorry, this is only going to work with terminals supporting "
               "coloured outputs.\n");
        running = false;
    }
    else
    {
#define DONT_CHANGE_COLOUR getbkgd(stdscr)
//        start_color();
//        init_pair( 1, COLOR_BLUE, DONT_CHANGE_COLOUR );
//        init_pair( 2, COLOR_WHITE, DONT_CHANGE_COLOUR );
    }

    while ( running )
    {
        display_room();
        handle_input();
        pickup_items();
    }

    destroy_zone( z );
    free( p );
    endwin();

    return EXIT_SUCCESS;
}

static void validate_player(const player *p)
{
    assert( p != NULL );
    assert( p->room != NULL );
    assert( p->x < p->room->width );
    assert( p->y < p->room->height );
    assert( p->name != NULL );
}

static void validate_room(const room *r)
{
    assert( r != NULL );
    assert( r->player != NULL );

    assert( (r->num_items == 0 && r->items == NULL) ||
            (r->num_items > 0 && r->items != NULL) );

    assert( r->doors[NORTH_DOOR] < r->width );
    assert( r->doors[EAST_DOOR]  < r->height );
    assert( r->doors[SOUTH_DOOR] < r->width );
    assert( r->doors[WEST_DOOR]  < r->height );

#ifndef NDEBUG
    int count = 0;
    item *curr = r->items;

    while (curr != NULL)
    {
        count++;
        assert( curr->x < r->width );
        assert( curr->y < r->height );
        curr = curr->next;
    }
    assert( count == r->num_items );
#endif
}

void handle_input(void)
{
    int c;

    validate_player( p );
    validate_room( r );

    c = getch();

    switch( c )
    {
        case KEY_UP:
            if ( p->y > 0 )
            {
                p->y -= 1;
            }
            else if ( p->x == r->doors[NORTH_DOOR] )
            {
                destroy_room();
                initialize_room();
            }
            break;
        case KEY_DOWN:
            if ( p->y < r->height - 1 )
            {
                p->y += 1;
            }
            else if ( p->x == r->doors[SOUTH_DOOR] )
            {
                destroy_room();
                initialize_room();
            }
            break;
        case KEY_LEFT:
            if ( p->x > 0 )
            {
                p->x -= 1;
            }
            else if ( p->y == r->doors[WEST_DOOR] )
            {
                destroy_room();
                initialize_room();
            }
            break;
        case KEY_RIGHT:
            if ( p->x < r->width - 1 )
            {
                p->x += 1;
            }
            else if ( p->y == r->doors[EAST_DOOR] )
            {
                destroy_room();
                initialize_room();
            }
            break;
        case KEY_EXIT:
        case 'x':
            running = false;
            break;
        case 'd':
            debug = !debug;
            break;
    }

    validate_player( p );
    validate_room( r );
}

void initialize_game(void)
{
#define MAX_NAME_LENGTH 10
    char name_buffer[MAX_NAME_LENGTH] = {0};

    printf("Welcome to the game. What's your name? ");
    do
    {
        fgets( name_buffer, MAX_NAME_LENGTH, stdin );
    } while ( strlen(name_buffer) > MAX_NAME_LENGTH );

    // cut the newline
    name_buffer[strlen(name_buffer) - 1] = '\0';

    // initialize the player object
    p = malloc(sizeof(player));
    
    if ( p != NULL )
    {
        strncpy( p->name, name_buffer, strlen( name_buffer ) );
        p->x = 0;
        p->y = 0;
    }

    initialize_room();

    validate_player( p );
    validate_room( r );
}

static void destroy_room(void)
{
    destroy_zone( z );
}

static void initialize_room(void)
{
    item *rand_item = NULL;
    // initialize the room object.
    // the zone is initialized to the largest possible size of room.
    z = make_zone(sizeof(room) + sizeof(item) * 20 * 20);
    r = zalloc(z, sizeof(room));

    if ( r != NULL )
    {
        r->height = 20;
        r->width = 20;
        r->items = NULL;

        // establish the cirular dependency.
        if ( p != NULL )
        {
            p->room = r;
            r->player = p;
        }

        // figure out how many items to generate for the room:
        // the maximum number of items is pretty much the dimensions of the
        // room less 1 for the player. You're pretty lucky if you enter a 
        // room that's full of loot.
        r->num_items = rand() % r->height * r->width;

        for (int i = 0; i < r->num_items; i++)
        {
            // generate items!
            rand_item = zalloc(z, sizeof(item));

            if ( rand_item != NULL )
            {
                rand_item->x = rand() % r->width;
                rand_item->y = rand() % r->height;
                rand_item->value = rand();

                rand_item->room = r;
                rand_item->next = r->items;

                r->items = rand_item;
            }
        }

        // now add the doors:
        r->doors[NORTH_DOOR] = rand() % r->width;
        r->doors[EAST_DOOR]  = rand() % r->height;
        r->doors[SOUTH_DOOR] = rand() % r->width;
        r->doors[WEST_DOOR]  = rand() % r->height;
    }
}

void display_room(void)
{
    validate_player( p );
    validate_room( r );

    refresh();

    // display the borders of the room first:
    move(0, 0);
    addch('+');
    for (int i = 0; i < r->width; i++)
    {
        if ( i == r->doors[NORTH_DOOR] )
        {
            addch('#');
        }
        else
        {
            addch('-');
        }
    }
    addch('+');
    for (int i = 0; i < r->height; i++)
    {
        move(i + 1, 0); // we need to skip the line we just drew.
        if (i == r->doors[WEST_DOOR])
        {
            addch('#');
        }
        else
        {
            addch('|');
        }
        for (int j = 0; j < r->width; j++)
        {
            // the order makes sure that the '@' player is displayed on top of
            // any items that are in this position.
            if (p->x == j && p->y == i )
            {
                addch('@');
            }
            else if (item_at(j, i))
            {
                addch('$');
            }
            else
            {
                addch(' ');
            }
        }
        if (i == r->doors[EAST_DOOR])
        {
            addch('#');
        } 
        else
        {
            addch('|');
        }
    }
    move(r->height + 1, 0);
    addch('+');
    for (int i = 0; i < r->width; i++)
    {
        if ( i == r->doors[SOUTH_DOOR])
        {
            addch('#');
        }
        else
        {
            addch('-');
        }
    }
    addch('+');

    // now display the player's stats:
    move(r->height + 2, 0);
    printw("%s: %lu (press x to exit, d for debug)\n", p->name, p->score);
    if ( debug )
    {
        printw("position: %u, %u; room dimensions: %u, %u\n", p->x, p->y, r->width, r->height);
        printw("doors (N E S W): %u %u %u %u\n", r->doors[NORTH_DOOR], r->doors[EAST_DOOR], r->doors[SOUTH_DOOR], r->doors[WEST_DOOR]);
    }

    validate_player( p );
    validate_room( r );
}

item *item_at(unsigned short x, unsigned short y)
{
    validate_room( r );
    assert( x < r->width );
    assert( y < r->height );

    item *found = NULL;
    item *curr = r->items;

    while (curr != NULL && found == NULL)
    {
        if (curr->x == x && curr->y == y)
        {
            found = curr;
        }
        curr = curr->next;
    }

    validate_room( r );
    return found;
}

void pickup_items(void)
{
    validate_player( p );
    validate_room( r );

    item *found = NULL;
    item *curr = r->items;
    item *prev = NULL;

    found = item_at( p->x, p->y );
    if ( found )
    {
        p->score += found->value;
        // remove item from the room:
        while (curr != NULL && curr != found)
        {
            prev = curr;
            curr = curr->next;
        }
        // we found an item, so there's no reason why
        // both would be NULL unless we're at the head of the list.
        assert( ( curr != NULL && prev != NULL ) ||
                ( curr != NULL && prev == NULL && curr == r->items ) );

        // remove the item. We're not bothering to free.
        if ( curr != NULL && prev == NULL && curr == r->items )
        {
            r->items = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        r->num_items--;
    }

    validate_player( p );
    validate_room( r );
}
