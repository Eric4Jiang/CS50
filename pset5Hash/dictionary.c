/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct node {
    char word[LENGTH + 1];
    struct node* next; 
}node;

node* hashtable[HASH_LENGTH];
node* positions[HASH_LENGTH];
int numberOfWords;

//uses first letter to indicate indexes: a = 0, b = 1
int hashFunction(char letter) {
    int index = tolower(letter) - 'a';
    return index;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int index = hashFunction(word[0]);
    node* curr = hashtable[index];
    char LCword[LENGTH + 1];
    strcpy(LCword, word);
    
    for(int i = 0; i < strlen(LCword); i++) {
        LCword[i] = (char) tolower(LCword[i]);
    }
    // //loops through hashtable until until it finds words
    while(curr != NULL) {
        if(strcmp(LCword, curr->word) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

node* addNodeToList(char *word) {
    node* n = malloc(sizeof(node));
    strcpy(n->word, word);
    return n;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //open file
    FILE* file = fopen(dictionary, "r");
    assert(file!= NULL);

    //initialize hashtable
    for(int i = 0; i < HASH_LENGTH; i++) {
        hashtable[i] = NULL;
    }

    char storage[LENGTH];
    numberOfWords = 0;

    //loop through every line
    while(fscanf(file, "%s", storage) == 1) {
        int index = hashFunction(storage[0]);

        //if linked list is empty
        if(hashtable[index] == NULL) {
            hashtable[index] = addNodeToList(storage);
            positions[index] = hashtable[index];
        }
        //Make new new from current position
        else {
            positions[index]->next = addNodeToList(storage);
            positions[index] = positions[index]->next;
        }
        numberOfWords++;
    }
    fclose(file);
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return numberOfWords;
}

void freeNodes(node* n) {
    node* temp;
    while(n != NULL) {
        temp = n;
        n = n->next;
        free(temp);
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < HASH_LENGTH; i++) {
        freeNodes(hashtable[i]);
    }
    return true;
}
