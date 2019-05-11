#pragma once
#include <string>
#include "YogDefine.h"
#include "../stdafx.h"
struct IEvent;
struct  YOG_DLL_EXPORT IYog {
	virtual ~IYog() = default;
	virtual YID GetId() = 0;
	virtual void SetId(YID id) = 0;
	virtual std::string GetName() = 0;
	virtual void SetName(std::string) = 0;
};
typedef void (IYog::*YogEventHandler)(IEvent* event);