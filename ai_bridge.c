#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"
float getAISimilarity()
{
    float score;
    // Run Python AI script
    system("python ai_semantic.py");
    FILE *fp = fopen("ai_result.txt", "r");
    if(fp == NULL)
    {
        printf("Cannot read AI result.\n");
        return 0;
    }
    fscanf(fp, "%f", &score);
    fclose(fp);
    return score;
}