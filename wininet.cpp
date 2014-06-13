#include "stdio.h"
#include "TCHAR.h"

#include <windows.h>
#include "Wininet.h"
#include "json/json.h"
#pragma comment( lib, "Wininet.lib" )
#pragma comment(lib, "json.lib")

// IP
static TCHAR IP[] = _T("192.168.0.101");
// 接口文件
static TCHAR GetResult[] = _T("testsocket.php");
// FILE

// 连接参数
static TCHAR hdrs[] = _T("Content-Type:application/x-www-form-urlencoded");				//Content-Type: multipart/form-data;
static TCHAR frmdata[] = _T("filename=1b1733d743295385");
static LPCSTR Accept[2] = {_T("*/*"), NULL};


void ConnectSlot();
void ConnectUpload();
int buf2int(char * buf, int len);

using namespace std;
void main()
{
	// 调用上传接口
	// 取得返回结果，显示到控制台
	
	ConnectUpload();
	//ConnectSlot();

}

// 网络连接
void ConnectUpload()
{
	DWORD dwNumberOfBytesWritten=0;

	// 开始连接
	HINTERNET hSession = InternetOpen("MyAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnect(hSession, IP, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", "testupload.php", NULL, NULL, Accept, 0, 1);

	DWORD dwBytesSend=0;

	// 读取文件到本地缓冲区
	HANDLE hFile;
	hFile=CreateFile("C:\\file_filter.txt",
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);
	
	DWORD dwFileSize = GetFileSize(hFile, 0);
	
	DWORD dwFlag;

	LPCTSTR boundary=TEXT("-----------------------------67491722032265");
	TCHAR content_type[128];
    _stprintf_s(content_type,TEXT("Content-Type: multipart/form-data; boundary=%s"),boundary);
    LPTSTR referer=TEXT("Referer: http://127.0.0.1/upload/~upload");
    LPTSTR accept=TEXT("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    LPTSTR accept_lan=TEXT("Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3");
    LPTSTR accept_encoding=TEXT("Accept-Encoding: gzip, deflate");
    LPTSTR user_agent=TEXT("User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:22.0) Gecko/20100101 Firefox/22.0");

	HttpAddRequestHeaders(hRequest,content_type,-1,HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	HttpAddRequestHeaders(hRequest,referer,-1,HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	HttpAddRequestHeaders(hRequest,accept,-1,HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	HttpAddRequestHeaders(hRequest,accept_lan,-1,HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
	HttpAddRequestHeaders(hRequest,accept_encoding,-1,HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);

	BYTE* lpBuffer=(BYTE*)VirtualAlloc(0,dwFileSize,MEM_COMMIT,PAGE_READWRITE);
	DWORD dwRead;
	ReadFile(hFile,lpBuffer,dwFileSize,&dwRead,0);

	// 处理文件上传缓冲区
	INTERNET_BUFFERS bufferin;
	
	char first_boundary[128];
	char end_boundary[128];

	LPCSTR aboundary="-----------------------------67491722032265"; //ansi
	sprintf_s(first_boundary, "--%s\r\n", aboundary);
	sprintf_s(end_boundary, "\r\n--%s--\r\n", aboundary);

	LPSTR content_dispos = "Content-Disposition: form-data; name=\"myfile\"; filename=\"1-130R5225921517.png\" \r\n";

	//LPSTR content_dispos = "Content-Disposition: form-data; name=\"myfile\"; filename=\"test.txt\"\r\n";
	LPSTR content_type2 = "Content-Type: application/octet-stream\r\n\r\n";
	
	bufferin.dwStructSize = sizeof(INTERNET_BUFFERS);
	bufferin.Next = NULL;
	bufferin.lpcszHeader = NULL;
	bufferin.dwHeadersLength = 0;
	bufferin.dwHeadersTotal = 0;
	bufferin.lpvBuffer = NULL;
	bufferin.dwBufferTotal = dwFileSize
		+strlen(first_boundary)
		+strlen(content_dispos)
		+strlen(content_type2)
		+strlen(end_boundary);
	bufferin.dwOffsetLow = 0;
	bufferin.dwOffsetHigh = 0;

	HttpSendRequestEx(hRequest, &bufferin,0, 0, 0);
	
	InternetWriteFile(hRequest,(byte*)first_boundary,strlen(first_boundary),&dwNumberOfBytesWritten); //first boundary
	InternetWriteFile(hRequest,(byte*)content_dispos,strlen(content_dispos),&dwNumberOfBytesWritten);
	InternetWriteFile(hRequest,(byte*)content_type2,strlen(content_type2),&dwNumberOfBytesWritten);
	InternetWriteFile(hRequest,lpBuffer,dwFileSize,&dwNumberOfBytesWritten);

	InternetWriteFile(hRequest,(byte*)end_boundary,strlen(end_boundary),&dwNumberOfBytesWritten);//last boundary

	HttpEndRequest(hRequest,0,0,0);

	VirtualFree(lpBuffer,0,MEM_RELEASE);

	// 获得服务器返回头部中Content-Length参数
	//DWORD dwInfoLevel=HTTP_QUERY_RAW_HEADERS_CRLF;	
	DWORD dwInfoLevel=HTTP_QUERY_CONTENT_LENGTH;
	DWORD dwInfoBufferLength=10;
	DWORD dwResultLength = 0;

	char* pInfoBuffer=(char*)malloc(dwInfoBufferLength+1);
	while(!HttpQueryInfo(hRequest,dwInfoLevel,pInfoBuffer,&dwInfoBufferLength,NULL)){
		if (GetLastError()==ERROR_INSUFFICIENT_BUFFER){
			free(pInfoBuffer);
			pInfoBuffer=(char*)malloc(dwInfoBufferLength+1);
		}else{
			fprintf(stderr,"HttpQueryInfo failed, error = %d (0x%x)\n",GetLastError(),GetLastError());
			break;
		}
	}
	pInfoBuffer[dwInfoBufferLength] = '\0';

	int resultLen = 0;
	resultLen = buf2int(pInfoBuffer, dwInfoBufferLength);

	// 读取文件
	char * result = (char *)malloc(resultLen+1);
	memset(result, 0, resultLen);
	DWORD dwRead2 = 0;
	InternetReadFile(hRequest, result, resultLen, &dwRead2);
	result[resultLen] = '\0';

	// 关闭连接
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hSession);
}


// 网络连接
void ConnectSlot()
{
	// 开始连接
	HINTERNET hSession = InternetOpen("MyAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	//HINTERNET hConnect = InternetConnect(hSession, _T("192.168.0.101"), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hConnect = InternetConnect(hSession, IP, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", GetResult, NULL, NULL, Accept, 0, 1);

	HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));

	// 获得服务器返回头部中Content-Length参数
	//DWORD dwInfoLevel=HTTP_QUERY_RAW_HEADERS_CRLF;	
	DWORD dwInfoLevel=HTTP_QUERY_CONTENT_LENGTH;
	DWORD dwInfoBufferLength=10;
	DWORD dwResultLength = 0;

	char* pInfoBuffer=(char*)malloc(dwInfoBufferLength+1);
	while(!HttpQueryInfo(hRequest,dwInfoLevel,pInfoBuffer,&dwInfoBufferLength,NULL)){
		if (GetLastError()==ERROR_INSUFFICIENT_BUFFER){
			free(pInfoBuffer);
			pInfoBuffer=(char*)malloc(dwInfoBufferLength+1);
		}else{
			fprintf(stderr,"HttpQueryInfo failed, error = %d (0x%x)\n",GetLastError(),GetLastError());
			break;
		}
	}
	pInfoBuffer[dwInfoBufferLength] = '\0';

	int resultLen = 0;
	resultLen = buf2int(pInfoBuffer, dwInfoBufferLength);

	// 读取文件
	char * result = (char *)malloc(resultLen+1);
	memset(result, 0, resultLen);
	DWORD dwRead = 0;
	InternetReadFile(hRequest, result, resultLen, &dwRead);
	result[resultLen] = '\0';


	// 关闭连接
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hSession);
}


// 把缓冲区中的字符串转换为整数
// 字符串最后结尾为 \0
int buf2int(char * buf, int len)
{
	int carry = 1;
	char * tmp = buf + len -1;
	int last = 0;

	while(len > 0)
	{
		last += (*tmp -48) * carry;
		carry *= 10;
		tmp--;
		len--;
	}
	return last;
}
