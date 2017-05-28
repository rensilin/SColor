#include <iostream>

class SColor {
public:
	static const int BLACK	= 0;
	static const int RED	= 1;
	static const int GREEN	= 2;
	static const int YELLOW	= 3;
	static const int BLUE	= 4;
	static const int PURPLE	= 5;
	static const int CYAN	= 6;
	static const int WHITE	= 7;

	static const int HIGHLIGHT		= 1<<1;
	static const int DARK			= 1<<2;
	static const int ITALIC			= 1<<3;
	static const int UNDERLINE		= 1<<4;
	static const int BLINK			= 1<<5;
	static const int INVERT			= 1<<7;
	static const int BLANK			= 1<<8;
	static const int STRIKETHROUGH	= 1<<9;

	static void moveUP(int n=1,std::ostream& os=std::cout)
	{
		os<<"\e["<<n<<"A";
	}

	static void moveDOWN(int n=1,std::ostream& os=std::cout)
	{
		os<<"\e["<<n<<"B";
	}

	static void moveRIGHT(int n=1,std::ostream& os=std::cout)
	{
		os<<"\e["<<n<<"C";
	}

	static void moveLEFT(int n=1,std::ostream& os=std::cout)
	{
		os<<"\e["<<n<<"D";
	}

	static void clean(std::ostream& os=std::cout)
	{
		os<<"\e[2J\e[0;0H";
	}

	static void cleanLine(std::ostream& os=std::cout)
	{
		os<<"\e[K";
	}

	static void setCursor(int x,int y,std::ostream& os=std::cout)
	{
		os<<"\e["<<x<<";"<<y<<"H";
	}

	static void saveCursor(std::ostream& os=std::cout)
	{
		os<<"\e[s";
	}

	static void unsetCursor(std::ostream& os=std::cout)
	{
		os<<"\e[u";
	}

	static void hideCursor(std::ostream& os=std::cout)
	{
		os<<"\e[?25l";
	}

	static void echoCursor(std::ostream& os=std::cout)
	{
		os<<"\e[?25h";
	}

	SColor(int fg=-30,int bg=-40,int style=0)
	{
		this->foreground=fg+30;
		this->background=bg+40;
		this->style=style;
	}

	friend std::ostream& operator<<(std::ostream& os,const SColor& sColor)
	{
		os<<"\e["<<sColor.foreground;
		if(sColor.background)os<<';'<<sColor.background;
		for(int i=1;i<=9;i++)os<<';'<<((sColor.style&(1<<i))?i:i+20);
		os<<"m";
		return os;
	}

	SColor operator~()
	{
		SColor res(*this);
		res.style=~res.style;
		return res;
	}

	const SColor& operator+=(int style)
	{
		this->style|=style;
		return *this;
	}

	const SColor& operator-=(int style)
	{
		this->style&=~style;
		return *this;
	}

	const SColor& operator|=(int style)
	{
		this->style|=style;
		return *this;
	}

	const SColor& operator&=(int style)
	{
		this->style&=style;
		return *this;
	}

	const SColor& operator^=(int style)
	{
		this->style^=style;
		return *this;
	}

	friend SColor operator+(const SColor &a,int b)
	{
		return SColor(a)+=b;
	}

	friend SColor operator-(const SColor &a,int b)
	{
		return SColor(a)-=b;
	}

	friend SColor operator|(const SColor &a,int b)
	{
		return SColor(a)|=b;
	}

	friend SColor operator&(const SColor &a,int b)
	{
		return SColor(a)&=b;
	}

	friend SColor operator^(const SColor &a,int b)
	{
		return SColor(a)^=b;
	}

	SColor& reset()
	{
		this->background=0;
		this->foreground=0;
		this->style=0;
	}

	SColor& setFg(int fg)
	{
		this->foreground=fg+30;
		return *this;
	}

	SColor& setBg(int bg)
	{
		this->background=bg+40;
		return *this;
	}

	SColor& setStyle(int style)
	{
		this->style=style;
		return *this;
	}

	int getFg()
	{
		return foreground-30;
	}

	int getBg()
	{
		return background-40;
	}

	int getStyle()
	{
		return style;
	}

private:
	int foreground;
	int background;
	int style;
};
