#include <lua.hpp>
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
#include "Component/ComponentSystem.h"
#include "../yogcore/physics/Collider.h"
#include <fstream>
using namespace Manager;
lua_State *globalLuaState;
void OnHandlingLuaCollision(IEvent* arg){
		auto res = dynamic_cast<ICollider*>(arg->GetArg("first"));
		auto res2 = dynamic_cast<ICollider*>(arg->GetArg("second"));
		LOG_N_F(YOG_INFO, "Triggering collision event, Entities are %d %d", res->entity->GetId(), res2->entity->GetId());
		int funcres = lua_getglobal(globalLuaState, "on_collision");
		if(funcres){
			lua_call(globalLuaState, 0, 0);
		}
}

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

void YogPillar::LuaUpdate(){
	std::fstream fs;
	fs.open("main.lua", std::ios::in);
	if (!fs) {
		return;
	}
	lua_getglobal(L, "update");
	lua_call(L, 0, 0);
}

void YogPillar::MainThread() {
	while(true) {
		double elapsedTime = timer.GetMilisecondsElapsed();
		Data::TimerData::deltaTime = elapsedTime;
		timer.Restart();

		ModuleManager *module_manager = dynamic_cast<ModuleManager*>(get_manager_by_name("module manager"));
		auto event_system = dynamic_cast<EventSystem*>(get_manager_by_name("event system"));

	
		ComponentSystem *cs = dynamic_cast<ComponentSystem*>(get_manager_by_name("component system"));
		event_system->HandlingEventSingle();
		LuaUpdate();
		EMIT("on update");
		cs->CallForUpdate();
		module_manager->CallUpdate();
		WaitForNextUpdate();
	}
}
void YogPillar::OnInit() {
	//初始化模组
	ModuleManager *module_manager = dynamic_cast<ModuleManager*>(get_manager_by_name("module manager"));

	module_manager->InitModule();
}

void YogPillar::LuaRun(){
	std::fstream fs;
	fs.open("main.lua", std::ios::in);
	if (!fs) {
		return;
	}
	L = luaL_newstate();
	globalLuaState = L;
	luaopen_base(L);

	luaL_openlibs(L);
	luaopen_entity_libs(L);

	luaL_dofile(L, "main.lua");
	lua_getglobal(L, "init");
	lua_call(L, 0, 0);

	//lua_close(L);
}
void YogPillar::PillarRun() {
	//初始化系统
	YogDebugger::DebugInfo("engine system init");
	PillarInit();

	YogDebugger::DebugInfo("engine init");
	//引擎初始化
	OnInit();

	LuaRun();

	EMIT("after init");

	YogDebugger::DebugInfo("main thread init");
	MainThread();

}
YogPillar::YogPillar(){




}
YogPillar::~YogPillar(){

}

