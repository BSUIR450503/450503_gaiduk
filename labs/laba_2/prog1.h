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
//WCHAR* CommandLine;

int main(int args, char *argv[])
{
	HANDLE CloseEvent;
	bool printflag = false;
	int number;
	number = atoi(argv[1]);
	/*if (args == 2)
	printf("second arg is:%d", number);
	*/

	wchar_t * t = new wchar_t[256];
	string eventname = { "print" };
	string closename = { "close" };
	string exitname = { "exit" };
	char procnumber[80];
	_itoa(number, procnumber, 10);
	eventname += procnumber;
	closename += procnumber;
	exitname = procnumber;
	mbstowcs(t, eventname.c_str(), 128);
	//return from program
	wchar_t * tt = new wchar_t[256];
	mbstowcs(tt, closename.c_str(), 128);
	//quit
	wchar_t * ttt = new wchar_t[256];
	mbstowcs(ttt, exitname.c_str(), 128);
	HANDLE PrintEvent;
	PrintEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, t);
	HANDLE ExitEvent;
	CloseEvent = CreateEvent(NULL, FALSE, FALSE, tt);
	ExitEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, ttt);

	while (1)
	{
		
		if (WaitForSingleObject(PrintEvent, 10) == WAIT_OBJECT_0)
		{
			printflag = true;
			if (printflag)
			{
				string prog = ("programm ");
				prog += procnumber;
				{
					for (int x = 0; x < prog.length(); x++)
					{
						cout << prog[x];
						Sleep(100);
						fflush(stdout);
					}
					fflush(stdout);
				}
				printflag = false;
				SetEvent(CloseEvent);
			}
			ResetEvent(PrintEvent);
		}
		ExitEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, ttt);
		if (WaitForSingleObject(ExitEvent, 10) == WAIT_OBJECT_0)
		{
			cout << "exitflag" << endl;
			//printflag = true;
			exit(0);
			/*if (printflag)
			{
			string prog = ("programm ");
			prog += procnumber;
			{
			for (int x = 0; x < prog.length(); x++)
			{
			cout << prog[x];
			Sleep(200);
			fflush(stdout);
			}
			fflush(stdout);
			}
			printflag = false;
			SetEvent(CloseEvent);
			}*/
		}
	}
	return 0;
}

//}
//#define UNICODE
//#ifdef UNICODE
//typedef wchar_t TCHAR;
//#else
//typedef char TCHAR;
//#endif
//#include <iostream>
//#include <Windows.h>
//#include <string>
//
//using namespace std;
////WCHAR* CommandLine;
//
//int main(int args, char *argv[])
//{
//
//	HANDLE CloseEvent;
//	bool printflag;
//	/*unsigned int value = 20;
//	std::wstring s = to_wstring(value);
//	s.c_str();
//	TCHAR * v1 = (wchar_t *)s.c_str();
//	TCHAR CommandLine[80] = { TEXT("process1 ") };
//	wcscat_s(CommandLine, v1);
//	*/
//
//	wchar_t * t = new wchar_t[256];
//	string eventname;
//	eventname = 20 + "print";
//	mbstowcs(t, eventname.c_str(), 128);
//
//	if (args < 2)
//	{
//		printf("usage: %s [cmdline]\n", argv[0]);
//		return 1;
//	}
//	int x = atoi(argv[1]);
//	HANDLE PrintEvent = (HANDLE)x;
//	while (1)
//	{
//
//		if (WaitForSingleObject(PrintEvent, 10) == WAIT_OBJECT_0)
//		{
//			printflag = true;
//			ResetEvent(PrintEvent);
//		}
//		else
//		{
//			printflag = false;
//			cout << "SEND ME THIS PUMPKIN SIGNAL!" << endl;
//			Sleep(100);
//		}
//		if (printflag)
//		{
//			char *prog = argv[1];
//			{
//				for (int x = 0; x < 4; x++)
//				{
//					cout << &prog[x];
//					fflush(stdout);
//				}
//				cout << atoi(argv[1]);
//				fflush(stdout);
//			}
//		}
//		Sleep(100);
//	}
//}