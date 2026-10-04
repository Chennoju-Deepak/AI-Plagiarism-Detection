#ifndef DECLARATIONS_H
#define DECLARATIONS_H
// ===================== Preprocessing =====================
void readFile(char filename[], char text[]);
void preprocessText(char text[]);
// ===================== KMP Algorithm =====================
int KMPSearch(char text[], char pattern[], int positions[]);
// ===================== Rabin-Karp Algorithm =====================
int rabinKarpSearch(char text[], char pattern[], int positions[]);
// ===================== Similarity Calculation =====================
float calculateSimilarity(char doc1[], char doc2[]);
int countCommonWords(char words1[][50], int count1, char words2[][50], int count2);
// ===================== Common Words / Phrases =====================
void detectCommonWords(char doc1[], char doc2[]);
void detectCommonPhrases(char doc1[], char doc2[]);
int splitWords(char text[], char words[][50]);
int compareWords(const void *a, const void *b);
int buildPhrases(char words[][50], int count, char phrases[][160]);
// ===================== AI Bridge =====================
float getAISimilarity();
#endif