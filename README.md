# C Programming Tasks

This repository contains implementations of several C programming tasks focusing on:

1. **Character Counting**: Count occurrences of a specific letter in multiple sentences
2. **Student Group Management**: Manage student records with sorting and filtering capabilities
3. **Human Records Management**: Personal record management with detailed information

## Task Descriptions

### Task 1: Character Counting
A program to find the total number of occurrences of a specific letter (input from keyboard) in multiple sentences. The function counts occurrences of the specified letter in a string.

### Task 2: Student Group Management
Implements a GROUP structure containing:
- Name (surname and initials)
- Date of birth (year, month, day)
- Academic performance (array of three elements)

The program:
- Takes input for up to 10 students
- Displays records sorted by academic performance
- Lists students under 20 years old as of December 1, 2010
- Shows a message if no such students exist

### Task 3: Human Records Management
Implements a structure for "Person" with comprehensive personal details:
- Full name (surname, first name, patronymic)
- Gender
- Nationality
- Height, weight
- Date of birth
- Phone number
- Home address (with detailed breakdown)

The program displays information about the youngest person in the records.

## Compilation and Running

To compile and run the program:

```bash
gcc -o program main.c task1.c task2.c task3.c
./program
```

## Menu Options

The program provides an interactive menu with the following options:
1. Character Counting
2. Student Group Management
3. Human Records Management
0. Exit

Select the desired option by entering the corresponding number.