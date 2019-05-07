#pragma once
#include "Module/YogModuleLoader.h"
#include "../tools/Timer/Timer.h"
class  YogPillar{
protected:
	YogModuleLoader* yog_module_loader{};
	Timer timer;
public:
	void PillarInit();
	void LoadMods();
	void WaitForNextUpdate();
	void MainThread();
	void OnInit();
	void PillarRun();
	YogPillar();
	~YogPillar();
};

