#ifndef SCOLOR_H
#define SCOLOR_H
#include <iostream>
class SColor {
private:
	static bool b_allEnabled;
	bool b_enabled=true;
public:
	enum Color {
		DEFAULT=-1,
		BLACK	= 0,
		RED	= 1,
		GREEN	= 2,
		YELLOW	= 3,
		BLUE	= 4,
		PURPLE	= 5,
		CYAN	= 6,
		WHITE	= 7,
	};
	enum Flag {
		HIGHLIGHT		= 1<<1,
		DARK			= 1<<2,
		ITALIC			= 1<<3,
		UNDERLINE		= 1<<4,
		BLINK			= 1<<5,
		INVERT			= 1<<7,
		BLANK			= 1<<8,
		STRIKETHROUGH	= 1<<9,
	};
	static void setAllEnabled(bool enabled=true);
	static bool allEnabled();
	void setEnabled(bool enabled=true);
	bool enabled()const;
	static void move(int x,int y,std::ostream& os=std::cout);
	static void moveUP(int n=1,std::ostream& os=std::cout);
	static void moveDOWN(int n=1,std::ostream& os=std::cout);
	static void moveRIGHT(int n=1,std::ostream& os=std::cout);
	static void moveLEFT(int n=1,std::ostream& os=std::cout);
	static void clear(std::ostream& os=std::cout);
	static void clearLine(std::ostream& os=std::cout);
	static void setCursor(int x,int y,std::ostream& os=std::cout);
	static void saveCursor(std::ostream& os=std::cout);
	static void unsetCursor(std::ostream& os=std::cout);
	static void hideCursor(std::ostream& os=std::cout);
	static void echoCursor(std::ostream& os=std::cout);
	SColor(int fg=DEFAULT,int bg=DEFAULT,int style=0);
	friend std::ostream& operator<<(std::ostream& os,const SColor& sColor);
	SColor operator~();
	const SColor& operator+=(int style);
	const SColor& operator-=(int style);
	const SColor& operator|=(int style);
	const SColor& operator&=(int style);
	const SColor& operator^=(int style);
	friend SColor operator+(const SColor &a,int b);
	friend SColor operator-(const SColor &a,int b);
	friend SColor operator|(const SColor &a,int b);
	friend SColor operator&(const SColor &a,int b);
	friend SColor operator^(const SColor &a,int b);
	SColor& reset();
	SColor& setFg(int fg=DEFAULT);
	SColor& setBg(int bg=DEFAULT);
	SColor& setStyle(int style);
	int getFg()const;
	int getBg()const;
	int getStyle()const;
private:
	int foreground;
	int background;
	int style;
};

#endif //SCOLOR_H
