#include "Color.h"

Color& Color::operator=(const Color& src){
	color = src.color;
	return *this;
}

Color::Color(const Color& src){
	color = src.color;
}

Color::Color(BYTE r, BYTE g, BYTE b, BYTE a){
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

Color::Color(BYTE r, BYTE g, BYTE b):Color(r,g,b,255){

}

Color::Color(unsigned val){
	color = val;
}

Color::Color():Color(0){

}

void Color::SetR(BYTE r){
	rgba[0] = r;
}
const Color Color::UnloaededTextureColor(100, 100, 100,255);
void Color::SetG(BYTE g){
	rgba[1] = g;
}

void Color::SetB(BYTE b){
	rgba[2] = b;
}

void Color::SetA(BYTE a){
	rgba[3] = a;
}
