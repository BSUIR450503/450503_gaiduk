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
        // child process
        /*
        int i = 0;
        for (; i < 5; ++i)
        {
            printf("child process: counter=%d\n", ++counter);
        }
        */

        execl("/home/yury/Desktop/laba1/bin/Debug/multpl","multpl",msg,NULL);
    }
    else if (pid > 0)
    {
        // parent process
        wait(&status);
            if (WIFEXITED(status))
            printf("Returned Value is : %i\n",WEXITSTATUS(status));
        /*
        int j = 0;
        for (; j < 5; ++j)
        {
            printf("parent process: counter=%d\n", ++counter);
        }
        */
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

#ifdef _WIN32
#define UNICODE
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#include <iostream>
#include <Windows.h>
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
	int value;
	cout << "enter integer value" << endl;
	cin >> value;

	//wchar_t* msg;
    //sprintf(msg,"%d ", value);
	//_wtoi
	//_itow_s(value,msg,2,10);
	//wchar_t* path;
	//path="I:\\SPO\\multpl.exe";	
	//TEXT(I:\\SPO\\multpl.exe 10)
	// Start the child process.
	if (!CreateProcess(L"I:\\SPO\\multpl.exe",   // No module name (use command line)
		TEXT("I:\\SPO\\multpl.exe 10"),        // Command line
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
