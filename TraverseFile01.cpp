/*******************************************************************************
*							±éÀúÎÄ¼þ¼Ð		                                   *
********************************************************************************
*		Designer : taxus					Origian Place : BJ of China		   *
*		Create Data : 04/03/2014			Now Version : 1.0				   *
*==============================================================================*
*						    Modification History							   *
*==============================================================================*
*		V1.0	1. Create the report program.    							   *
*******************************************************************************/
#include "io.h"
#include "stdio.h"

char * targetPath = "F:\\BaiduYunDownload\\*.*";
int main()
{
	long handle;
	struct _finddata_t find;

	handle = _findfirst(targetPath, &find);

	if(handle == -1)
		return -1;

	printf("%s\n", find.name);

	while (!_findnext(handle, &find))
	{
		printf("%s\n", find.name);
	}

	_findclose(handle);
	
	getchar();

	return 0;
}