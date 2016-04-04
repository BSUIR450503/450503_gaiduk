#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#include <iostream>
#include <Windows.h>
#include <string>
#include <list>
#include <conio.h>
using namespace std;

class my_proc
{
public:
	HANDLE PrintEvent;
	HANDLE CloseEvent;
	HANDLE ExitEvent;
	bool can_print;
	bool stop_print;
	HANDLE processArr[21];
	unsigned int numberofprocess = 0;
	int curr_process = 0;
	int run(int argc, WCHAR *argv[])
	{
		//CreateEvent();

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		string eventname = { "print" };
		string exitname = { "exit" };
		string closename = { "close" };
		wchar_t * t = new wchar_t[256];
		wchar_t * tt = new wchar_t[256];
		wchar_t * ttt = new wchar_t[256];
		bool busy = false;
		while (1)
		{
			int border = numberofprocess;
			for (int x = 0; x < border; x++)
			{
				if (numberofprocess == 0 || busy == false)
				{
				char procnumber[80];
				_itoa(x, procnumber, 10);
				string eventname = { "print" };
				string exitname = { "exit" };
				string closename = { "close" };
				eventname += procnumber;
				exitname += procnumber;
				closename += procnumber;
				mbstowcs(t, eventname.c_str(), 128);
				mbstowcs(tt, closename.c_str(), 128);
				mbstowcs(ttt, exitname.c_str(), 128);
				PrintEvent = CreateEvent(NULL, TRUE, FALSE, t);
				CloseEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, tt);
				SetEvent(PrintEvent);
				Sleep(500);
				ResetEvent(PrintEvent);
				busy = true;
				}
				if (WaitForSingleObject(CloseEvent, INFINITE)== WAIT_OBJECT_0)
				{
					// cout << "good";
					busy = false;
				}
				//numberofprocess++;


			}
			if (_kbhit())
			{
				string eventname = { "print" };
				string exitname = { "exit" };
				string closename = { "close" };
				char c = _getch();
				fflush(stdin);
				//case +
				switch (c)
				{
				case '+':
				{
							std::wstring s = to_wstring(numberofprocess);
							s.c_str();
							TCHAR * v1 = (wchar_t *)s.c_str();
							TCHAR CommandLine[80] = { TEXT("process1 ") };
							wcscat(CommandLine, v1);

							//string eventname = { "print" };
							char procnumber[80];
							_itoa(numberofprocess, procnumber, 10);
							eventname += procnumber;
							mbstowcs(t, eventname.c_str(), 128);
							//cout << "+" << endl;
							PrintEvent = CreateEvent(NULL, TRUE, FALSE, t);
							if (!CreateProcess(TEXT("F:\\SPO\\laba2_\\Debug\\output.exe"), CommandLine, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
							{
								printf("CreateProcess failed (%d).\n", GetLastError());
								system("pause");
								return 1;
							}
							processArr[numberofprocess] = pi.hProcess;
							Sleep(1500);
							numberofprocess++;
				}

					break;
				case '-':
				{
							if (numberofprocess == -1)
								break;
							string exitname = { "exit" };
							char procnumber[80];
							_itoa(numberofprocess-1, procnumber, 10);
							exitname = procnumber;
							mbstowcs(ttt, exitname.c_str(), 128);
							ExitEvent = CreateEvent(NULL, FALSE, FALSE, ttt);
							cout << "-" << endl;
							SetEvent(ExitEvent);
							Sleep(100);
							pi.hProcess = processArr[numberofprocess - 1];
							CloseHandle(pi.hProcess);
							CloseHandle(pi.hThread);
							numberofprocess--;
							processArr[numberofprocess] = NULL;
				}
					break;
					//case q
				case 'q':
				{
							cout << "q" << endl;
							int border = numberofprocess;
							for (int x = border; x > 0;x--)
							{
								if (numberofprocess == 0 || busy == false)
								{									
									char procnumber[80];
									_itoa(x, procnumber, 10);
									string exitname = { "exit" };
									exitname += procnumber;
									mbstowcs(ttt, exitname.c_str(), 128);
									ExitEvent = CreateEvent(NULL, FALSE, FALSE, ttt);
									SetEvent(ExitEvent);
									Sleep(500);
									pi.hProcess = processArr[numberofprocess - 1];
									CloseHandle(pi.hProcess);
									CloseHandle(pi.hThread);
									numberofprocess--;
								};
							}

				}
					break;	//delete
				default:
				{
						   cout << "default actions" << endl;
				}
					break;
					//defalut

				}
			}
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		system("pause");
		return 0;
	}
};
#endif

#ifdef __linux__

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>



bool printflag = false;
bool printend = true;

void hdl(int sig)
{
if (sig==SIGUSR1)
printflag = true;
if (sig==SIGUSR2)
printend = true;
}

int mygetch( ) {
  struct termios oldt,
                 newt;
  int            ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}
int kbhit(void)
{
        struct timeval        timeout;
        fd_set                readfds;
        int                how;

        /* look only at stdin (fd = 0) */
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

        /* poll: return immediately */
        timeout.tv_sec = 0L;
        timeout.tv_usec = 0L;

        how = select(1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
        /* Change "&timeout" above to "(struct timeval *)0"       ^^^^^^^^
         * if you want to wait until a key is hit
         */

        if ((how > 0) && FD_ISSET(0, &readfds))
                return 1;
        else
                return 0;
}

using namespace std;

int main (int args,char* argv[])
{


cout << "try to create process" <<endl;
pid_t pidArr[21];
int countofprocess=0;

struct sigaction act;
memset(&act, 0, sizeof(act));
act.sa_handler = hdl;
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGUSR1);
sigaddset(&set, SIGUSR2);
act.sa_mask = set;
sigaction(SIGUSR1, &act, 0);
sigaction(SIGUSR2, &act, 0);
pid_t parent_pid = getpid();
int noint=0;
int currentproc=0;
bool flag = false;
//string printstr = "process 1";
 string printstr[] = { "1. First process\r\n", "2. Second process\r\n",
                                    "3. Third process\r\n", "4. Fourth process\r\n",
                                    "5. Fifth process\r\n", "6. Sixth process\r\n",
                                    "7. Seventh process\r\n", "8. Eighth process\r\n",
                                    "9. Ninth process\r\n", "10. Tenth process\r\n" };

    while(1)
    {
        int key=15;
        if (kbhit())
            key = mygetch();
        fflush(stdin);
        fflush(stdout);

        usleep(10);
        switch(key)
        {
        case '+':
            {
                if (countofprocess < 21)
                {
                    pidArr[countofprocess] = fork();
                    countofprocess++;

                    switch(pidArr[countofprocess-1])
                    {
                        case -1:
                        {
                            cout << "erroe" <<endl;
                        }
                        break;
                        case 0:{
                                    printend=false;
                                    while (!printend)
                                    {
                                    usleep(1000);
                                    if (printflag)
                                    {
                                        for (int i=0;i < strlen(printstr[currentproc].c_str());i++)
                                        {
                                             cout << printstr[currentproc][i];
                                        fflush(stdout);
                                        usleep(50000);
                                        }

                                    }
                                    kill(parent_pid,SIGUSR2);
                                    }
                                    return 0;
                                    break;
                                }

                        break;
                    }
                }

            }
            break;
        case '-':
            {
            if (countofprocess > 0)
                {
                    kill(pidArr[--countofprocess], SIGUSR2);
                    waitpid(pidArr[countofprocess], NULL, 0);
                    kill(pidArr[countofprocess], SIGTERM);
                    waitpid(pidArr[countofprocess], NULL, 0);
                }
                //countofprocess--;
            }
            break;
        case 'q':
            {
                if (countofprocess > 0)
                {
                    for (; countofprocess > 0; countofprocess--)
                    {
                        kill(pidArr[countofprocess-1], SIGUSR2);
                        waitpid(pidArr[countofprocess-1], NULL, 0);
                        kill(pidArr[countofprocess-1], SIGKILL);
                        waitpid(pidArr[countofprocess-1], NULL, 0);
                    }
                }
            }
            break;
        }
        if (printend && countofprocess > 0)
            {
                //signal(SIGUSR2,SIG_DFL);
                printend = 0;
				if (currentproc >= countofprocess)
				{
					currentproc = 1;
				}
				else
				{
					if (!flag)
					{
						currentproc++;
					}
				}
				flag = false;
				kill(pidArr[currentproc-1], SIGUSR1);
				//sleep(2);
            }
            refresh;

    }

}

#endif