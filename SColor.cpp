#include "SColor.h"

bool SColor::b_allEnabled=true;

void SColor::setAllEnabled(bool enabled)
{
	b_allEnabled=enabled;
}

bool SColor::allEnabled()
{
	return b_allEnabled;
}

void SColor::setEnabled(bool enabled)
{
	b_enabled=enabled;
}

bool SColor::enabled()const
{
	return b_enabled;
}

void SColor::move(int x,int y,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<x-1<<";"<<y-1<<"H";
}

void SColor::moveUP(int n,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<n<<"A";
}

void SColor::moveDOWN(int n,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<n<<"B";
}

void SColor::moveRIGHT(int n,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<n<<"C";
}

void SColor::moveLEFT(int n,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<n<<"D";
}

void SColor::clear(std::ostream& os)
{
	if(allEnabled())os<<"\e[2J\e[1;1H";
}

void SColor::clearLine(std::ostream& os)
{
	if(allEnabled())os<<"\e[K";
}

void SColor::setCursor(int x,int y,std::ostream& os)
{
	if(allEnabled())os<<"\e["<<x<<";"<<y<<"H";
}

void SColor::saveCursor(std::ostream& os)
{
	if(allEnabled())os<<"\e[s";
}

void SColor::unsetCursor(std::ostream& os)
{
	if(allEnabled())os<<"\e[u";
}

void SColor::hideCursor(std::ostream& os)
{
	if(allEnabled())os<<"\e[?25l";
}

void SColor::echoCursor(std::ostream& os)
{
	if(allEnabled())os<<"\e[?25h";
}

SColor::SColor(int fg,int bg,int style)
{
	this->foreground=(fg==DEFAULT)?0:fg+30;
	this->background=(bg==DEFAULT)?0:bg+40;
	this->style=style;
}

std::ostream& operator<<(std::ostream& os,const SColor& sColor)
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

SColor SColor::operator~()
{
	SColor res(*this);
	res.style=~res.style;
	return res;
}

const SColor& SColor::operator+=(int style)
{
	this->style|=style;
	return *this;
}

const SColor& SColor::operator-=(int style)
{
	this->style&=~style;
	return *this;
}

const SColor& SColor::operator|=(int style)
{
	this->style|=style;
	return *this;
}

const SColor& SColor::operator&=(int style)
{
	this->style&=style;
	return *this;
}

const SColor& SColor::operator^=(int style)
{
	this->style^=style;
	return *this;
}

SColor operator+(const SColor &a,int b)
{
	return SColor(a)+=b;
}

SColor operator-(const SColor &a,int b)
{
	return SColor(a)-=b;
}

SColor operator|(const SColor &a,int b)
{
	return SColor(a)|=b;
}

SColor operator&(const SColor &a,int b)
{
	return SColor(a)&=b;
}

SColor operator^(const SColor &a,int b)
{
	return SColor(a)^=b;
}

SColor& SColor::reset()
{
	this->background=0;
	this->foreground=0;
	this->style=0;
}

SColor& SColor::setFg(int fg)
{
	this->foreground=(fg==DEFAULT)?0:fg+30;
	return *this;
}

SColor& SColor::setBg(int bg)
{
	this->background=(bg==DEFAULT)?0:bg+40;
	return *this;
}

SColor& SColor::setStyle(int style)
{
	this->style=style;
	return *this;
}

int SColor::getFg()const
{
	if(foreground==DEFAULT)return DEFAULT;
	return foreground-30;
}

int SColor::getBg()const
{
	if(background==DEFAULT)return DEFAULT;
	return background-40;
}

int SColor::getStyle()const
{
	return style;
}
