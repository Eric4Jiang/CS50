#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string encipher(string text, string key){
    int keyP = 0;
    int keyLength = strlen(key);
    for(int letter = 0, size = strlen(text); letter < size; letter++){
        if(isalpha(text[letter])){
            int keyNewP = keyP % keyLength;
            if(isupper(text[letter])){
                if(isupper(key[keyP % keyLength]))
                    text[letter] = (text[letter] - 65 + key[keyNewP] - 65) % 26 + 65; 
                else if(islower(key[keyP % keyLength]))
                    text[letter] = (text[letter] - 65 + key[keyNewP] - 97) % 26 + 65; 
            }
            else if(islower(text[letter])){
                if(isupper(key[keyP % keyLength]))
                    text[letter] = (text[letter] - 97 + key[keyNewP] - 65) % 26 + 97; 
                else if(islower(key[keyP % keyLength]))
                    text[letter] = (text[letter] - 97 + key[keyNewP] - 97) % 26 + 97; 
            }
        keyP++;
        }
    }
    return text;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Not a valid input.");
        return 1;
    }
    for(int i = 0; i < strlen(argv[1]); i++){
        if(!isalpha(argv[1][i])){
            printf("Not a valid Input");
            return 1;
        }
    }
    
    string key = argv[1];
    string plainText;
    
    plainText = GetString();    
    
    string cipherText = encipher(plainText, key);
    printf("%s\n", cipherText);
    
    return 0;
}