/**
 * Main program for C programming tasks
 * This program includes three tasks:
 * 1. Character counting in text
 * 2. Student group management
 * 3. Human records management
 */

#include <stdio.h>
#include <stdlib.h>

// Function declarations from other files
void runTask1();
void runTask2();
void runTask3();

/**
 * Display the main menu and get user choice
 */
int showMenu() {
    int choice;
    printf("\n===== C Programming Tasks =====\n");
    printf("1. Character Counting\n");
    printf("2. Student Group Management\n");
    printf("3. Human Records Management\n");
    printf("0. Exit\n");
    printf("Enter your choice (0-3): ");
    
    if (scanf("%d", &choice) != 1) {
        // Clear input buffer
        while (getchar() != '\n');
        return -1;
    }
    
    // Clear input buffer
    while (getchar() != '\n');
    
    return choice;
}

int main() {
    int choice;
    
    do {
        choice = showMenu();
        
        switch (choice) {
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            case 1:
                runTask1();
                break;
            case 2:
                runTask2();
                break;
            case 3:
                runTask3();
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 3.\n");
        }
    } while (choice != 0);
    
    return 0;
}
