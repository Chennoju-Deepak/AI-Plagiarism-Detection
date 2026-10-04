
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declarations.h"

#define DOCUMENT_SIZE 5000
#define PATTERN_SIZE 100
#define MAX_MATCHES 100

static void menu(void);
static void loadDoc1(char document[]);
static void loadDoc2(char document[]);
static void preprocessDocs(char document1[], char document2[]);
static void runKMP(char document1[], char document2[]);
static void runRabinKarp(char document1[], char document2[]);
static void dsaAnalysis(char document1[], char document2[], float *score);
static void aiAnalysis(float *score);
static void generateReport(float dsaScore, float aiScore);
static void displayReport(void);
static void executeMenu(int choice, char document1[], char document2[],
                        float *dsaScore, float *aiScore);


int main(void)
{
    char document1[DOCUMENT_SIZE];
    char document2[DOCUMENT_SIZE];

    float dsaScore = 0;
    float aiScore = 0;

    int choice;

    document1[0] = '\0';
    document2[0] = '\0';

    while (1)
    {
        menu();

        scanf("%d", &choice);

        if (choice == 13)
        {
            printf("\nThank You!\n");
            break;
        }

        executeMenu(choice, document1, document2,
                    &dsaScore, &aiScore);
    }

    return 0;
}


static void menu(void)
{
    printf("             AI PLAGIARISM DETECTION SYSTEM\n");
    printf("1.  Load Document 1\n");
    printf("2.  Load Document 2\n");
    printf("3.  Preprocess Documents\n");
    printf("             DSA ANALYSIS      \n");
    printf("4.  Search Phrase using KMP\n");
    printf("5.  Search Phrase using Rabin-Karp\n");
    printf("6.  Calculate DSA Similarity\n");
    printf("7.  Detect Common Words\n");
    printf("8.  Detect Common Phrases\n");
    printf("            AI ANALYSIS     \n");
    printf("9.  AI Semantic Similarity\n");
    printf("           RESULTS         \n");
    printf("10. Display Documents\n");
    printf("11. Generate Plagiarism Report\n");
    printf("12. Display Final Report\n");
    printf("13. Exit\n");
    printf("Enter your choice: ");
}


static void loadDoc1(char document[])
{
    readFile("document1.txt", document);

    printf("\nDocument 1 Loaded Successfully.\n");
}


static void loadDoc2(char document[])
{
    readFile("document2.txt", document);

    printf("\nDocument 2 Loaded Successfully.\n");
}


static void preprocessDocs(char document1[], char document2[])
{
    preprocessText(document1);
    preprocessText(document2);

    printf("\nDocuments Preprocessed Successfully.\n");
}


static void runKMP(char document1[], char document2[])
{
    char pattern[PATTERN_SIZE];
    int positions[MAX_MATCHES];
    int matchCount;
    int k;

    getchar();

    printf("\nEnter phrase to search: ");

    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    preprocessText(pattern);

    printf("\nSearching in Document 1...\n");

    matchCount = KMPSearch(document1, pattern, positions);

    for (k = 0; k < matchCount; k++)
    {
        printf("Match Found at Position %d\n", positions[k]);
    }

    printf("\nSearching in Document 2...\n");

    matchCount = KMPSearch(document2, pattern, positions);

    for (k = 0; k < matchCount; k++)
    {
        printf("Match Found at Position %d\n", positions[k]);
    }
}


static void runRabinKarp(char document1[], char document2[])
{
    char pattern[PATTERN_SIZE];
    int positions[MAX_MATCHES];
    int matchCount;
    int k;

    getchar();

    printf("\nEnter phrase to search: ");

    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    preprocessText(pattern);

    printf("\nSearching in Document 1...\n");

    /*
       rabinKarpSearch() is the existing Rabin-Karp
       function from the other source file.
    */
    matchCount = rabinKarpSearch(document1, pattern, positions);

    for (k = 0; k < matchCount; k++)
    {
        printf("Match Found at Position %d\n", positions[k]);
    }

    printf("\nSearching in Document 2...\n");

    matchCount = rabinKarpSearch(document2, pattern, positions);

    for (k = 0; k < matchCount; k++)
    {
        printf("Match Found at Position %d\n", positions[k]);
    }
}


static void dsaAnalysis(char document1[], char document2[], float *score)
{
    *score = calculateSimilarity(document1, document2);

    printf("\n        DSA SIMILARITY      \n");
    printf("Similarity Percentage : %.2f%%\n", *score);

    if (*score >= 70)
    {
        printf("Verdict : High Similarity\n");
    }
    else if (*score >= 40)
    {
        printf("Verdict : Moderate Similarity\n");
    }
    else
    {
        printf("Verdict : Low Similarity\n");
    }
}


static void aiAnalysis(float *score)
{
    printf("\n        AI SEMANTIC SIMILARITY        \n");

    *score = getAISimilarity();

    printf("AI Semantic Similarity : %.2f%%\n", *score);
}


static void generateReport(float dsaScore, float aiScore)
{
    FILE *report;
    float overallScore;

    overallScore = (dsaScore + aiScore) / 2;

    report = fopen("plagiarism_report.txt", "w");

    if (report == NULL)
    {
        printf("\nError: Could not create plagiarism report.\n");
        return;
    }

    fprintf(report, "        AI PLAGIARISM DETECTION REPORT\n");
    fprintf(report, "DOCUMENT INFORMATION\n");
    fprintf(report, "Document 1 : document1.txt\n");
    fprintf(report, "Document 2 : document2.txt\n\n");

    fprintf(report, "DSA ANALYSIS\n");
    fprintf(report, "DSA Similarity          : %.2f%%\n", dsaScore);

    fprintf(report, "\nAI ANALYSIS\n");
    fprintf(report, "AI Semantic Similarity  : %.2f%%\n", aiScore);

    fprintf(report, "\nFINAL RESULT\n");
    fprintf(report, "Combined Similarity     : %.2f%%\n", overallScore);

    if (overallScore >= 70)
    {
        fprintf(report, "Similarity Level        : HIGH\n");
    }
    else if (overallScore >= 40)
    {
        fprintf(report, "Similarity Level        : MODERATE\n");
    }
    else
    {
        fprintf(report, "Similarity Level        : LOW\n");
    }

    fprintf(report, "             END OF REPORT\n");

    fclose(report);

    printf("\nPlagiarism report generated successfully.\n");
    printf("Saved as: plagiarism_report.txt\n");
}


static void displayReport(void)
{
    FILE *report;
    char ch;

    report = fopen("plagiarism_report.txt", "r");

    if (report == NULL)
    {
        printf("\nNo report found.\n");
        printf("Please select option 11 first.\n");
        return;
    }

    printf("\n");
    printf("           FINAL PLAGIARISM REPORT\n");

    while ((ch = fgetc(report)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(report);
}


static void executeMenu(int choice,
                        char document1[],
                        char document2[],
                        float *dsaScore,
                        float *aiScore)
{
    switch (choice)
    {
        case 1:
            loadDoc1(document1);
            break;

        case 2:
            loadDoc2(document2);
            break;

        case 3:
            preprocessDocs(document1, document2);
            break;

        case 4:
            runKMP(document1, document2);
            break;

        case 5:
            runRabinKarp(document1, document2);
            break;

        case 6:
            dsaAnalysis(document1, document2, dsaScore);
            break;

        case 7:
            detectCommonWords(document1, document2);
            break;

        case 8:
            detectCommonPhrases(document1, document2);
            break;

        case 9:
            aiAnalysis(aiScore);
            break;

        case 10:
            printf("\n      DOCUMENT 1     \n");
            printf("%s\n", document1);

            printf("\n      DOCUMENT 2      \n");
            printf("%s\n", document2);
            break;

        case 11:
            generateReport(*dsaScore, *aiScore);
            break;

        case 12:
            displayReport();
            break;

        default:
            printf("\nInvalid Choice. Please try again.\n");
    }
}

