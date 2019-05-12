#pragma once
#include "helper.h"
#include <intsafe.h>
#include <exception>
#include "logger/ConsoleLogger.h"
#include <comutil.h>  
#include "../yogcore/Math/Vec3.h"
#include "../yogcore/yogwindow.h"
#include <algorithm>
#pragma comment(lib, "comsuppw.lib")

using Microsoft::WRL::ComPtr;

namespace YogDebugger {
	void ThrowIfFailed(HRESULT hr) {
		if (FAILED(hr)) {
			ConsoleLogger::get_instance()->log_format(YOG_DEBUG, L"An error rises ,error code: %X", hr);
			//		throw std::exception();
		}
	}
	void DebugResultInfo(HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_INFO, "the result is %X", hr);
	}
	void DebugInfo(std::string str) {
		ConsoleLogger::get_instance()->log_format(YOG_INFO, "%s", str.c_str());
	}
	void DebugError(HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_DEBUG, "A error: %X", hr);
	}
	void DebugError(std::wstring str) {
		ConsoleLogger::get_instance()->log_format(YOG_DEBUG, L"A error: %s", str);
	}
	 void DebugError(std::wstring str, HRESULT hr) {
		ConsoleLogger::get_instance()->log_format(YOG_ERROR, L"A error occured: %s %X", str.c_str(), hr);
	}
	void DebugErrorBox(std::wstring str) {
		MessageBox(nullptr, str.c_str(), L"Error", 0);
	}
	void FunctionNotInstalled(std::string info) {
		ConsoleLogger::get_instance()->log_format(YOG_WARN, "function not yet installed,function pointer:%s", info);
	}
	void LogInfo(const char* log_format, ...) {
		ConsoleLogger::get_instance()->log_format(YOG_INFO, log_format, "log nothing");
	}

}
 std::string PCharToString(const char* w) {
	std::string result(w);
	return result;
}

std::string YogString::GetDirectoryFromPath(const std::string& filename){
	size_t off1 = filename.find_last_of('\\');
	size_t off2 = filename.find_last_of('/');
	if(off1 == std::string::npos && off2 == std::string::npos){
		return "";
	}
	if(off1==std::string::npos){
		return filename.substr(0, off2 - 1);
	}
	if(off2==std::string::npos){
		return filename.substr(0, off1 - 1);
	}
	return filename.substr(0, std::max(off1, off2) -1);
}

namespace YogString {


	 std::string ws2s(const std::wstring& ws)
	{

		_bstr_t t = ws.c_str();
		char* pchar = (char*)t;
		std::string result = pchar;
		return result;
	}

	 std::string GetFileExtension(const std::string& filename){
		 size_t off = filename.find_last_of('.');
		 if(off== std::string::npos){
			 return {};
		 }
		 return std::string(filename.substr(off + 1));
	 }

	 std::wstring s2ws(const std::string& s)
	{
		_bstr_t t = s.c_str();
		wchar_t* pwchar = (wchar_t*)t;
		std::wstring result = pwchar;
		return result;
	}
}

namespace  YogHelper {
	 void GetAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize)
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
	std::wstring get_asset_path() {
		WCHAR assetsPath[512];
		GetAssetsPath(assetsPath, _countof(assetsPath));
		std::wstring res = assetsPath;
		return res;
	}
	std::wstring get_asset_path(std::wstring input) {
		return get_asset_path() + input;
	}
	void SetMousePosition(Vec3 vec3){
		POINT lp = { static_cast<int>(vec3.x),static_cast<int>(vec3.y) };
		ClientToScreen(YogWindow::get_instance()->MainWindow(), &lp);
		SetCursorPos(lp.x, lp.y);
	 }
}