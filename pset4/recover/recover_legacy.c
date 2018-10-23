// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jpeg.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // recover code here

    BLOCK block;

    int count = 0;

    int read = fread(&block, sizeof(BLOCK), 1, inptr);

    if (read)
    {

        do
        {

            read = fread(&block, sizeof(BLOCK), 1, inptr);

        }
        while (read && (block[0] != 0xff && block[1] != 0xd8 && block[2] != 0xff && (block[3] & 0xf0) != 0xe0));

        fprintf(stderr, "jpg found!\n");

        while(read)
        {
            while (read && (block[0] != 0xff) && (block[1] != 0xd8) && (block[2] != 0xff) && ((block[3] & 0xf0) != 0xe0))
            {
                read = fread(&block, sizeof(BLOCK), 1, inptr);
            }

            // create file name
            char filename[7];
            sprintf(filename, "%03d.jpg", count++);

            fprintf(stderr, "writing into %s\n", filename);

            // create new file for jpg
            FILE *outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

            // write the whole block to new file
            // while no new file found, keep writing
            do
            {

                for (int i = 0; i < sizeof(BLOCK); i++)
                {

                    fwrite(&block[i], sizeof(BYTE), 1, outptr);

                }

                read = fread(&block, sizeof(BLOCK), 1, inptr);

                if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xf0) == 0xe0))
                {
                    break;
                }

            }
            while (read && ((block[0] != 0xff) && (block[1] != 0xd8) && (block[2] != 0xff) && ((block[3] & 0xf0) != 0xe0)));

            fclose(outptr);

            fprintf(stderr, "image %s is written\n", filename);

        }

    }

    fprintf(stderr, "reach the END OF FILE\n");

    // close infile
    fclose(inptr);

    // success
    return 0;
}
