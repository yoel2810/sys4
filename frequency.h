#define NUM_LETTERS ((int)26)

typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    } node;

node* newNode(char c, int count);
int isLetter (char c);
int endOfLetters (char* data);
void freeTree(node* root);
void insert(char* data, node** root);
void printWord(char* start, int count, int p);
void print1(node* root, char* wordsArray, int p);
void print2(node* root, char* wordsArray, int p);
