#include "coder.h"
#include <ctype.h>
#include <string.h>

/*
 * Morse table mapping uppercase 'A' through 'Z'.
 * Use this lookup array for your character translations.
 * DO NOT MODIFY
 */
static const MorseMapping MORSE_TABLE[26] = {
    {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},  {'E', "."},
    {'F', "..-."}, {'G', "--."},  {'H', "...."}, {'I', ".."},   {'J', ".---"},
    {'K', "-.-"},  {'L', ".-.."}, {'M', "--"},   {'N', "-."},   {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},
    {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}};

/* ========================================================================= */
/* Helper Functions for Part 1 (Recursive Metrics)                          */
/* ========================================================================= */

/**
 * Returns true if the character is an English vowel (a, e, i, o, u).
 * DO NOT MODIFY
 */
static bool is_vowel(char c) {
  char lower = (char)tolower((unsigned char)c);
  return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
          lower == 'u');
}

/**
 * TODO: Implement a recursive helper function for analyzeTextRecursive.
 *
 * Requirements & Hints:
 * 1. Base case: If *text == '\0', return a TextMetrics struct where all
 *    four integer fields are initialized to 0.
 * 2. Recursive step:
 *    - Recurse on the tail: analyze_helper(text + 1, *text)
 *    - Evaluate *text:
 *      * If isalpha(*text): increment total_chars.
 *        - If is_vowel(*text): increment vowel_count.
 *        - Otherwise: increment consonant_count.
 *      * Token transition: If *text is non-whitespace (!isspace) and
 *        prev_char is whitespace or '\0' (start of string), increment
 * token_count.
 * 3. NO LOOPS (for, while, do-while) allowed!
 */
static TextMetrics analyze_helper(const char *text, char prev_char) {
  TextMetrics metrics = {0, 0, 0, 0};

  /* YOUR RECURSIVE IMPLEMENTATION HERE */
}

/* DO NOT MODIFY */
TextMetrics analyzeTextRecursive(const char *text) {
  if (text == NULL) {
    TextMetrics zero = {0, 0, 0, 0};
    return zero;
  }
  /* '\0' as prev_char signifies start of string */
  return analyze_helper(text, '\0');
}

/* ========================================================================= */
/* Helper Functions for Part 2 (Recursive Morse Encoding)                   */
/* ========================================================================= */

/**
 * Helper: Recursively copy characters from src string into dest buffer.
 * Stops when '\0' is reached or remaining_space runs out.
 * Returns the number of characters copied.
 * DO NOT MODIFY
 */
static int copy_string_recursive(char *dest, const char *src,
                                 int remaining_space) {
  if (*src == '\0' || remaining_space <= 0) {
    return 0;
  }
  *dest = *src;
  return 1 + copy_string_recursive(dest + 1, src + 1, remaining_space - 1);
}

/**
 * TODO: Implement a recursive helper function to build the Morse output buffer.
 *
 * Parameters:
 * - text: Current pointer in the source text.
 * - out_buffer: Base pointer of output buffer.
 * - out_idx: Current write index in out_buffer.
 * - max_len: Maximum size of out_buffer.
 * - in_whitespace: True if the previous processed char was whitespace.
 * - needs_letter_space: True if an alphabetical Morse symbol was just placed
 *                       and the next letter needs a preceding ' '.
 *
 * Rules:
 * 1. Base case: If *text == '\0' or out_idx >= max_len - 1:
 *    - Null-terminate: out_buffer[out_idx] = '\0'.
 *    - Return out_idx.
 * 2. If *text is whitespace:
 *    - If !in_whitespace and out_idx > 0: append " / " (or collapse any
 * trailing space).
 *    - Recurse with text + 1, in_whitespace = true, needs_letter_space = false.
 * 3. If isalpha(*text):
 *    - If needs_letter_space: write ' ' to out_buffer.
 *    - Lookup Morse string in MORSE_TABLE[toupper(*text) - 'A'].morse.
 *    - Copy string into out_buffer using copy_string_recursive.
 *    - Recurse with text + 1, in_whitespace = false, needs_letter_space = true.
 * 4. Punctuation / other chars:
 *    - Ignore / skip character and recurse with text + 1.
 */
static int morse_helper(const char *text, char *out_buffer, int out_idx,
                        int max_len, bool in_whitespace,
                        bool needs_letter_space) {
  /* YOUR RECURSIVE IMPLEMENTATION HERE */
}

/* DO NOT MODIFY */
int encodeMorseRecursive(const char *text, char *out_buffer,
                         int max_buffer_len) {
  if (text == NULL || out_buffer == NULL || max_buffer_len <= 0) {
    return 0;
  }
  return morse_helper(text, out_buffer, 0, max_buffer_len, true, false);
}
