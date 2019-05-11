#pragma once
#include <intsafe.h>
#ifndef  YOG_DLL_EXPORT
#define  YOG_DLL_EXPORT  __declspec( dllimport )
#endif
namespace Data{
	class YOG_DLL_EXPORT TimerData{

	public:
		static float deltaTime;
		static float deltaTimeEvent;
	};
	
}