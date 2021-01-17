#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frequency.h"

//#define NUM_LETTERS ((int)26)
//#define NULL 0

typedef enum {FALSE=0, TRUE=1} boolean;

/*typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    } node;*/

node* newNode(char c, int count)
{
    node* p = (node*) malloc(sizeof(node));
    if (p == NULL)
    {
        printf("Failed to allocate memory space. Terminating program...");
        return NULL;
    }
    p->letter = c;
    p->count = count;
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        p->children[i] = NULL;
    }
    return p;
}

int isLetter (char c)
{
    return (((c - 'a' >= 0) && ((c - 'a') <= ('z' - 'a'))) || ((c - 'A' >= 0) && ((c - 'A') <= ('Z' - 'A'))));
}

int endOfLetters (char* data)
{
    int i = 1;
    if (*(data + i) == '\0')
    {
        return TRUE;
    }
    
    while (*(data + i) != '\0')
    {
        if (isLetter(*(data +  i)))
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

void freeTree(node* root)
{
    if (root==NULL)
    {
        return;
    }
    
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (root->children[i] != NULL)
        {
            freeTree(root->children[i]);
        }
    }
    free(root);
    
}

void insert(char* data, node** root)
{
    node** p = root;
    int i = 0;
    while(*p != NULL && *(data + i) != '\0')
    {
        if (isLetter(*(data + i)))
        {
            *(data + i) = tolower(*(data + i));
            if (((*p)->children[*(data + i) - 'a']) == NULL)
            {
                int count = 0;
                p = &((*p)->children[*(data + i) - 'a']);
                if (endOfLetters(data + i))
                {
                    count = 1;
                }
                *p = newNode(*(data + i), count);
            }
            else
            {
                if (endOfLetters(data + i))
                {
                    (*((*p)->children[*(data + i) - 'a'])).count++;
                }
                p = &((*p)->children[*(data + i) - 'a']);
            }
        }
        i++;
    }
}

void printWord(char* start, int count, int p)
{
    for (int i = 0; i < p; i++)
    {
        printf("%c", *(start + i));
    }
    printf(" %d", count);
    printf("%c", '\n');
}

void print1(node* root, char* wordsArray, int p)
{
    if (root == NULL)
    {
        return;
    }
    //printf("%d\n", p);
    
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (root->letter == '\0')
        {
            print1(root->children[i], wordsArray, 0);
        }
        else
        {
            *(wordsArray + p) = root->letter;
            print1(root->children[i], wordsArray, p + 1);
        }
    }

    if (root->count > 0)
    {
        printWord(wordsArray, root->count, p+1);
    }
}

void print2(node* root, char* wordsArray, int p)
{
    if (root == NULL)
    {
        return;
    }
    //printf("%c\n", root->letter);
    
    for (int i = NUM_LETTERS - 1; i >= 0; i--)
    {
        if (root->letter == '\0')
        {
            print2(root->children[i], wordsArray, 0);
        }
        else
        {
            *(wordsArray + p) = root->letter;
            print2(root->children[i], wordsArray, p + 1);
        }
    }

    if (root->count > 0)
    {
        printWord(wordsArray, root->count, p+1);
    }
}

int main(int argc, char* argv[])
{
    // check malloc null
    node* root = newNode('\0', 0);
    char *cptr = NULL;
    char c;
    cptr = (char *) malloc(sizeof(char));
    int wordsLen = 0; //how many letters
    if (cptr == NULL)
    {
        printf("Failed to allocate memory space. Terminating program...");
        return -1;
    }

    int wordLen = 0;
    for (int x = scanf("%c", &c); x != -1; x = scanf("%c", &c))
    {
        if (c == ' ' || c == '\n')
        {
            *(cptr + wordLen) = '\0';
            insert(cptr, &root);
            free(cptr);
            cptr = (char *) malloc(sizeof(char));
            wordsLen += wordLen + 1;
            wordLen = 0;
        }
        else
        {
            wordLen++;
            cptr = realloc(cptr, (wordLen + 1) * sizeof(char));
            if (cptr == NULL)
            {
                printf("Failed to allocate memory space. Terminating program...");
                return -1;
            }
            *(cptr + wordLen - 1) = c;
        }
    }
    *(cptr + wordLen) = '\0';
    insert(cptr, &root);
    free(cptr);
    wordsLen += wordLen + 1;
    wordLen = 0;
    //printf("sdfdsf: %d\n", wordsLen);
    char* wordsArr = calloc(wordsLen, sizeof(char));
    if (argc == 1)
    {
        print1(root, wordsArr, 0);
    }
    else if (argc == 2)
    {
        if (*argv[1] == 'r')
        {
            print2(root, wordsArr, 0);
        }   
    }
    free(wordsArr);
    freeTree(root);
}