/**
 * Task 1: Character Counting
 * A program to count occurrences of a specific letter in multiple sentences.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCE_LEN 1000
#define MAX_SENTENCES 10

/**
 * Counts occurrences of a specific letter in a given string.
 * The search is case-insensitive.
 * 
 * @param str The string to search in
 * @param letter The letter to count
 * @return The number of occurrences of the letter in the string
 */
int countLetterOccurrences(const char *str, char letter) {
    int count = 0;
    char lowerLetter = tolower(letter);
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (tolower(str[i]) == lowerLetter) {
            count++;
        }
    }
    
    return count;
}

void runTask1() {
    printf("\n=== Task 1: Character Counting ===\n");
    
    char sentences[MAX_SENTENCES][MAX_SENTENCE_LEN];
    char letter;
    int numSentences;
    int totalOccurrences = 0;
    
    printf("Enter the number of sentences (1-%d): ", MAX_SENTENCES);
    if (scanf("%d", &numSentences) != 1 || numSentences < 1 || numSentences > MAX_SENTENCES) {
        printf("Invalid input. Setting to 1.\n");
        numSentences = 1;
    }
    
    // Clear the input buffer
    while (getchar() != '\n');
    
    printf("Enter the letter to count: ");
    if (scanf(" %c", &letter) != 1) {
        printf("Invalid input. Using 'a' as default.\n");
        letter = 'a';
    }
    
    // Clear the input buffer
    while (getchar() != '\n');
    
    // Read sentences
    for (int i = 0; i < numSentences; i++) {
        printf("Enter sentence %d: ", i + 1);
        if (fgets(sentences[i], MAX_SENTENCE_LEN, stdin) == NULL) {
            printf("Error reading sentence. Using empty string.\n");
            sentences[i][0] = '\0';
            continue;
        }
        
        // Remove newline character if present
        size_t len = strlen(sentences[i]);
        if (len > 0 && sentences[i][len - 1] == '\n') {
            sentences[i][len - 1] = '\0';
        }
    }
    
    // Count occurrences in each sentence and display
    printf("\nResults:\n");
    for (int i = 0; i < numSentences; i++) {
        int occurrences = countLetterOccurrences(sentences[i], letter);
        totalOccurrences += occurrences;
        
        printf("Sentence %d: \"%s\" - %d occurrence(s) of '%c'\n", 
               i + 1, sentences[i], occurrences, letter);
    }
    
    printf("\nTotal occurrences of '%c': %d\n", letter, totalOccurrences);
}
