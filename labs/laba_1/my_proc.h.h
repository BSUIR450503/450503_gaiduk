#ifdef linux
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;
class my_proc
{
public:
int run(int argc, char **argv)
{
    printf("--beginning of program\n");
    int status,value;
    printf("enter integer value:\n");
    cin >> value;
    char msg[80];
    sprintf(msg,"%d ", value);
    pid_t pid = fork();
    if (pid == 0)
    {


        execl("/home/yury/Desktop/laba1/bin/Debug/multpl","multpl",msg,NULL);
    }
    else if (pid > 0)
    {
        // parent process
        wait(&status);
            if (WIFEXITED(status))
            printf("Returned Value is : %i\n",WEXITSTATUS(status));
    }
    else
    {
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }
    printf("--end of program--\n");
    return 0;
}
};
#endif // linux

#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#define UNICODE
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

class my_proc
{
public:
int run(int argc, WCHAR *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//int to tchar
	unsigned int value;
	cout << "enter integer value" << endl;
	cin >> value;
	std::wstring s = to_wstring(value);
	s.c_str();
	TCHAR * v1 = (wchar_t *)s.c_str();
	//filepath+int to tchar
	TCHAR CommandLine[80] = { TEXT("F:\\SPO\\multpl.exe ")};
	wcscat(CommandLine,v1);
		
	if (!CreateProcess(L"F:\\SPO\\multpl.exe",   // No module name (use command line)
		CommandLine,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		NULL,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		system("pause");
		return 1;
	}
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD ret=0;
	GetExitCodeProcess(pi.hProcess, &ret);
	cout << "programm returned = " << ret << endl;
	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	system("pause");
	return 0;
}
};
#endif
