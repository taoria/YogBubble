#pragma once
#include "yogwindow.h"
#include "YogPillar.h"

#define EMIT(str) EventSystem::get_instance()->EmitInfo(str)
#define EMIT_M(eventname,key,eventinfo)  EventSystem::get_instance()->EmitInfo(eventname,key,eventinfo)
class __declspec(dllexport) yog{
public:
	yog();
	~yog();
	yog(std::string args);
	void yog_init();
	YogPillar* yog_pillar;
	void dock_to_engine(HWND hwnd);
};
