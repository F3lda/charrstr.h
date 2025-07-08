#include "charrstr.h"
#include <stdlib.h>
#include <string.h>

// =============================================================================
// CORE FUNCTIONS
// =============================================================================

/**
 * Initialize a new dynamic string with specified capacity
 * 
 * @param size Maximum capacity (including null terminator)
 * @return Pointer to new ChArrStr or NULL on allocation failure
 */
ChArrStr chArrStrInit(int size) {
    if (size <= 0) {
        return NULL;
    }
    
    ChArrStr new_str = malloc(sizeof(struct charrstr) + sizeof(char) * size);
    if (new_str == NULL) {
        return NULL;
    }
    
    new_str->size = size;
    new_str->curr_size = 0;
    new_str->str[0] = '\0';
    
    return new_str;
}

/**
 * Concatenate a C string to the dynamic string (no auto-resize)
 * 
 * @param str Target dynamic string
 * @param str2 Source C string to append
 * @return Number of characters actually copied
 */
int chArrStrCat(ChArrStr str, const char *str2) {
    if (str == NULL || str2 == NULL) {
        return 0;
    }
    
    int chars_copied = 0;
    int i = 0;
    
    // Copy characters while there's space and source has data
    while (str->curr_size + 1 < str->size && str2[i] != '\0') {
        str->str[str->curr_size++] = str2[i++];
        chars_copied++;
    }
    
    // Always null-terminate
    str->str[str->curr_size] = '\0';
    
    return chars_copied;
}

/**
 * Concatenate a C string to the dynamic string
 * Auto-resizes in blocks if block_size > 0
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param str2 Source C string to append
 * @param block_size Size of allocation blocks (0 = no auto-resize)
 * @return Number of characters actually copied
 */
int chArrStrCatEx(ChArrStr *str, const char *str2, int block_size) {
    if (str == NULL || *str == NULL || str2 == NULL) {
        return 0;
    }
    
    int str2_len = strlen(str2);
    int chars_copied = 0;
    int i = 0;
    
    // Check if we need to resize
    if (block_size > 0 && (*str)->curr_size + str2_len + 1 > (*str)->size) {
        // Calculate how many blocks we need
        int total_needed = (*str)->curr_size + str2_len + 1;
        int blocks_needed = (total_needed + block_size - 1) / block_size; // Ceiling division
        int new_size = blocks_needed * block_size;
        
        if (!chArrStrResize(str, new_size)) {
            // Resize failed, copy what we can
            while ((*str)->curr_size + 1 < (*str)->size && str2[i] != '\0') {
                (*str)->str[(*str)->curr_size++] = str2[i++];
                chars_copied++;
            }
            (*str)->str[(*str)->curr_size] = '\0';
            return chars_copied;
        }
    }
    
    // Copy characters while there's space and source has data
    while ((*str)->curr_size + 1 < (*str)->size && str2[i] != '\0') {
        (*str)->str[(*str)->curr_size++] = str2[i++];
        chars_copied++;
    }
    
    // Always null-terminate
    (*str)->str[(*str)->curr_size] = '\0';
    
    return chars_copied;
}

/**
 * Copy a C string to the dynamic string (overwrites existing content)
 * 
 * @param str Target dynamic string
 * @param str2 Source C string to copy
 * @return Number of characters copied
 */
int chArrStrCopy(ChArrStr str, const char *str2) {
    if (str == NULL) {
        return 0;
    }
    
    // Clear existing content
    str->curr_size = 0;
    str->str[0] = '\0';
    
    // Copy new content
    return chArrStrCat(str, str2);
}

/**
 * Copy a C string to the dynamic string (overwrites existing content)
 * Auto-resizes in blocks if block_size > 0
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param str2 Source C string to copy
 * @param block_size Size of allocation blocks (0 = no auto-resize)
 * @return Number of characters copied
 */
int chArrStrCopyEx(ChArrStr *str, const char *str2, int block_size) {
    if (str == NULL || *str == NULL) {
        return 0;
    }
    
    // Clear existing content
    (*str)->curr_size = 0;
    (*str)->str[0] = '\0';
    
    // Copy new content
    return chArrStrCatEx(str, str2, block_size);
}

/**
 * Clear the dynamic string (set to empty)
 * 
 * @param str Dynamic string to clear
 */
void chArrStrClear(ChArrStr str) {
    if (str != NULL) {
        str->curr_size = 0;
        str->str[0] = '\0';
    }
}

/**
 * Free the dynamic string and set pointer to NULL
 * 
 * @param str Pointer to dynamic string pointer
 */
void chArrStrFree(ChArrStr *str) {
    if (str != NULL && *str != NULL) {
        free(*str);
        *str = NULL;
    }
}

/**
 * Get the current length of the string
 * 
 * @param str Dynamic string
 * @return Current string length, or -1 if str is NULL
 */
int chArrStrLength(ChArrStr str) {
    return (str != NULL) ? str->curr_size : -1;
}

/**
 * Get the total capacity of the string
 * 
 * @param str Dynamic string
 * @return Total capacity, or -1 if str is NULL
 */
int chArrStrCapacity(ChArrStr str) {
    return (str != NULL) ? str->size : -1;
}

/**
 * Check if the string is empty
 * 
 * @param str Dynamic string
 * @return true if empty, false otherwise
 */
bool chArrStrIsEmpty(ChArrStr str) {
    return (str == NULL || str->curr_size == 0);
}

/**
 * Resize the dynamic string to a new capacity
 * 
 * @param str Pointer to dynamic string pointer (may be modified if reallocation occurs)
 * @param new_size New capacity (including null terminator)
 * @return 1 on success, 0 on failure (original string unchanged on failure)
 */
int chArrStrResize(ChArrStr *str, int new_size) {
    if (str == NULL || *str == NULL || new_size <= 0) {
        return 0;
    }
    
    // Check if new size is smaller than current content
    if (new_size <= (*str)->curr_size) {
        return 0; // Cannot shrink below current content size
    }
    
    // Calculate new total size needed
    size_t new_total_size = sizeof(struct charrstr) + sizeof(char) * new_size;
    
    // Attempt reallocation
    ChArrStr new_str = realloc(*str, new_total_size);
    if (new_str == NULL) {
        return 0; // Reallocation failed, original string unchanged
    }
    
    // Update the string pointer and size
    *str = new_str;
    (*str)->size = new_size;
    
    return 1; // Success
}
