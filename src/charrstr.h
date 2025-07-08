#ifndef CHARRSTR_H
#define CHARRSTR_H

#include <stddef.h>
#include <stdbool.h>

/**
 * ChArrStr - High-Performance Dynamic String Library
 * 
 * A lightweight C string library that provides O(1) concatenation by tracking
 * string length, eliminating expensive strlen() calls.
 */

// =============================================================================
// TYPE DEFINITIONS
// =============================================================================

/**
 * Dynamic string structure
 * Uses flexible array member for efficient memory allocation
 */
typedef struct charrstr {
    int size;           // Total allocated size (including null terminator)
    int curr_size;      // Current string length (excluding null terminator)
    char str[];         // Flexible array member for string data
} *ChArrStr;

// =============================================================================
// CORE FUNCTIONS
// =============================================================================

/**
 * Initialize a new dynamic string with specified capacity
 * 
 * @param size Maximum capacity (including null terminator)
 * @return Pointer to new ChArrStr or NULL on allocation failure
 */
ChArrStr chArrStrInit(int size);

/**
 * Concatenate a C string to the dynamic string (no auto-resize)
 * 
 * @param str Target dynamic string
 * @param str2 Source C string to append
 * @return Number of characters actually copied
 */
int chArrStrCat(ChArrStr str, const char *str2);

/**
 * Concatenate a C string to the dynamic string
 * Auto-resizes in blocks if block_size > 0
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param str2 Source C string to append
 * @param block_size Size of allocation blocks (0 = no auto-resize)
 * @return Number of characters actually copied
 */
int chArrStrCatEx(ChArrStr *str, const char *str2, int block_size);

/**
 * Copy a C string to the dynamic string (overwrites existing content)
 * 
 * @param str Target dynamic string
 * @param str2 Source C string to copy
 * @return Number of characters copied
 */
int chArrStrCopy(ChArrStr str, const char *str2);

/**
 * Copy a C string to the dynamic string (overwrites existing content)
 * Auto-resizes in blocks if block_size > 0
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param str2 Source C string to copy
 * @param block_size Size of allocation blocks (0 = no auto-resize)
 * @return Number of characters copied
 */
int chArrStrCopyEx(ChArrStr *str, const char *str2, int block_size);

/**
 * Clear the dynamic string (set to empty)
 * 
 * @param str Dynamic string to clear
 */
void chArrStrClear(ChArrStr str);

/**
 * Free the dynamic string and set pointer to NULL
 * 
 * @param str Pointer to dynamic string pointer
 */
void chArrStrFree(ChArrStr *str);

/**
 * Get the current length of the string
 * 
 * @param str Dynamic string
 * @return Current string length, or -1 if str is NULL
 */
int chArrStrLength(ChArrStr str);

/**
 * Get the total capacity of the string
 * 
 * @param str Dynamic string
 * @return Total capacity, or -1 if str is NULL
 */
int chArrStrCapacity(ChArrStr str);

/**
 * Check if the string is empty
 * 
 * @param str Dynamic string
 * @return true if empty, false otherwise
 */
bool chArrStrIsEmpty(ChArrStr str);

/**
 * Resize the dynamic string to a new capacity
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param new_size New capacity (including null terminator)
 * @return 1 on success, 0 on failure (original string unchanged on failure)
 */
int chArrStrResize(ChArrStr *str, int new_size);

// =============================================================================
// CONVENIENCE MACROS
// =============================================================================

#define cas_init(size) chArrStrInit(size)
#define cas_cat(str, str2) chArrStrCat(str, str2)
#define cas_cat_ex(str, str2, block_size) chArrStrCatEx(&(str), str2, block_size)
#define cas_copy(str, str2) chArrStrCopy(str, str2)
#define cas_copy_ex(str, str2, block_size) chArrStrCopyEx(&(str), str2, block_size)
#define cas_clear(str) chArrStrClear(str)
#define cas_resize(str, new_size) chArrStrResize(&(str), new_size)
#define cas_free(str) chArrStrFree(&(str))
#define cas_length(str) chArrStrLength(str)
#define cas_capacity(str) chArrStrCapacity(str)
#define cas_empty(str) chArrStrIsEmpty(str)

#endif // CHARRSTR_H
