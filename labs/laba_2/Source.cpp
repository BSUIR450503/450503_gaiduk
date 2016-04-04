#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include "proc.h"

using namespace std;

int main(int args, WCHAR*argv[])
{
	my_proc process;
	process.run(args, argv);
	return 0;
}

