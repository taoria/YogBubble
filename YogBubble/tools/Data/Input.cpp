#include "Input.h"
KeyCode KeyCode::A = 'A';
KeyCode KeyCode::B = 'B';
KeyCode KeyCode::C = 'C';
KeyCode KeyCode::D = 'D';
KeyCode KeyCode::E = 'E';
KeyCode KeyCode::F = 'F';
KeyCode KeyCode::G = 'G';
KeyCode KeyCode::H = 'H';
KeyCode KeyCode::III = 'I';
KeyCode KeyCode::J = 'J';
KeyCode KeyCode::K = 'K';
KeyCode KeyCode::L = 'L';
KeyCode KeyCode::M = 'M';
KeyCode KeyCode::N = 'N';
KeyCode KeyCode::O = 'O';
KeyCode KeyCode::P = 'P';
KeyCode KeyCode::Q = 'Q';
KeyCode KeyCode::R = 'R';
KeyCode KeyCode::S = 'S';
KeyCode KeyCode::T = 'T';
KeyCode KeyCode::U = 'U';
KeyCode KeyCode::V = 'V';
KeyCode KeyCode::W = 'W';
KeyCode KeyCode::X = 'X';
KeyCode KeyCode::Y = 'Y';
KeyCode KeyCode::Z = 'Z';
KeyCode KeyCode::SPACE = 32;
KeyCode KeyCode::LEFT = 37;
KeyCode KeyCode::UP = 38;
KeyCode KeyCode::RIGHT = 39;
KeyCode KeyCode::DOWN = 40;
std::map<KeyCode, bool> Input::keyCodeState;
float Input::MouseDelta = 0.0;
Vec3 Input::MousePosition = {0, 0, 0};
bool Input::MouseLeftPressed = false;
bool Input::MouseRightPressed = false;

bool KeyCode::operator==(KeyCode& keyCode){
	return keyCodeCode == keyCode.keyCodeCode;
}

bool KeyCode::operator<(KeyCode& keyCode){
	return keyCodeCode < keyCode.keyCodeCode;
}

bool KeyCode::operator<(const KeyCode keyCode){
	return keyCodeCode < keyCode.keyCodeCode;
}

bool KeyCode::operator==(UINT keyCode){
	return keyCodeCode == keyCode;
}

bool KeyCode::operator==(char keyCode){
	return keyCodeCode == keyCode;
}

KeyCode& KeyCode::operator=(KeyCode& keyCode){
	return keyCode;
}

KeyCode& KeyCode::operator=(UINT keyCode){
	keyCodeCode = keyCode;
	return * (this);
}


KeyCode::KeyCode(const KeyCode& keycode){
	keyCodeCode = keycode.keyCodeCode;
}

KeyCode::KeyCode(UINT keyCode){
	keyCodeCode = keyCode;
}

void Input::KeyDown(KeyCode& keyCode){
	keyCodeState[std::move(keyCode)] = true;
}

void Input::KeyUp(KeyCode& keyCode){
	keyCodeState[std::move(keyCode)] = false;
}

bool Input::KeyCodeDown(KeyCode& keyCode){
	return keyCodeState[std::move(keyCode)];
}


bool operator<(const KeyCode& left, const KeyCode& right){
	return left.keyCodeCode < right.keyCodeCode;
}
