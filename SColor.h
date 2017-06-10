#include <iostream>

class SColor {
private:
	static bool b_allEnabled;
	bool b_enabled=true;
public:
	static const int DEFAULT=-1;
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

	static void setAllEnabled(bool enabled=true)
	{
		b_allEnabled=enabled;
	}

	static bool allEnabled()
	{
		return b_allEnabled;
	}

	void setEnabled(bool enabled=true)
	{
		b_enabled=enabled;
	}

	bool enabled()const
	{
		return b_enabled;
	}

	static void moveUP(int n=1,std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e["<<n<<"A";
	}

	static void moveDOWN(int n=1,std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e["<<n<<"B";
	}

	static void moveRIGHT(int n=1,std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e["<<n<<"C";
	}

	static void moveLEFT(int n=1,std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e["<<n<<"D";
	}

	static void clean(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[2J\e[0;0H";
	}

	static void cleanLine(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[K";
	}

	static void setCursor(int x,int y,std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e["<<x<<";"<<y<<"H";
	}

	static void saveCursor(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[s";
	}

	static void unsetCursor(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[u";
	}

	static void hideCursor(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[?25l";
	}

	static void echoCursor(std::ostream& os=std::cout)
	{
		if(allEnabled())os<<"\e[?25h";
	}

	SColor(int fg=DEFAULT,int bg=DEFAULT,int style=0)
	{
		this->foreground=(fg==DEFAULT)?0:fg+30;
		this->background=(bg==DEFAULT)?0:bg+40;
		this->style=style;
	}

	friend std::ostream& operator<<(std::ostream& os,const SColor& sColor)
	{
		if(SColor::allEnabled()&&sColor.enabled())
		{
			os<<"\e["<<sColor.foreground;
			if(sColor.background)os<<';'<<sColor.background;
			for(int i=1;i<=9;i++)os<<';'<<((sColor.style&(1<<i))?i:i+20);
			os<<"m";
		}
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

	SColor& setFg(int fg=DEFAULT)
	{
		this->foreground=(fg==DEFAULT)?0:fg+30;
		return *this;
	}

	SColor& setBg(int bg=DEFAULT)
	{
		this->background=(bg==DEFAULT)?0:bg+40;
		return *this;
	}

	SColor& setStyle(int style)
	{
		this->style=style;
		return *this;
	}

	int getFg()const
	{
		if(foreground==DEFAULT)return DEFAULT;
		return foreground-30;
	}

	int getBg()const
	{
		if(background==DEFAULT)return DEFAULT;
		return background-40;
	}

	int getStyle()const
	{
		return style;
	}

private:
	int foreground;
	int background;
	int style;
};

bool SColor::b_allEnabled=true;

