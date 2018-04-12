#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc !=2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }

    //get filename
    char *infile = argv[1];

    //open memory card file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    typedef uint8_t  BYTE;
    BYTE buffer[512];
    int jpg_num = 000;
    char current_img[8];
    current_img[7] = '\0';
    FILE *img = NULL;
    int found = 0;

    while (fread(buffer, 1, 512, inptr)==512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!found)
            {
                sprintf(current_img, "%03i.jpg", jpg_num);
                jpg_num++;
                img = fopen(current_img, "w");
                fwrite(buffer, 1, 512, img);
                found = 1;
            }
            else
            {
                fclose(img);
                sprintf(current_img, "%03i.jpg", jpg_num);
                jpg_num++;
                img = fopen(current_img, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        else
        {
            if (found)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }


//close input file
   fclose(inptr);

    // close outfile
    fclose(img);

//done
    return 0;

}