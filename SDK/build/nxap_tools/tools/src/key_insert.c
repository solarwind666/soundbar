/*
 * Copyright (C) 2014 The YunOS Project. All rights reserved.
 */

/*HEADER
 *========================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    FILE *boot_in= fopen(argv[1],"r+"); 
    FILE *key_in= fopen(argv[3],"r+"); 
    FILE *output= fopen("bootload.tmp","w+"); 
    int  boot_len;
    char *ptr1, *ptr2, *ptr3;

    fseek(boot_in, 0 , SEEK_END);
    boot_len = ftell(boot_in);
    fseek(boot_in, 0 , SEEK_SET);
    ptr1 = malloc(boot_len);
    ptr3 = malloc(100);
    ptr2 = ptr1;
    fread(ptr1, boot_len, 1, boot_in);
    fread(ptr3, 24, 1, key_in);
    ptr2 += strtol(argv[2], NULL, 10);
    memcpy(ptr2, ptr3, 24);
    fwrite(ptr1, boot_len, 1, output);
    fclose(output);

    return 0;
}

