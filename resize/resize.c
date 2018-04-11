// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

//check if resize_scale is valid (must be between 1 and 100)
int resize_scale = atoi(argv[1]);

if (resize_scale < 1 || resize_scale > 100)
{
    fprintf(stderr, "Resize Scale must be between 1 and 100\n");
    return 1;
}

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int width_input = bi.biWidth;
    int new_padding;
    bi.biWidth *= resize_scale;
    bi.biHeight *= resize_scale;
    new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) *bi.biWidth) + new_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines while i is less than the height of the output file height
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        if(i % resize_scale) //if i is not divisible by resize scale, move cursor back to beginning of infile scanline to read/write line again
        {
            fseek(inptr, -(width_input * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
        }

        for (int j = 0; j < width_input; j++)

        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile, repeated once up to resize_scale
                for (int pixel = 0; pixel < resize_scale; pixel++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
        }

 //       skip over padding from infile, if any
        fseek(inptr, padding, SEEK_CUR);

        // add any necessary padding to output file
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
