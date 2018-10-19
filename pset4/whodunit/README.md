# Questions

## What's `stdint.h`?

stdint.h let us define typedef data structure of integer with desired minimum and maximum width

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

to allocate memory by the size, width specified with typedefs above

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of BITMAPFILEHEADER which is 12 bytes; biSize is the size of BITMAPINFOHEADER which is 40 bytes

## What does it mean if `biHeight` is negative?

if biHeight is negative, the bitmap pixel starts from top-left corner of display space

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

BITMAPINFOHEADER.biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

when the program cannot open or create the file the file successfully

## Why is the third argument to `fread` always `1` in our code?

to specify how many byte for fread to move after completing the function

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

for moving cursor of file streaming (fread or fwrite) to the position relative to beginning, current, last position of the file

## What is `SEEK_CUR`?

parameter for fseek to move cursor of file streaming to specidied positions given in second parameter from to the current position

## Whodunit?

It was Professor Plum with the candlestick in the library
