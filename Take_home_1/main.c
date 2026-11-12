#include "coder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 8192
#define MAX_OUTPUT_SIZE 32768

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: could not open file %s\n", argv[1]);
        return 1;
    }

    char *buffer = malloc(MAX_INPUT_SIZE);
    if (!buffer) {
        fclose(fp);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, MAX_INPUT_SIZE - 1, fp);
    buffer[bytes_read] = '\0';
    fclose(fp);

    /* Part 1: Recursive Metrics */
    TextMetrics metrics = analyzeTextRecursive(buffer);
    printf("=== Text Metrics ===\n");
    printf("Total Letters:   %d\n", metrics.total_chars);
    printf("Vowels:          %d\n", metrics.vowel_count);
    printf("Consonants:      %d\n", metrics.consonant_count);
    printf("Tokens:          %d\n", metrics.token_count);

    /* Part 2: Recursive Morse Code */
    char *morse_out = malloc(MAX_OUTPUT_SIZE);
    if (!morse_out) {
        free(buffer);
        return 1;
    }

    int chars_written = encodeMorseRecursive(buffer, morse_out, MAX_OUTPUT_SIZE);
    printf("\n=== Morse Encoding ===\n");
    printf("Length:  %d\n", chars_written);
    printf("Encoded: %s\n", morse_out);

    free(buffer);
    free(morse_out);
    return 0;
}
