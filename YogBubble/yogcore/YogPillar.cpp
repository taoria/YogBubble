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

	//�����¼�
	event_system->HandlingEvent();
}

void  YogPillar::PillarInit() {

	LoadMods();

	//������ѭ��
//	std::thread thread(main_loop);

	//��
//	thread.detach();

	//����ģ��




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
		//�����¼�
		event_system->HandlingEventSingle();
		module_manager->CallUpdate();
		WaitForNextUpdate();
	}
}
void YogPillar::OnInit() {
	//��ʼ��ģ��
	ModuleManager *module_manager = dynamic_cast<ModuleManager*>(get_manager_by_name("module manager"));

	module_manager->InitModule();
}
void YogPillar::PillarRun() {
	//��ʼ��ϵͳ
	YogDebugger::DebugInfo("engine system init");
	PillarInit();

	YogDebugger::DebugInfo("engine init");
	//�����ʼ��
	OnInit();

	EMIT("after init");

	YogDebugger::DebugInfo("main thread init");
	MainThread();

}
YogPillar::YogPillar(){




}
YogPillar::~YogPillar(){

}

