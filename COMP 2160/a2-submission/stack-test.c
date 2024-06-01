/*-----------------------------------------
 * NAME: Connor Langan
 * STUDENT NUMBER: 7993941
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Franklin Bristow
 * ASSIGNMENT: 2, QUESTION: 2
 *
 * REMARKS: Test suite for implementations of the stack.h interface. Finds
 *          successes and failures while printing useful info to the terminal.
 *          Note that best programming practices do NOT apply to this code.
 *-----------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stack.h"

int total_tests = 0;
int success_tests = 0;

void test_create_stack(void)
{
    stack *s;

    s = create_stack();

    if(s != NULL)
    {
        printf("PASS: Able to make a stack.\n");
        success_tests++;
    }
    else
    {
        printf("FAIL: Not able to make a stack.\n");
    }
    total_tests++;
    destroy_stack(s);
}

void test_push_general(void)
{
    // ======================= Test pushing values ============================
    stack *s = create_stack();

    if(push(s, 5))
    {
        success_tests++;
        printf("PASS: Able to push a single value.\n");

        if(push(s, 6))
        {
            success_tests++;
            printf("PASS: Able to push multiple values.\n");
        }
        else
        {
            printf("FAIL: Unble to push multiple values.\n");
        }
    }
    else
    {
        printf("FAIL: Unable to push a single value.\n");
    }
    total_tests += 2;
    destroy_stack(s);
    // ========================================================================

    // ===================== Test pushing after popping =======================
    s = create_stack();
    int value;

    push(s, 30);
    push(s, 40);
    pop(s, &value);
    value = 0;

    if(push(s, 50))
    {
        success_tests++;
        printf("PASS: Able to push after popping.\n");

    }
    else
    {
        printf("FAIL: Did not push after popping.\n");
    }
    total_tests++;
    destroy_stack(s);
    // =======================================================================
}

void test_peek_general(void)
{
    // =============== Test if Pushed values match Peeked values =============
    stack *s = create_stack();
    int peeked;
    
    for(int i = 0; i < 10; i++)
    {
        push(s, i);
        
        if(peek(s, &peeked))
        {
            success_tests++;

            if(peeked == i)
            {
                success_tests++;
            }
            else
            {
                printf("FAIL: pushed value %d, but peeked value %d.\n", i, peeked);
            }
        }
        else
        {
            printf("FAIL: unable to peek a stack with %d elements.\n", i);
        }
    }
    total_tests += 20;
    destroy_stack(s);
    // ========================================================================

    // ======== Test that peeking a value doesn't modify the top value ========
    s = create_stack();
    int second_peek;

    push(s, 5);

    peek(s, &peeked);
    peek(s, &second_peek);

    if(peeked == second_peek)
    {
        success_tests++;
        printf("PASS: Peeking value doesn't modify top value.\n");
    }
    else
    {
        printf("FAIL: Peeking value modifies top value.\n");
    }
    total_tests++;
    destroy_stack(s);
    // ========================================================================
}

void test_pop_general(void)
{
    // ============ Test if popped values match order of stack ================
    stack *s = create_stack();
    int popped;
    int elements = 20;

    for(int i = 0; i < elements; i += 2)
    {
        push(s, i);
    }
    for(int i = elements - 2; i >= 0; i -= 2)
    {
        if(pop(s, &popped))
        {
            success_tests++;

            if(popped == i)
            {
                success_tests++;
            }
            else
            {
                printf("FAIL: Popped %d, expected %d.\n", popped, i);
            }
        }
        else
        {
            printf("FAIL: Unable to pop on attempt %d, attempting to pop %d.\n", elements - i - 1, i);
        }
    }
    total_tests += elements;
    destroy_stack(s);
    // ========================================================================
}

void test_size_general(void)
{
    // ====================== Test Size of populated stack ====================
    stack *s = create_stack();
    int num_nodes;

    push(s, 9);
    push(s, 31);
    push(s, 3948);
    push(s, 21);

    num_nodes = size(s);
    
    if(num_nodes == 4)
    {
        success_tests++;
        printf("PASS: Determined correct size of populated stack.\n");
    }
    else
    {
        printf("FAIL: Found incorrect size of populated stack" 
                        "(Got %d, expected 4).\n", num_nodes);
    }
    total_tests++;
    destroy_stack(s);

    // ========================================================================

    // =============== Test size of stack after popping values ================
    s = create_stack();
    int value;

    push(s, 43);
    push(s, 4444);
    push(s, 999);
    push(s, 2); 
    pop(s, &value);

    num_nodes = size(s);
    
    if(num_nodes == 3 && value == 2)
    {
        success_tests++;
        printf("PASS: Determined correct size of stack after popping.\n");
    }
    else
    {
        printf("FAIL: Found incorrect size of stack after popping" 
                        "(Got %d, expected 4).\n", num_nodes);
    }
    total_tests++;
    destroy_stack(s);
    // =======================================================================

    // ============= Test that size does not modify values ===================
    s = create_stack();
    int popped;

    push(s, 3);
    num_nodes = size(s);

    if(pop(s, &popped) && popped == 3)
    {
        success_tests++;
        printf("PASS: Checking size doesn't modify values.\n");
    }
    else
    {
        printf("FAIL: Checking size modifies values.\n");
    }
    total_tests++;
    destroy_stack(s);
    // ========================================================================

}

void test_empty_general(void)
{
    // ================= Test if populated stack is not empty =================
    stack *s = create_stack();

    push(s, 88);

    if(!empty(s))
    {
        success_tests++;
        printf("PASS: correctly determined a populated stack is not empty.\n");
    }
    else
    {
        printf("FAIL: determined a populated stack is empty.\n");
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================

    // ============== Test if an emptied stack is empty =====================
    s = create_stack();
    int value;

    push(s, 19);
    pop(s, &value);

    if(empty(s) && value == 19)
    {
        success_tests++;
        printf("PASS: correctly determined an emptied stack is empty.\n");
    }
    else
    {
        printf("FAIL: determined an emptied stack is not empty.\n");
    }
    total_tests++;
    destroy_stack(s);\
    // ======================================================================
}

void test_push_edge(void)
{
    // ============= Test pushing a value onto an emptied stack =============
    stack *s = create_stack();
    int value;

    push(s, 22);
    pop(s, &value);

    if(push(s, 83) && value == 22)
    {
        success_tests++;
        printf("PASS: Able to push a value onto an emptied stack.\n");
    }
    else
    {
        printf("FAIL: Unable to push a value onto an emptied stack.\n");
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================
}

void test_peek_edge(void)
{
    // ===================== Test peeking an empty stack ====================
    stack *s = create_stack();
    int value;

    if(!(peek(s, &value)))
    {
        success_tests++;
        printf("PASS: Peeking an empty stack returns false.\n");
    }
    else
    {
        printf("FAIL: Peeking an empty stack returned true (reutrned value %d).\n", value);
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================
}

void test_pop_edge(void)
{
    // ====================== Test popping an empty stack ===================
    stack *s = create_stack();
    int value;

    if(!(pop(s, &value)))
    {
        success_tests++;
        printf("PASS: Popping an empty stack returns false.\n");
    }
    else
    {
        printf("FAIL: Popping an empty stack returned true (reutrned value %d).\n", value);
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================
}

void test_size_edge(void)
{
    // ===================== Test size of an empty stack ====================
    stack *s = create_stack();
    int returned_size = size(s);

    if(returned_size == 0)
    {
        success_tests++;
        printf("PASS: Correctly determined size of an empty stack to be 0.\n");
    }
    else
    {
        printf("FAIL: Correctly determined size of an empty stack to be %d,"
                                    "expected 0.\n", returned_size);
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================
}

void test_empty_edge()
{
    // ==================== Test if new stack is empty ======================
    stack *s = create_stack();

    if(empty(s))
    {
        success_tests++;
        printf("PASS: correctly determined an new stack is empty.\n");
    }
    else
    {
        printf("FAIL: determined a new stack is not empty.\n");
    }
    total_tests++;
    destroy_stack(s);
    // ======================================================================
}

int main(int argc, char **argv)
{
    test_create_stack();
    test_push_general();
    test_peek_general();
    test_pop_general();
    test_size_general();
    test_empty_general();

    test_push_edge();
    test_peek_edge();
    test_pop_edge();
    test_size_edge();
    test_empty_edge();
    
    printf("Total tests ran: %d\n"
            "Successful tests: %d\n"
            "Failed tests: %d\n", total_tests, success_tests,
                                total_tests - success_tests);
    return EXIT_SUCCESS;
}
