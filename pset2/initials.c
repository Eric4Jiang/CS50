#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void printInitials(string name){
    printf("%c", toupper(name[0]));
    for(int letter = 0; letter < strlen(name); letter++){
        if(strncmp(&name[letter], " ", 1) == 0){
            name[letter + 1] = toupper(name[letter + 1]);
            printf("%c", name[letter + 1]);
        }
    }
    printf("\n");
}

int main(void){
    string name;
    name = GetString();
    
    printInitials(name);
    return 0;
}