#pragma once
#include "../stdafx.h"
#include <string>
#include "YogDefine.h"
struct IEvent;
interface  __declspec(dllexport) IYog{
public:
	virtual ~IYog() = default;
	virtual UINT GetId()=0;
	virtual void SetId(YID id) = 0;
	virtual std::string GetName()=0;
	virtual void SetName(std::string) = 0;

};


	

typedef void (IYog::*YogEventHandler)(IEvent* event);