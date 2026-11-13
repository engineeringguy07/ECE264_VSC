#ifndef CODER_H
#define CODER_H

#include <stdbool.h>

typedef struct {
    int total_chars;        /* Total alphabetic letters encountered */
    int vowel_count;        /* Total vowels (a, e, i, o, u, case-insensitive) */
    int consonant_count;    /* Total consonants (all other letters A-Z) */
    int token_count;        /* Count of delimited tokens/words */
} TextMetrics;

typedef struct {
    char letter;            /* Uppercase character 'A'-'Z' */
    const char *morse;      /* String of dots and dashes (e.g., ".-") */
} MorseMapping;

/**
 * Recursively analyzes text metrics (letters, vowels, consonants, tokens).
 * Loops (for, while, do-while) are strictly forbidden.
 */
TextMetrics analyzeTextRecursive(const char *text);

/**
 * Recursively encodes text to Morse code written into out_buffer.
 * Loops (for, while, do-while) are strictly forbidden.
 * Returns the number of characters written to out_buffer (excluding '\0').
 */
int encodeMorseRecursive(const char *text, char *out_buffer, int max_buffer_len);

#endif /* CODER_H */
