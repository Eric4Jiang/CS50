/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    int factor = atoi(argv[1]); // stores sclae factor as an int
    
    if (factor < 1 || factor > 100)
    {
        printf("Incorrect use: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    } 

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // construct bitmap headers for the outfile
		BITMAPFILEHEADER out_bf;
		BITMAPINFOHEADER out_bi;	
		out_bf = bf;
		out_bi = bi;
		out_bi.biWidth = bi.biWidth * factor;
		out_bi.biHeight = bi.biHeight * factor;
    
    // update infile's BITMAPINFOHEAD information
    //scale height and width by factor
    out_bi.biHeight = bi.biHeight * factor;
    out_bi.biWidth = bi.biWidth * factor;
    // determine padding for new scanlines
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding  = (4-(out_bi.biWidth * sizeof(RGBTRIPLE) % 4) % 4) % 4;
    
    
    //new file size
    out_bf.bfSize = 54 + 3 * abs(out_bi.biHeight) * out_bi.biWidth + abs(out_bi.biHeight) * out_padding; //metadata + (3 bytes per pixel * amount of pixels)
    //new image size
    out_bi.biSizeImage = ((((out_bi.biWidth * out_bi.biBitCount) + 31) & ~31) / 8) * abs(out_bi.biHeight);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //loops each line for vertical expansion
        for(int k = 0; k < factor; k++) {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            	for(int m = 0; m < factor; m++) {
                	// write scaled RGB triple to outfile
                	fwrite(&triple, sizeof(RGBTRIPLE), 1 , outptr);
            	}	
			}	
			
            // skip over padding, if any
            fseek(inptr, in_padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int l = 0; l < out_padding; l++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, -(bi.biWidth * 3 + in_padding ), SEEK_CUR); // move back to the front of the line instead of going to next
        }
        fseek(inptr, bi.biWidth*3+in_padding, SEEK_CUR); // move to next line 
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
