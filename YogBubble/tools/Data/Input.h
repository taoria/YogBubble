#pragma once
#include "../../stdafx.h"
#include <map>
#include "../../yogcore/Math/Vec3.h"

class YOG_DLL_EXPORT KeyCode{
public:
	UINT keyCodeCode;
	static KeyCode CTRL;
	static KeyCode LSHIFT;
	bool operator ==(KeyCode& keyCode);
	bool operator <(KeyCode& keyCode);
	bool operator <(KeyCode keyCode);
	bool operator ==(UINT keyCode);
	bool operator ==(char keyCode);
	KeyCode& operator =(KeyCode& keyCode);
	KeyCode& operator =(UINT keyCode);
	KeyCode(const KeyCode& keycode);
	friend bool operator <(KeyCode& left, KeyCode& rgiht);
	KeyCode(UINT keyCode);
	static KeyCode A;
	static KeyCode B;
	static KeyCode C;
	static KeyCode D;
	static KeyCode E;
	static KeyCode F;
	static KeyCode G;
	static KeyCode H;
	static KeyCode J;
	static KeyCode K;
	static KeyCode L;
	static KeyCode M;
	static KeyCode N;
	static KeyCode O;
	static KeyCode P;
	static KeyCode Q;
	static KeyCode R;
	static KeyCode S;
	static KeyCode T;
	static KeyCode U;
	static KeyCode V;
	static KeyCode W;
	static KeyCode X;
	static KeyCode Y;
	static KeyCode Z;
	static KeyCode SPACE;
	static KeyCode LEFT;
	static KeyCode UP;
	static KeyCode RIGHT;
	static KeyCode DOWN;
	static KeyCode III;

};

class YOG_DLL_EXPORT Input{
private:
	static std::map<KeyCode, bool> keyCodeState;
public:
	static bool MouseRightPressed;
	static bool MouseLeftPressed;
	static float MouseDelta;
	static Vec3 MousePosition;
	static void KeyDown(KeyCode& keyCode);
	static void KeyUp(KeyCode& keyCode);
	static bool KeyCodeDown(KeyCode& keyCode);
};
