/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    //open card file
    FILE* file = fopen("card.raw", "r");
    
    //number per block you're reading
    int n = 512;
    
    //make buffer
    char buffer[n];
    
    //title of the jpeg
    char title[1] = {};
    
    //image object that we will use to open all 50 images
    FILE* image;
    
    //used to name the pictures from 1 - 50
    int numberOfJPEGS = -1;
    
    //read until end of file
    while (fread(&buffer, sizeof(char) * n, 1, file) == 1) {
        //find a jpeg (always start with 0xff 0xd8 0xff (0xe0 or 0xe1)) and instantiate a new jpg file for each
        if(buffer[0] == (char)0xff && buffer[1] == (char)0xd8 && buffer[2] == (char)0xff && (buffer[3] == (char)0xe0 || buffer[3] == (char)0xe1)) {
            numberOfJPEGS++;
            
            //will close the already opened file
            if(numberOfJPEGS > 0) {
                fclose(image);
            }
            
            //open new jpeg file with the correct name -> ###.jpg
            title[0] = numberOfJPEGS + 48; // to change from int 1 to char 1
            
            //formatting the name of the file
            if(numberOfJPEGS < 10) {
                sprintf(title, "00%i.jpg", numberOfJPEGS);
                image = fopen(title, "a");
            } else if(numberOfJPEGS >= 10 && numberOfJPEGS < 100) {
                sprintf(title, "0%i.jpg", numberOfJPEGS);
                image = fopen(title, "a");
            }
        }
        
        //once a jpeg is initialized, fwrite into it
        if(numberOfJPEGS > -1) {
            fwrite(&buffer, sizeof(char), n, image);
        }
    }
}
