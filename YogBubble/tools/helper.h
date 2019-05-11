#pragma once
#include "logger/ConsoleLogger.h"
#include "../stdafx.h"
#define LOG_N_F(LEVEL,format,...)ConsoleLogger::get_instance()->log_format(LEVEL,format,__VA_ARGS__)
#define LOG(s) ConsoleLogger::get_instance()->log_format(YOG_INFO, "in file '%s' ,line %d, function %s   :%s",__FILE__,__LINE__,__FUNCTION__,s)
#define LOG_L(LEVEL,s) ConsoleLogger::get_instance()->log_format(LEVEL, "in file '%s' ,line %d, function %s    %s",__FILE__,__LINE__,__FUNCTION__,s)
#define LOG_F(LEVEL,format,...)  ConsoleLogger::get_instance()->log_format(LEVEL,(PCharToString("in file '%s' ,line %d, function %s  ")+format).c_str(),__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)

class Vec3;

namespace YogDebugger {
	 void ThrowIfFailed(HRESULT hr);
	 void DebugResultInfo(HRESULT hr);
	 void DebugInfo(std::string str);
	 void DebugError(HRESULT hr);
	 void DebugError(std::wstring str);
	 void DebugError(std::wstring str, HRESULT hr);
	 void DebugErrorBox(std::wstring str);
	 void FunctionNotInstalled(std::string info);
	 void LogInfo(const char* log_format, ...);

}
std::string YOG_DLL_EXPORT PCharToString(const char* w);

namespace YogString {


	 std::string ws2s(const std::wstring& ws);

	 std::wstring s2ws(const std::string& s);
}

namespace  YogHelper{
	void GetAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize);
	 std::wstring YOG_DLL_EXPORT get_asset_path();
	 std::wstring YOG_DLL_EXPORT get_asset_path(std::wstring input);
	 void YOG_DLL_EXPORT SetMousePosition(Vec3 vec3);
}