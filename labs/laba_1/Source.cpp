#include "my_proc.h.h"

using namespace std;

int main(int args, WCHAR*argv[])
{
	my_proc process;
	process.run(args, argv);
	return 0;
}