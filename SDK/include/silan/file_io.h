#ifndef __FILE_IO_DEF__
#define __FILE_IO_DEF__


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define FILE int

typedef struct 
{
	int (*fopen)(char *name, char * mode);
	int (*fread)(int handle, char * buf,  unsigned int len);
	int (*fseek)(int handle, int offset, int whence);
	int (*fwrite)(int fhandle, char * buf, unsigned int len);
	unsigned int (*fsize)(int handle);
	unsigned int (*ftell)(int handle);
	int (*fclose)(int fhandle);
	int (*feof)(int fhandle);
} FILE_IO;


#endif
