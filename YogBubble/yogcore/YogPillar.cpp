#include "YogPillar.h"
#include "Event/EventSystem.h"
#include "Manager/YogManager.h"
#include <thread>
#include "yogwindow.h"
#include "yog.h"
#include "Module/ModuleManager.h"
#include "Manager/Manager.h"
#include "../tools/helper.h"
#include "../tools/Data/Data.h"
using namespace Manager;
void main_loop() {
	auto event_system = dynamic_cast<EventSystem*>(get_manager_by_name("event system"));

	//接收事件
	event_system->HandlingEvent();
}

void  YogPillar::PillarInit() {

	LoadMods();

	//开启主循环
//	std::thread thread(main_loop);

	//解
//	thread.detach();

	//载入模组




}
void YogPillar::LoadMods() {
	yog_module_loader = new YogModuleLoader;

	yog_module_loader->load_mod("null");
}

void YogPillar::WaitForNextUpdate() {

}

void YogPillar::MainThread() {
	while(true) {
		double elapsedTime = timer.GetMilisecondsElapsed();
		Data::TimerData::deltaTime = elapsedTime;
		timer.Restart();
		ModuleManager *module_manager = dynamic_cast<ModuleManager*>(get_manager_by_name("module manager"));
		auto event_system = dynamic_cast<EventSystem*>(get_manager_by_name("event system"));
		EMIT("on update");
		//接收事件
		event_system->HandlingEventSingle();
		module_manager->CallUpdate();
		WaitForNextUpdate();
	}
}
void YogPillar::OnInit() {
	//初始化模组
	ModuleManager *module_manager = dynamic_cast<ModuleManager*>(get_manager_by_name("module manager"));

	module_manager->InitModule();
}
void YogPillar::PillarRun() {
	//初始化系统
	YogDebugger::DebugInfo("engine system init");
	PillarInit();

	YogDebugger::DebugInfo("engine init");
	//引擎初始化
	OnInit();

	EMIT("after init");

	YogDebugger::DebugInfo("main thread init");
	MainThread();

}
YogPillar::YogPillar(){




}
YogPillar::~YogPillar(){

}

