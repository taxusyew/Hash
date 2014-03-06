/*******************************************************************************
*							遍历文件夹		                                   *
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
#include "Windows.h"

char * targetPath = "F:\\BaiduYunDownload\\";
int indentNum = 4;  // 缩进空格数

void Traverse(char * filepath, int level)
{
	//char * curPath;
	char curPath[0x1000];
	struct _finddata_t find;
	long handle;
	int nReturn = 0;

	level++;
	int indent = level * indentNum;

	strcpy(curPath, filepath);
	strcat(curPath, "*.*");

	handle = _findfirst(curPath, &find);

	// 循环遍历同层目录
	while (handle != -1 && nReturn != -1)
	{
		indent = level * indentNum;			// 恢复缩进

		// 过滤 . 和 ..
		if (strcmp(find.name, ".") == 0 || strcmp(find.name, "..") == 0)
		{
			nReturn = _findnext(handle, &find);
			continue;
		}

		// 找到的是文件夹
		if(find.attrib & _A_SUBDIR)
		{

			// 恢复文件路径
			strcpy(curPath, filepath);
			strcat(curPath, find.name);
			strcat(curPath, "\\");
			printf("%s\n", find.name);
			// 递归调用
			Traverse(curPath, level);
		}
		else
		{
			// 输出文件缩进
			while(indent > 0)
			{
				printf(" ");
				indent--;
			}
			strcpy(curPath, filepath);
			strcat(curPath, find.name);

			printf("%s\n", find.name);
		} 

		// 该层文件结束
		nReturn = _findnext(handle, &find);
	}

	_findclose(handle);
}
int main()
{
	Traverse(targetPath, -1);
	getchar();

	return 0;
}
