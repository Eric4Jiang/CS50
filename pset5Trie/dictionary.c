/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node* alphabet[ALPHA_LENGTH];
}
node;

//GLOBALS
node* root;
int numberOfWords = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* curr;
    curr = root;
    int index;
    
    for(int i = 0; i < strlen(word); i++) {
        index = (word[i] == '\'') ?  APOSTROPHE : (tolower(word[i]) - 'a');
        
        //if it points to NULL it means the word doesn't exist in the dictionary
        if (curr->alphabet[index] == NULL) return false;
        
        //else move to next letter
        else curr = curr->alphabet[index];
    }
    return curr->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary) {
    //open file
    FILE* file = fopen(dictionary, "r");
    assert(file != NULL);

    //storage for words
    char storage[LENGTH+1];

    //node intialization
    root = malloc(sizeof(node));
    root->is_word = false;
    //make sure to set everything to fales at first
    for(int j = 0; j < ALPHA_LENGTH; j++) {
        root->alphabet[j] = NULL;
    }

    node* curr;
    int index; // represents index of the letter in the node

    //loops through all lines in the dictionary
    while(fscanf(file, "%s", storage) == 1) {
        //restart back at the root node
        curr = root;
        //for every letter in a word
        for(int i = 0; i < strlen(storage); i++) {
            //calculates the index using a letter, APOSTROPHE CASE included
            index = (storage[i] == '\'') ? APOSTROPHE: tolower(storage[i]) - 'a';
            
            //if no letter currently exist in current node, make new one and move into it
            if(curr->alphabet[index] == NULL) {
                node* n = malloc(sizeof(node));
                n->is_word = false;
                for(int k = 0; k < ALPHA_LENGTH; k++) {
                    n->alphabet[k] = NULL;
                }
                //points the letter to the new node
                curr->alphabet[index] = n;
                //set the curr node as the new one
                curr = n;
            }
            else { //else just move into existing node
                curr = curr->alphabet[index];
            }
        }
        curr->is_word = true;
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

//frees a node and all other nodes in it recursively
void freeNode(node* n) {
    for(int i = 0; i < ALPHA_LENGTH; i++) {
        if(n->alphabet[i] != NULL) freeNode(n->alphabet[i]);
    }
    free(n);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freeNode(root);
    return true;
}

