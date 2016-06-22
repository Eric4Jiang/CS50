#include <cs50.h>
#include <stdio.h>

void buildPyramid(int height){
    for(int line = 1; line <= height; line++){ // loops until you reach the height of pyramid
        for(int spaces = 0; spaces < height-line; spaces++){ //makes space before pyramid
            printf(" ");
        }
        for(int hashes = 0; hashes < line + 1; hashes++){
            printf("#");
        }
        printf("\n");
    }
}

bool validateInput(int input){
    if(input >= 0 && input <= 23) return true;
    else return false;
}

int main(void){
    int height;
    do{
        printf("What is the height of the pyramid?\n");
        height = GetInt();

    }while(validateInput(height) == false); // repeats until there is valid input

    buildPyramid(height);
    return 0;
}
