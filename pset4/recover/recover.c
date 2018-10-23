// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t  BYTE;
typedef BYTE BLOCK[512];

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
        return 1;
    }

    // recover code here

    BLOCK block;

    for (int i = 0; i < sizeof(BLOCK); i++)
    {
        block[i] = -1;
    }

    int count = 0;
    bool jpgFound = false;

    int read = fread(&block, 1, sizeof(BLOCK), inptr);

    // create file name
    FILE *outptr = (FILE *) malloc(sizeof(FILE));
    char filename[7];

    while(read == 512)
    {

        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && (((block[3] & 0xf0) == 0xe0) || ((block[3] & 0xff) == 0xe0)))
        {
            if (!jpgFound)
            {
                jpgFound = true;
            }
            else
            {
                if (outptr != NULL)
                {
                    fclose(outptr);
                }

            }

            // create file name
            sprintf(filename, "%03d.jpg", count++);

            fprintf(stderr, "writing into %s\n", filename);

            // create new file for jpg
            FILE *file = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

            outptr = file;

            for (int i = 0; i < sizeof(BLOCK); i++)
            {

                fwrite(&block[i], sizeof(BYTE), 1, outptr);

                fprintf(stderr, "%x ", block[i]);

            }

        }
        else if (jpgFound)
        {
            for (int i = 0; i < sizeof(BLOCK); i++)
            {

                fwrite(&block[i], sizeof(BYTE), 1, outptr);

                fprintf(stderr, "%x ", block[i]);

            }

            fprintf(stderr, "\n");


        }

        read = fread(&block, 1, sizeof(BLOCK), inptr);

    }

    // fprintf(stderr, "size of FILE = %lu\n", sizeof(FILE));

    fprintf(stderr, "reach the END OF FILE\n");

    if (count == 0)
    {
        fprintf(stderr, "Could not find forensic image in %s.\n", infile);
        return 2;
    }

    // close infile
    fclose(inptr);
    free(outptr);

    // success
    return 0;
}
