#include "EventSystem.h"
#include "../../tools/helper.h"
#include "../Manager/YogManager.h"
#include "../Module/IYogModule.h"
#include "../../tools/Timer/Timer.h"
#include "EventQueue.h"
#include "InfoWrapper.h"
#include "../../tools/Data/Data.h"
EventSystem* EventSystem::event_system = nullptr;
void OnModuleInitialized(IEvent* i_yog) {
	// IYogModule* mod = dynamic_cast<IYogModule*>(i_yog->GetArg("module"));
	// InfoWrapper<std::string>* name = dynamic_cast<InfoWrapper<std::string>*>(i_yog->GetArg("module name"));
	// IYogManager* manager = dynamic_cast<IYogManager*>(get_manager("module manager"));
	// manager->RegisterTargetByName(name->GetData(), mod);
}
void OnKeyDown(IEvent* key_down) {
	ConsoleLogger::get_instance()->log("a key is down", YOG_INFO);
}
void OnRender(IEvent* render) {
	IYogManager* manager = dynamic_cast<IYogManager*>(get_manager("module manager"));
	IYogModule* render_module = dynamic_cast<IYogModule*>(manager->GetTargetFromName("renderer"));
	ConsoleLogger::get_instance()->log("rendering", YOG_INFO);
	render_module->OnModuleUpdate();

}
void on_init_finished(IEvent* i_yog){
	
}
void on_manager_init(IEvent* i_yog) {
	
}
void EventSystem::assign(IEvent* arg) {

	
}
void OnMouseWheel(IEvent* arg){
	
}

EventSystem::EventSystem(){
	RegisterEvent("module init", OnModuleInitialized);
	RegisterEvent("render", OnRender);
	RegisterEvent("mouse wheel", OnMouseWheel);
	RegisterEvent("after init", on_init_finished);
}


EventSystem::~EventSystem(){
}

EventSystem* EventSystem::get_instance() {
	if( !EventSystem::event_system) {
		event_system = new EventSystem;
	}
	return event_system;

}

void EventSystem::EmitInfo(IEvent* args) {
	if(this->get_event_queue()) {
		this->get_event_queue()->push(args);
	}
}
void EventSystem::EmitInfo(std::string str) {
	if(this->get_event_queue()) {
		EventTemplate * temp = dynamic_cast<EventTemplate*>(this->GetTargetFromName(str));
		if(this->GetTargetFromName(str)==nullptr) {
			ConsoleLogger::get_instance()->log_format(YOG_ERROR, "Event create failed :event template name %s ", str.c_str());
		}else {
			IEvent* new_event = create_event(str);
			this->EmitInfo(new_event);
		}
	}
}

void EventSystem::EmitInfo(std::string str,std::string key,IYog* info){
	if (this->get_event_queue()) {
		EventTemplate * temp = dynamic_cast<EventTemplate*>(this->GetTargetFromName(str));
		if (this->GetTargetFromName(str) == nullptr) {
			ConsoleLogger::get_instance()->log_format(YOG_ERROR, "Event create failed :event template name %s ", str.c_str());
		}
		else {
			IEvent* new_event = create_event(str);
			new_event->push(key, info);
			this->EmitInfo(new_event);
		}
	}

}

void EventSystem::RegisterEvent(std::string name ,EventTemplate* registerEventTemplate) {
	if (!event_type_pool[name]) {
		event_type_pool[name] = registerEventTemplate;
	}
	else {
		ConsoleLogger::get_instance()->log_format(YOG_ERROR, "error,event name duplicate");
	}
}



void EventSystem::RegisterEvent(std::string name,EventHandler eventHandle) {
	if(event_type_pool[name]){
		EventTemplate* y_template = event_type_pool[name];
		y_template->m_eventHandlerList.push_back(eventHandle);
	}else{
		EventTemplate* y_template = new EventTemplate;
		y_template->m_eventHandlerList.push_back(eventHandle);
		RegisterEvent(name, y_template);
	}
}

EventQueue* EventSystem::get_event_queue() {
	if(this->event_queue==nullptr) {
		return event_queue = new EventQueue();
	}
	return event_queue;
}

void EventSystem::HandlingEvent() {
	Timer timer;

	while(true) {
		Data::TimerData::deltaTimeEvent = timer.GetMilisecondsElapsed();
		timer.Restart();
		while (get_event_queue()->size()>0) {
			ConsoleLogger::get_instance()->log( "An event is hooked", YOG_INFO);
			IEvent* event = this->get_event_queue()->front();
			EventTemplate *event_template = static_cast<EventTemplate*>(this->GetTargetFromName(event->GetName()));
			if (event_template->m_eventHandlerList.size()==0) {
				
				ConsoleLogger::get_instance()->log_format(YOG_ERROR, "Event create failed :event template name %s", GetName().c_str());
				continue;
			}else{
				for(EventHandler v : event_template->m_eventHandlerList){
					v(event);
				}
			}
			get_event_queue()->pop();
		}
		while (get_event_queue()->size() == 0);
	}

}

void EventSystem::HandlingEventSingle(){
	while (get_event_queue()->size() > 0) {
		ConsoleLogger::get_instance()->log("An event is hooked", YOG_INFO);
		IEvent* event = this->get_event_queue()->front();
		EventTemplate *event_template = static_cast<EventTemplate*>(this->GetTargetFromName(event->GetName()));
		if (event_template->m_eventHandlerList.size() == 0) {
			ConsoleLogger::get_instance()->log_format(YOG_ERROR, "Event create failed :event template name %s", GetName().c_str());
			continue;
		}
		else {
			for (EventHandler v : event_template->m_eventHandlerList) {
				v(event);
			}
		}
		get_event_queue()->pop();
	}
}

IEvent* EventSystem::create_event(std::string event_name) {
	auto temp = new YEvent;
	temp->SetName(event_name);
	return dynamic_cast<IEvent*>(temp);
}

UINT EventSystem::GetId() {
	return 0;
}

void EventSystem::SetId(YID id) {
	this->id = id;
}

std::string EventSystem::GetName() {
	return "event system";
}

void EventSystem::SetName(std::string) {
	/* to do here*/
}

IYog* EventSystem::GetTargetFromName(std::string name) {
	return event_type_pool[name];
}

IYog* EventSystem::GetTargetFromName(std::wstring name) {
	return event_type_pool[YogString::ws2s(name)];
}

bool EventSystem::RegisterTargetByName(std::string name, IYog* target) {
	this->RegisterEvent(name, dynamic_cast<EventTemplate*>(target));
	return true;
}

bool EventSystem::RegisterTargetById(UINT yog_id, IYog* target) {
	YogDebugger::FunctionNotInstalled("EventSystem:register_target_by_id ");
	return false;
}

IYog* EventSystem::GetTargetFromId(UINT id) {
	YogDebugger::FunctionNotInstalled("EventSystem:get_target_from_id ");
	return nullptr;
}

// void EventSystem::on_target_registered(IYog* target) {
// }