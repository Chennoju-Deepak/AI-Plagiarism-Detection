#include <stdio.h> 
#include <string.h>
#include "declarations.h"
// Function for building LPS 
void computeLPS(char pattern[], int lps[]) 
{ 
    int length = 0;  
    int i = 1; 
    lps[0] = 0;  
    while (pattern[i] != '\0') 
    { 
        if (pattern[i] == pattern[length]) 
        { 
            length++; 
            lps[i] = length; 
            i++; 
        } 
        else
        { 
            if (length != 0) 
            { 
                length = lps[length - 1]; 
            } 
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 
// KMP Searching function 
int KMPSearch(char text[], char pattern[], int positions[]) 
{ 
    int n = strlen(text); 
    int m = strlen(pattern); 
    int lps[100]; 
    int matchCount = 0;
    computeLPS(pattern, lps); 
    int i = 0; 
    int j = 0; 
    while (i < n) 
    { 
        if (text[i] == pattern[j]) 
        { 
            i++; 
            j++; 
        } 
        if (j == m) 
        { 
            positions[matchCount] = i - j; 
            matchCount++; 
            j = lps[j - 1]; 
        } 
        else if (i < n && text[i] != pattern[j]) 
        { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i++; 
        } 
    } 
    return matchCount; 
}