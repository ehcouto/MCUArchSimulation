#include <stdio.h>
#include <stdlib.h>
#include "SFloader.h"
#define SF_SIZE 65536


unsigned long int SF_size;
char *SF_ptr;;



unsigned char SFloader__Initialize(char *FileName)
{

// code from this example https://www.codingunit.com/writing-memory-to-a-file-and-reading-memory-from-a-file-in-c
    FILE *ptr_fp;
	int ret_v;
	unsigned char tmp = 0;

    SF_size = SF_SIZE;
    SF_ptr = (char *)malloc(SF_SIZE * sizeof(char));
    if((ptr_fp = fopen(FileName, "rb"))!=NULL)
    {
		ret_v = fread(SF_ptr, SF_SIZE * sizeof(char), 1, ptr_fp);
        fclose(ptr_fp);
        tmp = 1;
    }
    return(tmp);
}
