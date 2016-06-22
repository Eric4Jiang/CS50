#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

bool load(const char* dictionary)
{
    //open dictionary to read from
    FILE* dictionary = fopen(dictionary, "r");
    
    //base for a trie
    node* root;
    node* curr;
    node* next;
    
    char* storage[1];
    int maxChars = 45, i = 0;
    bool isLoaded = false;
    
    //loops through all lines in the dictionary
    while(fscanf(dictionary, "%s", storage)) {
        isLoaded = true;
        //reset back to main node every new word
        curr = root;
        //loop through every characters until end of string
        while(storage[i] != '\0') {
            next = curr->alphabet[tolower(storage[i] - 'a')];
            //if letter does not exist in the trie yet
            else if(next == NULL) {
                //make a new node if one does not currently exist
                struct node *n;
                n = malloc(sizeof(node));
                for(int j = 0; j < 26; j++) {
                    n -> alphabet[j] = NULL;
                }
                //sets pointer to new node for every letter
                curr->alphabet[towlower(storage[i] - 'a')] = &n;
                //set current node to the new one
                curr = n;
            } else { //else just move into the already existing node
                curr = curr->alphabet[tolower(storage[i] - 'a')];    
            }
            i++;
        }
        //after every word set it to true
        curr->is_word = true;
    }
    
    return isLoaded;
}

int main(int argc, char* argv[])
{
    // check for correct number of args
    if (argc != 2)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }
    char* dictionary = argv[1];
    bool loaded = load(dictionary);
}