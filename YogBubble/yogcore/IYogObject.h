#pragma once
#include "IYog.h"
struct YOG_DLL_EXPORT IYogObject : public IYog{
	virtual void OnInit()=0;
	virtual void OnRelease()=0;
};
