#pragma once
#include <exception>
#include "../../stdafx.h"
#include <string>
#include <map>
#include "../../yogcore/Event/InfoWrapper.h"

struct IYog;

enum Level {YOG_DEBUG, YOG_INFO, YOG_WARN,YOG_ERROR, YOG_FATAL};
#define CONSOLE_LOGGER 1
#define BOX_HINTER 2
#define ENGINE 1
#define GAME 2
class YOG_DLL_EXPORT Logger {
protected:
	std::map<Level, bool> m_disable_toggle_map_;
	virtual std::wstring w_get_level_str(Level level);
	virtual std::string get_level_str(Level level);
public:
	virtual ~Logger() = default;
	/**
	 * \brief 
	 * \param log_info 
	 * \param level 
	 */
	virtual void log(std::wstring log_info, Level level);
	virtual void log(std::string log_info, Level level) ;
	virtual void log_format(Level level, const wchar_t* log_format, ...) ;
	virtual void log_format(Level level, const char* log_format, ...);
	virtual auto hint(std::string hint_info, Level level) -> void;
	virtual void hint(std::wstring hint_info, Level level);
	virtual void close_level(Level level);
	virtual void open_level(Level level);
	Logger();

};


// class YogDebugger {
// protected:
//
// 	const static UINT DEBUG_MAX_INFO_SIZE = 128;
// 	static void debug_message_box(std::wstring str) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		MessageBox(nullptr, str.c_str(), L"info", 0);
// #endif
// 	}
// 	static void debug_message_console(std::wstring str) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		wprintf(L"message : %s\n", str.c_str());
// #endif
// 	}
// 	static void debug_error_box(std::wstring info) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		MessageBox(nullptr, info.c_str(), L"Error", 0);
// #endif
// 	}
// 	static void debug_error_console(std::wstring str) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		wprintf(L"Error : %s\n", str.c_str());
// #endif
// 	}
// 	static void debug_last_error_box(std::wstring hint) {
// 		MessageBox(nullptr, (hint + std::to_wstring(GetLastError())).c_str(), L"Error", 0);
// 	}
// 	static void debug_last_error_console(std::wstring hint) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		wprintf(L"Error  %s happens ,code : %d\n", hint.c_str(),GetLastError());
// #endif
// 	}
//
// public:
// 	static void debug_result_info(HRESULT hr) {
// #if defined(DEBUG) || defined(_DEBUG)
// 		switch (LOG_TARGET) {
// 		case DEBUG_LOG_TARGET_MESSAGE_BOX: {
// 			wchar_t buffer[DEBUG_MAX_INFO_SIZE];
// 			wsprintf(buffer, L"ERROR CODE : %X", hr);
// 			MessageBox(nullptr, buffer, L"ERROR", 0);
// 		}
// 		case DEBUG_LOG_TARGET_CONSOLE: {
// 			printf("error code %X\n", hr);
// 			break;
// 		}
// 		}
// #endif
// 	}
// 	static void throw_if_failed(HRESULT hr){
// 		if (FAILED(hr)){
//
// 			throw std::exception();
// 		}
// 	}
// 	static void debug_message(std::wstring str) {
// #if defined(DEBUG_LOG_TARGET_CONSOLE)
// 			debug_message_box(str);
// #endif
// #if defined(DEBUG_LOG_TARGET_MESSAGE_BOX)
// 			debug_message_console(str);
// #endif
// 	}
// 	static void debug_last_error(std::wstring str) {
// #if defined(DEBUG_LOG_TARGET_CONSOLE)
// 			debug_last_error_console(str);
// #endif
// #if defined(DEBUG_LOG_TARGET_MESSAGE_BOX)
// 			debug_last_error_box(str);
// #endif
// 	}
// 	static void debug_error(std::wstring str) {
// #if defined(DEBUG_LOG_TARGET_CONSOLE)
// 		debug_error_console(str);
// #endif
// #if defined(DEBUG_LOG_TARGET_MESSAGE_BOX)
// 		debug_error_box(str);
// #endif
// 	}
// 	static void message_box(std::wstring str, std::wstring cap) {
// 		MessageBox(nullptr, str.c_str(), cap.c_str(), 0);
// 	}
// 	static void message_box(LPCWSTR str, LPCWSTR cap) {
// 		MessageBox(nullptr, str, cap, 0);
// 	}
// 	static void console_write(std::wstring str) {
// 		wprintf(L" %s", str.c_str());
// 	}
// 	static void message_error_box(std::wstring str) {
// 		message_box(str, L"Error");
// 	}
// 	static void message_error_console(std::wstring str) {
// 		message_box(str, L"Error");
// 	}
//
// };

