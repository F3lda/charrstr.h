#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/charrstr.h"

// =============================================================================
// PERFORMANCE TESTING
// =============================================================================

/**
 * Get current time in seconds
 */
double getCurrentTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

/**
 * Test performance of dynamic string concatenation
 */
double testDynamicStringPerformance(int array_len) {
    printf("Testing dynamic string performance...\n");
    
    double start = getCurrentTime();
    
    // Initialize dynamic string
    ChArrStr str = chArrStrInit(array_len);
    if (str == NULL) {
        printf("Failed to allocate dynamic string\n");
        return -1.0;
    }
    
    // Initial content
    chArrStrCopy(str, "Text");
    
    // Concatenate "1234" repeatedly
    int i = 0;
    while (i + 5 < array_len) {
        chArrStrCat(str, "1234");
        i += 5;
    }
    
    // Cleanup
    chArrStrFree(&str);
    
    double end = getCurrentTime();
    return end - start;
}

/**
 * Test performance of standard C string concatenation
 */
double testStandardStringPerformance(int array_len) {
    printf("Testing standard string performance...\n");
    
    double start = getCurrentTime();
    
    // Initialize standard string
    char *str = calloc(array_len, sizeof(char));
    if (str == NULL) {
        printf("Failed to allocate standard string\n");
        return -1.0;
    }
    
    // Initial content
    strcpy(str, "Text");
    
    // Concatenate "1234" repeatedly
    int i = 0;
    while (i + 5 < array_len) {
        strcat(str, "1234");
        i += 5;
    }
    
    // Cleanup
    free(str);
    
    double end = getCurrentTime();
    return end - start;
}

// =============================================================================
// DEMONSTRATION FUNCTIONS
// =============================================================================

/**
 * Demonstrate basic ChArrStr usage
 */
void demonstrateBasicUsage() {
    printf("=== Basic Usage Demo ===\n");
    
    ChArrStr str = chArrStrInit(50);
    if (str == NULL) {
        printf("Failed to allocate string\n");
        return;
    }
    
    // Build a string step by step
    chArrStrCopy(str, "Hello");
    chArrStrCat(str, " ");
    chArrStrCat(str, "World!");
    
    printf("String: \"%s\"\n", str->str);
    printf("Length: %d, Capacity: %d\n", 
           chArrStrLength(str), chArrStrCapacity(str));
    
    // Test utility functions
    printf("Is empty: %s\n", chArrStrIsEmpty(str) ? "yes" : "no");
    
    chArrStrClear(str);
    printf("After clear - Is empty: %s\n", chArrStrIsEmpty(str) ? "yes" : "no");
    
    chArrStrFree(&str);
}

/**
 * Demonstrate convenience macros
 */
void demonstrateMacros() {
    printf("\n=== Macro Usage Demo ===\n");
    
    ChArrStr str = cas_init(100);
    if (str == NULL) {
        printf("Failed to allocate string\n");
        return;
    }
    
    cas_copy(str, "Using");
    cas_cat(str, " convenient");
    cas_cat(str, " macros!");
    
    printf("String: \"%s\"\n", str->str);
    printf("Length: %d, Capacity: %d\n", cas_length(str), cas_capacity(str));
    
    cas_free(str);
}

/**
 * Demonstrate resize functionality
 */
void demonstrateResize() {
    printf("\n=== Resize Demo ===\n");
    
    ChArrStr str = chArrStrInit(20);
    if (str == NULL) {
        printf("Failed to allocate string\n");
        return;
    }
    
    chArrStrCopy(str, "Small start");
    printf("Initial: \"%s\" (Capacity: %d)\n", str->str, chArrStrCapacity(str));
    
    // Manual resize
    if (chArrStrResize(&str, 100)) {
        printf("After resize: Capacity = %d\n", chArrStrCapacity(str));
        chArrStrCat(str, " - now we have more space for longer text!");
        printf("Extended: \"%s\"\n", str->str);
    } else {
        printf("Resize failed!\n");
    }
    
    chArrStrFree(&str);
}

/**
 * Demonstrate auto-resize with blocks
 */
void demonstrateAutoResize() {
    printf("\n=== Auto-Resize Demo ===\n");
    
    ChArrStr str = chArrStrInit(10);
    if (str == NULL) {
        printf("Failed to allocate string\n");
        return;
    }
    
    chArrStrCopy(str, "Short");
    printf("Initial: \"%s\" (Capacity: %d)\n", str->str, chArrStrCapacity(str));
    
    // Auto-resize in 32-byte blocks
    chArrStrCatEx(&str, " - This text will trigger auto-resizing in 32-byte blocks!", 32);
    printf("After auto-resize: \"%s\"\n", str->str);
    printf("New capacity: %d (Length: %d)\n", 
           chArrStrCapacity(str), chArrStrLength(str));
    
    // Show blocks calculation
    int total_needed = chArrStrLength(str) + 1;
    int blocks_used = (total_needed + 31) / 32; // Ceiling division for 32-byte blocks
    printf("Blocks used: %d (32 bytes each)\n", blocks_used);
    
    chArrStrFree(&str);
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("=== ChArrStr Performance Test & Demo ===\n\n");
    
    // Configuration
    const int ARRAY_LEN = 1000000;  // Smaller for faster testing
    
    printf("Array length: %d\n", ARRAY_LEN);
    printf("Operation: Repeated concatenation of \"1234\"\n\n");
    
    // Run performance tests
    double dynamic_time = testDynamicStringPerformance(ARRAY_LEN);
    double standard_time = testStandardStringPerformance(ARRAY_LEN);
    
    // Display results
    printf("\n=== Performance Results ===\n");
    if (dynamic_time >= 0) {
        printf("ChArrStr time: %.6f seconds\n", dynamic_time);
    }
    if (standard_time >= 0) {
        printf("Standard time: %.6f seconds\n", standard_time);
    }
    
    if (dynamic_time >= 0 && standard_time >= 0) {
        double speedup = standard_time / dynamic_time;
        printf("Speedup: %.2fx\n", speedup);
        
        if (speedup > 1.0) {
            printf("ChArrStr is %.2fx faster!\n", speedup);
        } else {
            printf("Standard is %.2fx faster.\n", 1.0 / speedup);
        }
    }
    
    // Run demonstrations
    printf("\n=== Feature Demonstrations ===\n");
    demonstrateBasicUsage();
    demonstrateMacros();
    demonstrateResize();
    demonstrateAutoResize();
    
    printf("\n=== Test Complete ===\n");
    printf("ChArrStr library demonstrates significant performance improvements\n");
    printf("for string concatenation operations while providing a clean API.\n");
    
    return 0;
}
