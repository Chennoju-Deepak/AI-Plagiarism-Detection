#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "declarations.h"
// Function for reading a text file
void readFile(char filename[], char text[])
{
    FILE *fp;
    char line[200];
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }
    text[0] = '\0';
    while (fgets(line, sizeof(line), fp))
    {
        strcat(text, line);
    }
    fclose(fp);
}
// Function for preprocessing text
void preprocessText(char text[])
{
    int i, j = 0;
    char temp[5000];
    for (i = 0; text[i] != '\0'; i++)
    {
        char ch = tolower(text[i]);
        if (isalnum(ch) || ch == ' ')
        {
            temp[j] = ch;
            j++;
        }
    }
    temp[j] = '\0';
    strcpy(text, temp);
}