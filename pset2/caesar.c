#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string encipher(string text, int key){
    
    for(int letter = 0, size = strlen(text); letter < size; letter++){
        if(isalpha(text[letter])){
            if(isupper(text[letter]))
                text[letter] = (text[letter] - 65 + key) % 26 + 65;//-65 --> alphabetical scale; +65 --> ASCII value
            else if(islower(text[letter]))
                text[letter] = (text[letter] - 97 + key) % 26 + 97;
        }
    }
    return text;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Not a valid input.");
        return 1;
    }
    
    int key = atoi(argv[1]); //converts value user enters to integer
    string plainText;
    
//    printf("Enter text: ");
    plainText = GetString();    
    
    string cipherText = encipher(plainText, key);
    printf("%s\n", cipherText);
    
    return 0;
}