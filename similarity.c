#include <stdio.h>
#include <string.h>
#include "declarations.h"
#include <stdlib.h>
float calculateSimilarity(char doc1[], char doc2[])
{
    char words1[500][50];
    char words2[500][50];
    int count1 = 0;
    int count2 = 0;
    int common = 0;
    count1 = splitWords(doc1, words1);
    count2 = splitWords(doc2, words2);
     common = countCommonWords(words1,count1,words2,count2);
    int unique = count1 + count2 - common;
    if(unique == 0) return 0;
    return ((float)common / unique) * 100;
}
int countCommonWords(char words1[][50], int count1, char words2[][50], int count2)
{
    qsort(words1, count1, 50, compareWords);
    qsort(words2, count2, 50, compareWords);
    int i = 0, j = 0;
    int common = 0;
    while (i < count1 && j < count2)
    {
        int cmp = strcmp(words1[i], words2[j]);
        if (cmp == 0)
        {
            common++;
            i++;
            j++;
        }
        else if (cmp < 0)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return common;
}