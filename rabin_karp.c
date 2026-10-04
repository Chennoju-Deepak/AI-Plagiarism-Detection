#include <stdio.h>
#include <string.h>
#include "declarations.h"
#define d 256
#define q 101
int rabinKarpSearch(char text[], char pattern[], int positions[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    int matchCount = 0;
    for(i = 0; i < m - 1; i++)
        h = (h * d) % q;
    for(i = 0; i < m; i++)
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    for(i = 0; i <= n - m; i++)
    {
        if(p == t)
        {
            for(j = 0; j < m; j++)
            {
                if(text[i + j] != pattern[j])
                    break;
            }
            if(j == m)
            {
                positions[matchCount] = i;
                matchCount++;
            }
        }
        if(i < n - m)
        {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if(t < 0)
                t = t + q;
        }
    }
    return matchCount;
}