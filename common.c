#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declarations.h"
int splitWords(char text[], char words[][50])
{
    int wordCount = 0;
    char buffer[50];
    int bufIndex = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (c != ' ')
        {
            buffer[bufIndex] = c;
            bufIndex++;
        }
        else
        {
            if (bufIndex > 0)
            {
                buffer[bufIndex] = '\0';
                strcpy(words[wordCount], buffer);
                wordCount++;
                bufIndex = 0;
            }
        }
    }
    if (bufIndex > 0)
    {
        buffer[bufIndex] = '\0';
        strcpy(words[wordCount], buffer);
        wordCount++;
    }
    return wordCount;
}
int compareWords(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}
int buildPhrases(char words[][50], int count, char phrases[][160])
{
    int phraseCount = 0;
    for (int i = 0; i <= count - 3; i++)
    {
        strcpy(phrases[phraseCount], words[i]);
        strcat(phrases[phraseCount], " ");
        strcat(phrases[phraseCount], words[i + 1]);
        strcat(phrases[phraseCount], " ");
        strcat(phrases[phraseCount], words[i + 2]);
        phraseCount++;
    }
    return phraseCount;
}
void detectCommonWords(char doc1[], char doc2[])
{
    char words1[500][50];
    char words2[500][50];
    int count1 = splitWords(doc1, words1);
    int count2 = splitWords(doc2, words2);
    qsort(words1, count1, 50, compareWords);
    qsort(words2, count2, 50, compareWords);
    printf("\n        COMMON WORDS       n");
    int i = 0, j = 0;
    int printed = 1;
    char lastPrinted[50] = "";
    while (i < count1 && j < count2)
    {
        int cmp = strcmp(words1[i], words2[j]);

        if (cmp == 0)
        {
            if (strcmp(words1[i], lastPrinted) != 0)
            {
                printf("%d. %s\n", printed, words1[i]);
                printed++;
                strcpy(lastPrinted, words1[i]);
            }
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
    if (printed == 1)
    {
        printf("No common words found.\n");
    }
}
void detectCommonPhrases(char doc1[], char doc2[])
{
    char words1[500][50];
    char words2[500][50];
    int wcount1 = splitWords(doc1, words1);
    int wcount2 = splitWords(doc2, words2);
    printf("\n        COMMON PHRASES      \n");
    if (wcount1 < 3 || wcount2 < 3)
    {
        printf("No common phrases found.\n");
        return;
    }
    char phrases1[500][160];
    char phrases2[500][160];
    int pcount1 = buildPhrases(words1, wcount1, phrases1);
    int pcount2 = buildPhrases(words2, wcount2, phrases2);
    qsort(phrases1, pcount1, 160, compareWords);
    qsort(phrases2, pcount2, 160, compareWords);
    int i = 0, j = 0;
    int found = 0;
    char lastPrinted[160] = "";
    while (i < pcount1 && j < pcount2)
    {
        int cmp = strcmp(phrases1[i], phrases2[j]);
        if (cmp == 0)
        {
            if (strcmp(phrases1[i], lastPrinted) != 0)
            {
                printf("%s\n", phrases1[i]);
                found = 1;
                strcpy(lastPrinted, phrases1[i]);
            }
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
    if (found == 0)
    {
        printf("No common phrases found.\n");
    }
}