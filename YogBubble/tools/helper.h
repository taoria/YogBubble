#pragma once
#include <intsafe.h>
#include <exception>
#include "logger/ConsoleLogger.h"
#include <comutil.h>  

#pragma comment(lib, "comsuppw.lib")

using Microsoft::WRL::ComPtr;

namespace YogDebugger {
	inline void ThrowIfFailed(HRESULT hr) {
		if(FAILED(hr)) {
			ConsoleLogger::get_instance()->log_format(YOG_DEBUG,L"An error rises ,error code: %X",hr);
	//		throw std::exception();
		}
	}
	inline void DebugResultInfo(HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_INFO, "the result is %X", hr);
	}
	inline void DebugInfo(std::string str) {
		ConsoleLogger::get_instance()->log_format(YOG_INFO, "%s", str.c_str());
	}
	inline void DebugError(HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_DEBUG, "A error: %X", hr);
	}
	inline void DebugError(std::wstring str) {
		ConsoleLogger::get_instance()->log_format(YOG_DEBUG, L"A error: %s", str);
	}
	inline void DebugError(std::wstring str, HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_ERROR, L"A error occured: %s %X", str.c_str(),hr);
	}
	inline void DebugErrorBox(std::wstring str) {
		MessageBox(nullptr, str.c_str(), L"Error", 0);
	}
	inline void FunctionNotInstalled(std::string info) {
		ConsoleLogger::get_instance()->log_format(YOG_WARN, "function not yet installed,function pointer:%s", info);
	}
	inline void LogInfo(const char* log_format, ...){
		ConsoleLogger::get_instance()->log_format(YOG_INFO,log_format,"log nothing");
	}

}
inline std::string PCharToString(const char* w){
	std::string result(w);
	return result;
}
#define LOG_N_F(LEVEL,format,...)ConsoleLogger::get_instance()->log_format(LEVEL,format.c_str(),__VA_ARGS__)
#define LOG(s) ConsoleLogger::get_instance()->log_format(YOG_INFO, "in file '%s' ,line %d, function %s   %s",__FILE__,__LINE__,__FUNCTION__,s)
#define LOG_L(LEVEL,s) ConsoleLogger::get_instance()->log_format(LEVEL, "in file '%s' ,line %d, function %s    %s",__FILE__,__LINE__,__FUNCTION__,s)
#define LOG_F(LEVEL,format,...)  ConsoleLogger::get_instance()->log_format(LEVEL,(PCharToString("in file '%s' ,line %d, function %s  ")+format).c_str(),__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
namespace YogString {


	inline std::string ws2s(const std::wstring& ws)
	{
	
		_bstr_t t = ws.c_str();
		char* pchar = (char*)t;
		std::string result = pchar;
		return result;
	}

	inline std::wstring s2ws(const std::string& s)
	{
		_bstr_t t = s.c_str();
		wchar_t* pwchar = (wchar_t*)t;
		std::wstring result = pwchar;
		return result;
	}
}

namespace  YogHelper{
	inline void GetAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize)
	{
		if (path == nullptr)
		{
			throw std::exception();
		}

		DWORD size = GetModuleFileName(nullptr, path, pathSize);
		if (size == 0 || size == pathSize)
		{
			// Method failed or path was truncated.
			throw std::exception();
		}

		WCHAR* lastSlash = wcsrchr(path, L'\\');
		if (lastSlash)
		{
			*(lastSlash + 1) = L'\0';
		}
	}
	inline std::wstring get_asset_path(){
		WCHAR assetsPath[512];
		GetAssetsPath(assetsPath, _countof(assetsPath));
		std::wstring res = assetsPath;
		return res;
	}
	inline std::wstring get_asset_path(std::wstring input){
		return get_asset_path() + input;
	}
}