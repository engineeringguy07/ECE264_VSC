# Take Home Programming Test 1: Recursive Text Entropy & Morse Encoder

## Overview

In telecommunications and data compression, text streams are analyzed for information density and encoded into variable-length symbols. In this assignment, you will build a lightweight stream analyzer and recursive Morse code encoder using custom structs and recursive string traversal.

---

## Release and due date

- Release: Wednesday, November 11 at 9:00pm
- **Due: Friday, November 13 at 9:00pm**
- Note: There is no extension for this take-home quiz, you will have 48 hours from the release time to submit your solution.

## Data Structures (`coder.h`)

The header file `coder.h` defines two primary custom data structures along with the function prototypes:

### 1. `TextMetrics`

The `TextMetrics` structure aggregates statistical character and word counts during the recursive analysis of an input string in Part 1. Because C functions cannot directly return multiple values, returning a struct by value allows `analyzeTextRecursive` to return all metrics cleanly without requiring multiple pointer arguments.

Note: This entire assignment is **case-insensitive**, meaning that lowercase and uppercase letters are treated the same. For example, 'a' and 'A' should both be counted as vowels and 'b' and 'B' should both be counted as consonants. Feel free to use the `toupper()` function from the `<ctype.h>` header file to convert characters to uppercase.

```c
typedef struct {
    int total_chars;        // Total alphabetic letters encountered
    int vowel_count;        // Total vowels (a, e, i, o, u, case-insensitive)
    int consonant_count;    // Total consonants (all other letters A-Z)
    int token_count;        // Count of delimited tokens/words
} TextMetrics;
```

#### Field Descriptions:
- **`total_chars`** (`int`):
  Tracks the total count of alphabetic letters (`A`-`Z`, `a`-`z`) encountered in the string. Non-alphabetic characters (digits, symbols, whitespace) are ignored and do not count toward this total.
- **`vowel_count`** (`int`):
  Tracks the number of English vowels encountered (`'a'`, `'e'`, `'i'`, `'o'`, `'u'`, case-insensitive).
- **`consonant_count`** (`int`):
  Tracks the number of consonants encountered (any alphabetic letter that is not a vowel). Notice that for any valid text:
  `total_chars = vowel_count + consonant_count`
- **`token_count`** (`int`):
  Tracks the total number of words/tokens. A token is defined as a contiguous sequence of non-whitespace characters. A token begins when a non-whitespace character (`!isspace`) is preceded by a whitespace character (`isspace`) or is at the very beginning of the string.

> **Base Case Tip:** For an empty string (or when recursion reaches `'\0'`), the base case returns a `TextMetrics` struct with all four fields initialized to `0`: `(TextMetrics){0, 0, 0, 0}`.

---

### 2. `MorseMapping`

The `MorseMapping` structure represents an entry in a lookup table (key-value pair) associating an uppercase English letter with its Morse code dot-dash representation.

```c
typedef struct {
    char letter;            // Uppercase character 'A'-'Z'
    const char *morse;      // String of dots and dashes (e.g., ".-")
} MorseMapping;
```

#### Field Descriptions:
- **`letter`** (`char`):
  The single uppercase character key (`'A'` through `'Z'`).
- **`morse`** (`const char *`):
  A pointer to a null-terminated string literal of dots `.` and dashes `-` representing the Morse code sequence (e.g., `".-"` for `'A'`, `"-..."` for `'B'`). Because string literals reside in static read-only memory, storing `const char *` avoids dynamic memory allocation and pointer duplication.

#### Usage:
A lookup table `MORSE_TABLE` containing 26 `MorseMapping` entries is defined in `coder.c`. Because it is ordered alphabetically from `'A'` (index 0) to `'Z'` (index 25), you can look up any uppercase character in `O(1)` time using the offset:
```c
int index = toupper((unsigned char)c) - 'A';
const char *morse_code = MORSE_TABLE[index].morse;
```

---

### Function Prototypes

```c
// Part 1: Recursively traverses text and returns accumulated metrics
TextMetrics analyzeTextRecursive(const char *text);

// Part 2: Recursively converts text to Morse code written into out_buffer
int encodeMorseRecursive(const char *text, char *out_buffer, int max_buffer_len);
```

---

## Part 1: Recursive Stream Metrics (`analyzeTextRecursive`)

### Objective
Recursively traverse a null-terminated string and populate a `TextMetrics` struct without using standard looping constructs (`for`, `while`, `do-while`).

### Function Signature
```c
TextMetrics analyzeTextRecursive(const char *text);
```

### Rules & Specification
1. **Base Case:** Reaching the null-terminator (`'\0'`) returns a `TextMetrics` struct with all fields initialized to `0`.
2. **Recursive Step:** Inspect the current character `*text`, recursively process the tail (`text + 1`), and combine the results:
   - **`total_chars`**: Increment by 1 if the current character is an alphabetic letter (`isalpha`).
   - **`vowel_count`**: Increment by 1 if the current character is a vowel (`a, e, i, o, u`, case-insensitive).
   - **`consonant_count`**: Increment by 1 if the current character is an alphabetic letter but not a vowel.
   - **`token_count`**: Count transitions that define words. A token is defined as a contiguous sequence of non-whitespace characters. Increment `token_count` by 1 if the current character is non-whitespace (`!isspace`) and the preceding character was whitespace (or the start of the string).
     *(Hint: You may write a helper function with an extra parameter tracking the previous character: `analyzeHelper(const char *text, char prev_char)`).*

---

## Part 2: Recursive Morse Formatter (`encodeMorseRecursive`)

### Objective
Recursively translate an input string into Morse code representation, writing the result into a caller-provided output buffer.

### Function Signature
```c
int encodeMorseRecursive(const char *text, char *out_buffer, int max_buffer_len);
```

### Morse Lookup Table
Use this standard array of structs inside your `coder.c`:

```c
static const MorseMapping MORSE_TABLE[26] = {
    {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."},    {'F', "..-."}, {'G', "--."},  {'H', "...."},
    {'I', ".."},   {'J', ".---"}, {'K', "-.-"},  {'L', ".-.."},
    {'M', "--"},   {'N', "-."},   {'O', "---"},  {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},
    {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};
```

### Rules & Specification
1. **Letter Translation:**
   - Letters are case-insensitive (`'a'` and `'A'` both map to `.-`).
   - Each Morse symbol corresponding to an alphabetic letter must be separated by a single space `' '`.
2. **Word Separation:**
   - Whitespace characters in the input text should be represented in the output buffer by a forward slash followed by a space: `"/ "`. Multiple consecutive whitespace characters in the input count as a single word break.
3. **Punctuation & Unknowns:**
   - Skip punctuation marks (e.g., `,`, `.`, `!`). Do not output symbols for them.
4. **Buffer Safety:**
   - Never write past `max_buffer_len - 1`. Always null-terminate the output buffer.
   - Return the total number of characters successfully written to `out_buffer` (excluding the null terminator).
5. **Recursion Requirement:**
   - Must be implemented using recursion to advance through `text` (or via a recursive helper that tracks current indices). No loops allowed.

### Example I/O
- Input: `"SOS"`
  - Output: `"... --- ..."`
- Input: `"Go west"`
  - Output: `"--. --- / .-- . ... -"`

---

## Files Provided

- `main.c` - Test driver and comparison harness (DO NOT MODIFY)
- `coder.h` - Header definitions and function prototypes (DO NOT MODIFY)
- `coder.c` - Your implementation goes here
- `inputs/` - Test input text files
- `expected/` - Expected analysis statistics and encoded outputs

---

## Building and Testing

```bash
# Compile
gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror main.c coder.c -o coder

# Run with an input file
./coder inputs/input_1.txt

# Compare output with expected
./coder inputs/input_1.txt > output.txt
diff output.txt expected/expected_1.txt
```

---

## Submission & Grading

Submit only `coder.c` to Gradescope.

- **File submission:** 10%
- **Compilation without warnings:** 10%
- **Part 1 Correctness (`analyzeTextRecursive`):** 40%
- **Part 2 Correctness (`encodeMorseRecursive`):** 40%