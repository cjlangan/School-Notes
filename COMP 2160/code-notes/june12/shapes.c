#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct RECTANGLE
{
    uint8_t width;
    uint8_t height;
};

struct TRIANGLE
{
    uint8_t base;
    uint8_t height;
};

struct CIRCLE
{
    uint8_t radius;
};

union DIMENSIONS
{
    struct RECTANGLE rectangle;
    struct TRIANGLE triangle;
    struct CIRCLE circle;
};

typedef struct SHAPE
{
    union DIMENSIONS dimensions;
    // declares a varibale called print, the type is pointer to funciton that
    // takes a shape pointer and has no return type.
    void (*print)(struct SHAPE *); 
    char shape_type[10]; //dont need this anymore
}shape;

void printRectangle(shape *s)
{
    printf("Rectangle: width %d, height %d\n", 
            s->dimensions.rectangle.width, 
            s->dimensions.rectangle.height);
}

void printTriangle(shape *s)
{
    printf("Triangle: base %d, height %d\n", 
            s->dimensions.triangle.base, 
            s->dimensions.triangle.height);
}

void printCircle(shape *s)
{
    printf("Circle: radius %d\n", 
            s->dimensions.circle.radius);
}
shape makeRectangle(uint8_t width, uint8_t height)
{
    struct RECTANGLE rect = {
        .width = width,
        .height = height
    };

    shape s = {
        .dimensions.rectangle = rect,
        .print = printRectangle // don't need anymore
    };
    strcpy(s.shape_type, "rectangle"); //don't need this either.

    return s;
}

shape makeTriangle(uint8_t base, uint8_t height)
{
    struct TRIANGLE triangle = {
        .base = base,
        .height = height
    };

    shape s = {
        .dimensions.triangle = triangle,
        .print = printTriangle
    };
    strcpy(s.shape_type, "triangle");

    return s;
}

shape makeCircle(uint8_t radius)
{
    struct CIRCLE circle = {
        .radius = radius
    };

    shape s = {
        .dimensions.circle = circle,
        .print = printCircle
    };
    strcpy(s.shape_type, "circle");

    return s;
}


int main(int argc, char **argv)
{
    // shape triangle = makeTriangle(10, 50);
    // shape square = makeRectangle(10, 10);

    shape shapes[5] = {0};

    shapes[0] = makeCircle(4);
    shapes[1] = makeTriangle(5, 40);

    for(int i = 0; i < 2; i++)
    {
        shapes[i].print(&shapes[i]);
/*        
        if (strcmp(shapes[i].shape_type, "circle"))
        {
            printf("If this is a circle, dimensions are: radius %d\n",
                shapes[i].dimensions.circle.radius);

        }
        else if(strcmp(shapes[i].shape_type, "rectangle"))
        {
            printf("If this is a rectangle, dimensions are: width %d, height %d\n",
                shapes[i].dimensions.rectangle.width, shapes[i].dimensions.rectangle.height);
        }
        else
        {
            printf("If this is a triangle, dimensions are: base %d, height %d\n",
                shapes[i].dimensions.triangle.base, shapes[i].dimensions.triangle.height);
*/
        
    }

    return EXIT_SUCCESS;
}
