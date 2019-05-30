#pragma once
#include "../lua/lua_reg.h"
#include "Module/YogModuleLoader.h"
#include "../tools/Timer/Timer.h"


class  YogPillar{
protected:
	YogModuleLoader* yog_module_loader{};
	Timer timer;
	lua_State* L;
public:
	void PillarInit();
	void LoadMods();
	void WaitForNextUpdate();
	void LuaUpdate();
	void MainThread();
	void OnInit();
	void LuaRun();
	void PillarRun();
	YogPillar();
	~YogPillar();
};

