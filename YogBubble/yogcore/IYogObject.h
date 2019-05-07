#pragma once
#include <combaseapi.h>
#include "IYog.h"
interface YOG_DLL_EXPORT IYogObject : public IYog{
	virtual void OnInit()=0;
	virtual void OnRelease()=0;
};
