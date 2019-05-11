#pragma once
#include <map>
#include "IEvent.h"
#include "../Manager/IYogManager.h"
#include "EventQueue.h"


class YOG_DLL_EXPORT EventSystem:public IYogManager{
protected:
	static EventSystem* event_system;
	std::map<std::string,EventTemplate*> event_type_pool;
	YID id;
	EventQueue* event_queue;
	void assign(IEvent *arg);
public:
	EventSystem();
	~EventSystem();
	static EventSystem* get_instance();
	void EmitInfo(IEvent* args);
	void EmitInfo(std::string str);
	void EmitInfo(std::string str, std::string key, IYog* info);

	void RegisterEvent(std::string name, EventHandler eventHandle);
	void RegisterEvent(std::string name , EventTemplate* register_event_template);

	virtual EventQueue* get_event_queue();
	virtual void HandlingEvent();
	virtual void HandlingEventSingle();
	virtual IEvent* create_event(std::string event_name);
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	IYog* GetTargetFromName(std::string name) override;
	IYog* GetTargetFromName(std::wstring name) override;
	bool RegisterTargetByName(std::string name, IYog* target) override;
	bool RegisterTargetById(UINT yog_id, IYog* target) override;
	IYog* GetTargetFromId(UINT id) override;
};

