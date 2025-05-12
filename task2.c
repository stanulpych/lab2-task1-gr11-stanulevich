/**
 * Task 2: Student Group Management
 * Program to manage student records with name, birth date, and grades.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50
#define NUM_GRADES 3
#define GROUP_SIZE 10

// Structure for date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// Structure for student group
typedef struct {
    char name[MAX_NAME_LEN];  // Surname and initials
    Date dob;                // Date of birth
    int ses[NUM_GRADES];     // Grades (success)
} GROUP;

/**
 * Calculates the average grade of a student
 */
float calculateAverage(const int grades[NUM_GRADES]) {
    float sum = 0;
    for (int i = 0; i < NUM_GRADES; i++) {
        sum += grades[i];
    }
    return sum / NUM_GRADES;
}

/**
 * Calculates age on a specific date
 */
int calculateAge(Date dob, Date reference) {
    int age = reference.year - dob.year;
    
    // Check if birthday has occurred this year
    if (reference.month < dob.month || 
        (reference.month == dob.month && reference.day < dob.day)) {
        age--;
    }
    
    return age;
}

/**
 * Compares two students by their average grade
 * Returns negative if s1 < s2, positive if s1 > s2, 0 if equal
 */
int compareByGrades(const GROUP *s1, const GROUP *s2) {
    float avg1 = calculateAverage(s1->ses);
    float avg2 = calculateAverage(s2->ses);
    
    if (avg1 < avg2) return -1;
    if (avg1 > avg2) return 1;
    return 0;
}

/**
 * Sort students by grades (using bubble sort)
 */
void sortStudentsByGrades(GROUP students[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareByGrades(&students[j], &students[j + 1]) > 0) {
                // Swap students
                GROUP temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/**
 * Validate a date
 * Returns true if valid, false otherwise
 */
bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    
    // Days in each month (not considering leap years for simplicity)
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Adjust February for leap years
    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        daysInMonth[2] = 29;
    }
    
    return day <= daysInMonth[month];
}

/**
 * Checks if a grade is valid (between 0 and 100)
 */
bool isValidGrade(int grade) {
    return grade >= 0 && grade <= 100;
}

void runTask2() {
    printf("\n=== Task 2: Student Group Management ===\n");
    
    GROUP gr5[GROUP_SIZE];
    int actualSize = 0;
    
    printf("Enter data for up to %d students (enter empty name to finish):\n", GROUP_SIZE);
    
    for (int i = 0; i < GROUP_SIZE; i++) {
        printf("\nStudent %d:\n", i + 1);
        
        printf("Name (surname and initials): ");
        if (scanf("%49s", gr5[i].name) != 1 || gr5[i].name[0] == '\0') {
            if (i == 0) {
                printf("At least one student must be entered. Using 'Default Student'.\n");
                strcpy(gr5[i].name, "Default Student");
            } else {
                break;
            }
        }
        
        // Read date of birth
        do {
            printf("Date of birth (YYYY MM DD): ");
            if (scanf("%d %d %d", &gr5[i].dob.year, &gr5[i].dob.month, &gr5[i].dob.day) != 3) {
                printf("Invalid input. Please try again.\n");
                // Clear input buffer
                while (getchar() != '\n');
                continue;
            }
            
            if (!isValidDate(gr5[i].dob.year, gr5[i].dob.month, gr5[i].dob.day)) {
                printf("Invalid date. Please try again.\n");
                continue;
            }
            
            break;
        } while (1);
        
        // Read grades
        printf("Enter %d grades:\n", NUM_GRADES);
        for (int j = 0; j < NUM_GRADES; j++) {
            do {
                printf("Grade %d: ", j + 1);
                if (scanf("%d", &gr5[i].ses[j]) != 1 || !isValidGrade(gr5[i].ses[j])) {
                    printf("Invalid grade. Please enter a value between 0 and 100.\n");
                    // Clear input buffer
                    while (getchar() != '\n');
                    continue;
                }
                break;
            } while (1);
        }
        
        actualSize++;
    }
    
    if (actualSize == 0) {
        printf("No students entered. Exiting task.\n");
        return;
    }
    
    // Sort students by grades
    sortStudentsByGrades(gr5, actualSize);
    
    // Display sorted list
    printf("\nStudents sorted by grades (ascending):\n");
    printf("%-30s %-15s %-15s\n", "Name", "Date of Birth", "Average Grade");
    printf("------------------------------------------------------------------\n");
    
    for (int i = 0; i < actualSize; i++) {
        float avg = calculateAverage(gr5[i].ses);
        printf("%-30s %04d-%02d-%02d     %.2f\n", 
               gr5[i].name, 
               gr5[i].dob.year, gr5[i].dob.month, gr5[i].dob.day,
               avg);
    }
    
    // Define reference date: December 1, 2010
    Date reference = {2010, 12, 1};
    
    // Find students under 20 years old
    printf("\nStudents under 20 years old on December 1, 2010:\n");
    bool foundYoung = false;
    
    for (int i = 0; i < actualSize; i++) {
        int age = calculateAge(gr5[i].dob, reference);
        
        if (age < 20) {
            if (!foundYoung) {
                printf("%-30s %-15s %-10s\n", "Name", "Date of Birth", "Age");
                printf("------------------------------------------------------------------\n");
                foundYoung = true;
            }
            
            printf("%-30s %04d-%02d-%02d     %d\n", 
                   gr5[i].name, 
                   gr5[i].dob.year, gr5[i].dob.month, gr5[i].dob.day,
                   age);
        }
    }
    
    if (!foundYoung) {
        printf("No students under 20 years old found.\n");
    }
}
