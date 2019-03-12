/*
 * Copyright (C) 2014 The YunOS Project. All rights reserved.
 */

/*HEADER
 *========================================================================*/
#include <stdio.h>
#include <stdlib.h>

#include "byteswap.h"

/*MACRO
 *========================================================================*/

/*TYPE
 *========================================================================*/

/*VARIABLES
 *========================================================================*/

/*FUNCTIONS
 *========================================================================*/
/*
 * hex2bin
 * turn hex string to binary form
 * @dst[out]  output binary stream
 * @str[in]   input hex string
 * @count[in] output string length
 * @return    the same with dst[out]
 */
char*  hex2bin(char *dst, const char *str, int count)
{
    unsigned char val;
    unsigned char c;

    while (*str && count) {
        c = *str++;
        if (isdigit(c)) {
            val = c - '0';
        }
        else if ((c|0x20) >= 'a' && (c|0x20) <= 'f') {
            val = (c|0x20) - ('a' - 10);
        }
        else {
            return NULL;
        }

        val <<= 4;
        c = *str;

        if (isdigit(c)) {
            val |= c - '0';
        }
        else if ((c|0x20) >= 'a' && (c|0x20) <= 'f') {
            val |= (c|0x20) - ('a' - 10);
        }
        else if (c == ':' || c == '\0') {
            val >>= 4;
        }
        else {
            return NULL;
        }

        *dst++ = val;
        if (c != '\0') {
            str++;
        }
        if (*str == ':') {
            str++;
        }
        count--;
    }

    return dst;
}

/*
 * main
 * the main function that transform a file in hex string
 * format into binary form
 * @arg[1][in]  input file name
 * @arg[2][in]  output file name
 * @return      succeed or error number
 */
int main(int argc, char *argv[])
{
    char *in_buf, *out_buf;
    FILE *input = fopen(argv[1],"r+"); 
    FILE *output = fopen(argv[2],"w+"); 
    int file_length; 

    fseek(input, 0 , SEEK_END);
    file_length = ftell(input);
    fseek(input, 0 , SEEK_SET);
    in_buf = malloc(file_length); 
    out_buf = malloc(file_length/2); 
    fread(in_buf, file_length, 1, input);
    hex2bin(out_buf, in_buf, file_length/2);
    fwrite(out_buf, file_length/2, 1, output);
    fclose(output);
    
    return 0;
}

