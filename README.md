# SColor
cpp-shell-color-manager

## example

![example.gif](https://github.com/kkkeQAQ/SColor/blob/markdown/example.gif)

	SColor defaultColor;
	SColor ac(SColor::BLUE,SColor::RED,SColor::UNDERLINE|SColor::ITALIC);
	SColor::hideCursor();
	int maxx=5,maxy=8;
	for(int i=0,j=0;;i++,j++)
	{
		int x=i,y=j;
		while(x>maxx)x=abs(2*maxx-x);
		while(y>maxy)y=abs(2*maxy-y);
		SColor::clean();
		SColor::setCursor(x,y*2);
		cout<<ac<<"test"<<defaultColor<<endl;
		ac^=SColor::INVERT;
		for(int i=0;i<100000000;i++);
	}
