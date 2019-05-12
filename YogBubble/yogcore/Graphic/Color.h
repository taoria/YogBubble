#pragma once
#include "../../stdafx.h"
class Color{
public:
	Color & operator= (const Color& src);
	Color(const Color &src);
	Color(BYTE r,BYTE g,BYTE b,BYTE a);
	Color(BYTE r, BYTE g, BYTE b);
	Color(unsigned int val);
	Color();
	const static Color UnloaededTextureColor;
	constexpr  BYTE GetR() const;
	void SetR(BYTE r);
	constexpr  BYTE GetG() const;
	void SetG(BYTE g);
	constexpr  BYTE GetB() const;
	void SetB(BYTE b);
	constexpr  BYTE GetA() const;
	void SetA(BYTE a);
private:
	union{
		unsigned int color;
		BYTE rgba[4];
	};
};

constexpr BYTE Color::GetR() const{
	return rgba[0];
}

constexpr BYTE Color::GetG() const{
	return rgba[1];
}

constexpr BYTE Color::GetB() const{
	return rgba[2];
}

constexpr BYTE Color::GetA() const{
	return rgba[3];
}
