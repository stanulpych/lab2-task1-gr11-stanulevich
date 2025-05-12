/**
 * Task 3: Human Records Management
 * Program to manage personal records and find the youngest person.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STR_LEN 100
#define MAX_RECORDS 50

// Structure for date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// Structure for address
typedef struct {
    char postalCode[MAX_STR_LEN];
    char country[MAX_STR_LEN];
    char region[MAX_STR_LEN];
    char district[MAX_STR_LEN];
    char city[MAX_STR_LEN];
    char street[MAX_STR_LEN];
    char house[MAX_STR_LEN];
    char apartment[MAX_STR_LEN];
} Address;

// Structure for human
typedef struct {
    char lastName[MAX_STR_LEN];
    char firstName[MAX_STR_LEN];
    char middleName[MAX_STR_LEN];
    char gender[MAX_STR_LEN];
    char nationality[MAX_STR_LEN];
    float height;
    float weight;
    Date birthDate;
    char phoneNumber[MAX_STR_LEN];
    Address address;
} Human;

/**
 * Validate a date
 * Returns true if valid, false otherwise
 */
bool isValidDateHuman(int year, int month, int day) {
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
 * Compare two dates
 * Returns: 
 *   -1 if date1 is earlier than date2
 *    0 if dates are equal
 *    1 if date1 is later than date2
 */
int compareDates(Date date1, Date date2) {
    if (date1.year < date2.year) return -1;
    if (date1.year > date2.year) return 1;
    
    if (date1.month < date2.month) return -1;
    if (date1.month > date2.month) return 1;
    
    if (date1.day < date2.day) return -1;
    if (date1.day > date2.day) return 1;
    
    return 0;
}

/**
 * Calculate age based on current date
 */
int calculateAgeHuman(Date birthDate) {
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    
    Date today = {
        .year = current->tm_year + 1900,
        .month = current->tm_mon + 1,
        .day = current->tm_mday
    };
    
    int age = today.year - birthDate.year;
    
    // Check if birthday has occurred this year
    if (today.month < birthDate.month || 
        (today.month == birthDate.month && today.day < birthDate.day)) {
        age--;
    }
    
    return age;
}

/**
 * Find the index of the youngest person in the array
 * Returns -1 if the array is empty
 */
int findYoungestPerson(Human people[], int count) {
    if (count <= 0) return -1;
    
    int youngestIdx = 0;
    Date youngestDate = people[0].birthDate;
    
    for (int i = 1; i < count; i++) {
        // If current person's birth date is later (newer) than youngest so far
        if (compareDates(youngestDate, people[i].birthDate) < 0) {
            youngestIdx = i;
            youngestDate = people[i].birthDate;
        }
    }
    
    return youngestIdx;
}

/**
 * Display detailed information about a person
 */
void displayPerson(const Human *person) {
    printf("========== Personal Information ==========\n");
    printf("Name: %s %s %s\n", person->lastName, person->firstName, person->middleName);
    printf("Gender: %s\n", person->gender);
    printf("Nationality: %s\n", person->nationality);
    printf("Height: %.2f cm\n", person->height);
    printf("Weight: %.2f kg\n", person->weight);
    printf("Date of Birth: %04d-%02d-%02d (Age: %d)\n", 
           person->birthDate.year, person->birthDate.month, person->birthDate.day,
           calculateAgeHuman(person->birthDate));
    printf("Phone: %s\n", person->phoneNumber);
    
    printf("\n----------- Address Information -----------\n");
    printf("Postal Code: %s\n", person->address.postalCode);
    printf("Country: %s\n", person->address.country);
    printf("Region: %s\n", person->address.region);
    printf("District: %s\n", person->address.district);
    printf("City: %s\n", person->address.city);
    printf("Street: %s\n", person->address.street);
    printf("House: %s\n", person->address.house);
    printf("Apartment: %s\n", person->address.apartment);
    printf("===========================================\n");
}

/**
 * Get a valid input for height or weight
 */
float getValidFloat(const char *prompt, float minValue, float maxValue) {
    float value;
    char buffer[MAX_STR_LEN];
    
    do {
        printf("%s", prompt);
        
        if (fgets(buffer, MAX_STR_LEN, stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        if (sscanf(buffer, "%f", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (value < minValue || value > maxValue) {
            printf("Value must be between %.2f and %.2f. Please try again.\n", minValue, maxValue);
            continue;
        }
        
        break;
    } while (1);
    
    return value;
}

/**
 * Get a string input with validation
 */
void getStringInput(const char *prompt, char *target, int maxLen) {
    printf("%s", prompt);
    
    if (fgets(target, maxLen, stdin) == NULL) {
        printf("Error reading input. Using default value.\n");
        strcpy(target, "Default");
        return;
    }
    
    // Remove trailing newline
    size_t len = strlen(target);
    if (len > 0 && target[len - 1] == '\n') {
        target[len - 1] = '\0';
    }
    
    // If empty, use default
    if (target[0] == '\0') {
        strcpy(target, "Default");
    }
}

/**
 * Get a valid date input
 */
Date getValidDateInput(const char *prompt) {
    Date date;
    char buffer[MAX_STR_LEN];
    
    do {
        printf("%s", prompt);
        
        if (fgets(buffer, MAX_STR_LEN, stdin) == NULL) {
            printf("Error reading input. Using default date.\n");
            date.year = 2000;
            date.month = 1;
            date.day = 1;
            return date;
        }
        
        if (sscanf(buffer, "%d %d %d", &date.year, &date.month, &date.day) != 3) {
            printf("Invalid input. Please enter year, month, and day separated by space.\n");
            continue;
        }
        
        if (!isValidDateHuman(date.year, date.month, date.day)) {
            printf("Invalid date. Please try again.\n");
            continue;
        }
        
        break;
    } while (1);
    
    return date;
}

void runTask3() {
    printf("\n=== Task 3: Human Records Management ===\n");
    
    Human people[MAX_RECORDS];
    int count = 0;
    char buffer[MAX_STR_LEN];
    
    printf("Enter data for people records (enter empty last name to finish):\n");
    
    while (count < MAX_RECORDS) {
        printf("\nPerson %d:\n", count + 1);
        
        // Get last name
        getStringInput("Last Name: ", people[count].lastName, MAX_STR_LEN);
        if (strcmp(people[count].lastName, "Default") == 0 && count > 0) {
            break;
        }
        
        // Get other personal information
        getStringInput("First Name: ", people[count].firstName, MAX_STR_LEN);
        getStringInput("Middle Name: ", people[count].middleName, MAX_STR_LEN);
        getStringInput("Gender (Male/Female): ", people[count].gender, MAX_STR_LEN);
        getStringInput("Nationality: ", people[count].nationality, MAX_STR_LEN);
        
        people[count].height = getValidFloat("Height (cm): ", 50.0, 250.0);
        people[count].weight = getValidFloat("Weight (kg): ", 10.0, 500.0);
        
        people[count].birthDate = getValidDateInput("Date of Birth (YYYY MM DD): ");
        
        getStringInput("Phone Number: ", people[count].phoneNumber, MAX_STR_LEN);
        
        // Get address information
        printf("\nAddress Information:\n");
        getStringInput("Postal Code: ", people[count].address.postalCode, MAX_STR_LEN);
        getStringInput("Country: ", people[count].address.country, MAX_STR_LEN);
        getStringInput("Region: ", people[count].address.region, MAX_STR_LEN);
        getStringInput("District: ", people[count].address.district, MAX_STR_LEN);
        getStringInput("City: ", people[count].address.city, MAX_STR_LEN);
        getStringInput("Street: ", people[count].address.street, MAX_STR_LEN);
        getStringInput("House: ", people[count].address.house, MAX_STR_LEN);
        getStringInput("Apartment: ", people[count].address.apartment, MAX_STR_LEN);
        
        count++;
    }
    
    if (count == 0) {
        printf("\nNo records entered. Exiting task.\n");
        return;
    }
    
    // Find the youngest person
    int youngestIdx = findYoungestPerson(people, count);
    
    if (youngestIdx >= 0) {
        printf("\nInformation about the youngest person:\n");
        displayPerson(&people[youngestIdx]);
    } else {
        printf("\nError: Could not determine the youngest person.\n");
    }
}
