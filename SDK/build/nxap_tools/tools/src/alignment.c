/*
 * Copyright (C) 2014 The YunOS Project. All rights reserved.
 */

/*HEADER
 *========================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manifest.h"

/*MACRO
 *========================================================================*/

/*TYPE
 *========================================================================*/

/*VARIABLES 
 *========================================================================*/

/*FUNCTIONS
 *========================================================================*/
/*
 * main
 * insert encrypted key into bootload
 * @arg[1][in]  bootload file
 * @arg[2][in]  key offset
 * @arg[3][in]  key file
 * @return      succeed or error number
 */
int main(int argc, char *argv[])
{
    int i, size, align;
    FILE *fp;

    fp = fopen(argv[1], "rb+");
    fseek(fp, 0 , SEEK_END);
    size = ftell(fp);
    align = 128 - (size % 128);
    fwrite("\0", 1, align, fp);

    return 0;
}

