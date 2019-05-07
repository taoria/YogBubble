#pragma once
#include "../../stdafx.h"
#include "../IYog.h"
#include "../IYogObject.h"
#include <map>
#include <complex.h>
interface  YOG_DLL_EXPORT IEvent:public IYog{
	virtual std::string GetEventType()= 0;
	virtual IYog* GetArg(std::string str) = 0;
	virtual void push(std::string name, IYog* object) = 0;
};

class YOG_DLL_EXPORT YEvent:public IEvent {
protected:
	std::string event_type;
	std::string event_name;
	std::map<std::string, IYog*> arg_yog_pool;
public:
	YEvent();
	YEvent(std::string name);
	~YEvent();
	UINT GetId() override;
	void SetId(YID id) override;

	std::string GetName() override;
	void SetName(std::string) override;
	IYog* GetArg(std::string str) override;
	std::string GetEventType() override;
	void push(std::string name, IYog* object);
};
class EventTemplate;
typedef void (*EventHandler) (IEvent*);
class YOG_DLL_EXPORT  EventTemplate:public IYogObject {

public:
	EventHandler temp_event_handler;
	std::vector<EventHandler> m_eventHandlerList;

	UINT GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	EventTemplate();
	IEvent* CreateEvent();

};
