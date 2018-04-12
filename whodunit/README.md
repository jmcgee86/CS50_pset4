# Questions

## What's `stdint.h`?

A header file that providies a set of typedefs

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Helps keep track of how much memory each data type will use.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 1
DWORD: 4
WORD:2
LONG: 4

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

 ASCII: BM
 Hex: 0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

bfSize is size in bytes of the bitmap file, biSize is the number of bytes required by the structure.


## What does it mean if `biHeight` is negative?

Its origin is the upper left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file does not exist or cannot be found.

## Why is the third argument to `fread` always `1` in our code?

That is the number of elements we want read

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

sets the file position to the offset that is passed in.

## What is `SEEK_CUR`?

returns current position of the file pointer.
