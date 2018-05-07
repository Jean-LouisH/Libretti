#include "include/Libretti.h"
#include "include/File.h"

int test()
{
	char* c;
	int a = 0;
	a++;
	c = loadScriptFile("../Demos/Single channel Test.txt");
	return a;
}