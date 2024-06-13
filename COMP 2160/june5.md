## Modular Design
- Separate code into resusable objects.
- logical subsets
- abstract data types and data structures

### How to Separate Code?
- How many lines of code in a function?  NO.
- Lines of code in a file?  NO.
- Single responsibility Principle?  YES.
    - Do one thing, and *do it well*.

### Two Main Targets
1. Reusable abstract data types, data structures.
2. Subsystems (look for Design Patterns). 
    - common solution for problems.

## Abstract Data Types and Structures
- Lists, Sets, Trees
- Each get a .c and .h file.

## Subsystems
- A collection of related functionality
    - In C: stdio.h library, allrelated to input and output.
- Grouped together as a moduel (A class or package in Java)
- May use other ADT's
- Each gets a .c and .h file.

### Defining Subsystems

#### Measuring subsystems
1. Cohesion
    - measure of how well pieces of code and concepts beling together
        - Single Responsibility Principle, do one thing well.
    - Classes/modules implemetns one concept (one ADT, or action)
    - Cohesion is measured as *high* or *low*
2. Coupling
    - Measure of how much a class/module/funciton/cncept depends on other classes/modules/function ...
    - High coupling makes codes hard to change
        - Changes to one thing are affecting others
    - Coupling is unavoidable.
        - Modular design can reduce it
    - Measured as high/tight or low/loose

### Menti
Lego - High cohesion, loosely coupled 
Lego, stranger pieces - Mid cohesion, loosely coupled
Web Cam - High cohesion, loose coupling
Train and Tracks - High cohesion, High coupling in general.  - He says low coupling
Key and Lock - High cohesion, High couling.

## Assignemnt 2 smaple solution
- went over stuff.

## Notes:
- use coupling and cohesion to describe some abstract concept, like a picture.

