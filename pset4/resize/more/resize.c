// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // get factor for resize
    float f = atof(argv[1]);

    // fprintf(stderr, "f as string: %s;\n", argv[1]);
    // fprintf(stderr, "f as float: %f;\n", f);

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

    // testing struct copying
    // fprintf(stderr, "bi.biWidth = %x;\n", bi.biWidth);
    // fprintf(stderr, "newBi.biWidth = %x;\n", inBi.biWidth);
    // inBi.biWidth *= 2;
    // fprintf(stderr, "bi.biWidth = %x;\n", bi.biWidth);
    // fprintf(stderr, "newBi.biWidth = %x;\n", inBi.biWidth);
    // return 0;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // remember input bf and bi before modifying bf and bi for output
    BITMAPFILEHEADER inBf = bf;
    BITMAPINFOHEADER inBi = bi;

    // determine padding for scanlines
    int inPadding = (4 - (inBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // fprintf(stderr, "bi.biWidth *= f => %i * %f = %f\n", bi.biWidth, f, bi.biWidth * f);

    // fprintf(stderr, "bi.biHeight *= f => %i * %f = %f\n", bi.biHeight, f, bi.biHeight * f);

    // modify BITMAPINFOHEADER
    bi.biWidth *= f;
    bi.biHeight *= f;

    // determine new padding with new biWidth and biHeight
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate new biSizeImage
    // need to do after calculating the padding
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);

    // modify BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE triples[abs(inBi.biHeight)][inBi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inBi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0, biWidth = inBi.biWidth; j < biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            triples[i][j] = triple;


            // fprintf(stderr, "triples[%i][%i] = %x%x%x;\t", i, j, triples[i][j].rgbtRed, triples[i][j].rgbtGreen, triples[i][j].rgbtBlue);

        }

        // fprintf(stderr, "\n");

        // skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);

    }

    fprintf(stderr, "\n");

    // resize the array to the size of output file
    // find avarage value of pixels combined by 1/f x 1/f for 1 pixel in input file
    // iterate over infile's scanlines, skip over every 1/f pixel vertically
    if (f >= 1)
    {

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(inBi.biHeight); i < biHeight; i++)
        {
            for (int l = 0; l < f; l++) {

                // iterate over pixels in scanline
                for (int j = 0; j < inBi.biWidth; j++)
                {

                    RGBTRIPLE triple = triples[i][j];

                    // write pixel triple repeatedly f times
                    for (int m = 0; m < f; m++)
                    {

                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                        // fprintf(stderr, "%x%x%x\t", triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);

                    }

                }

                // write padding to output file
                for (int k = 0; k < padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }

        }

    }
    else
    {
        // when f < 1
        // instead of iterating over the infile scanlines, we iterate over the array

        // fprintf(stderr, "sizeof(triples) = %lu = %f byte\n", sizeof(triples), (sizeof(triples) / sizeof(RGBTRIPLE)) * f);
        // fprintf(stderr, "sizeof(triples[i]) = %lu = %f byte\n", sizeof(triples[0]), (sizeof(triples[0]) / sizeof(RGBTRIPLE)) * f);

        int width = (sizeof(triples[0]) / sizeof(RGBTRIPLE)) * f;
        int height = sizeof(triples) / sizeof(triples[0]) *f;

        // fprintf(stderr, "width = %i;\nheight = %i;\n", width, height);

        for(int i = 0; i < height; i++)
        {

            for (int j = 0; j < width; j++)
            {
                int x = (int) (j * (1 / f));
                int y = (int) (i * (1 / f));

                RGBTRIPLE triple = triples[y][x];

                // fprintf(stderr, "triples[%i][%i] = %x%x%x\t\t", y, x, triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // padding must be added during writing phase
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            // fprintf(stderr, "\n");

        }

    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
