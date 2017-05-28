#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "SColor.h"

using namespace std;

int main()
{
	SColor defaultColor;
	SColor ac(SColor::BLUE,SColor::RED,SColor::UNDERLINE|SColor::ITALIC);
	SColor::hideCursor();
	while(1)
	{
		SColor::clean();
		cout<<ac<<"test"<<defaultColor<<endl;
		ac^=SColor::INVERT;
		for(int i=0;i<100000000;i++);
	}
	return 0;
}

