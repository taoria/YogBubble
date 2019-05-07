#include "IEvent.h"

YEvent::YEvent()
{
}

YEvent::YEvent(std::string name) {
	event_type = name;
	event_name = event_type + ":" + std::to_string(GetId());
}

UINT YEvent::GetId() {
	return 0;
}

void YEvent::SetId(YID id) {

}

std::string YEvent::GetName() {
	return this->event_name;
}

void YEvent::SetName(std::string name) {
	event_name = name;

}


IYog* YEvent::GetArg(std::string str) {
	return this->arg_yog_pool[str];
}

std::string YEvent::GetEventType() {
	return this->event_name;
}

YEvent::~YEvent() {
}

void YEvent::push(std::string name, IYog* object) {
	this->arg_yog_pool[name] = object;
}


UINT EventTemplate::GetId() {
	return 0;
}

void EventTemplate::SetId(YID id) {
}

std::string EventTemplate::GetName() {
	return {};
}

void EventTemplate::SetName(std::string) {
}

void EventTemplate::OnInit() {
}

void EventTemplate::OnRelease() {

}

EventTemplate::EventTemplate() {

}


