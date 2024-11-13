#include <string.h>

// Space-Deliniated Match
static inline int match(void *ptr, const char *entry) {
    char *s = (char*)ptr;
    // Navigate to the start of the next entry
    while (*s == ' ') s++;
    if (!*s) return 0; // EOL, return 0
    
    // Save the start of the entry
    char *start = s;
    
    // Navigate to the end of the entry
    while (*s && *s != ' ') s++;
    
    // Temporarily null-terminate the entry
    char temp = *s;
    *s = '\0';
    
    // Compare the entry with the target string
    int match = strcmp(start, entry) == 0;
    
    // Restore the original string
    *s = temp;
    
    return match ? 1 : 0;
}


