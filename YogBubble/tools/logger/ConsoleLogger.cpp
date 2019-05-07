#include "ConsoleLogger.h"
#include <ctime>
#include "../helper.h"
#include "../../stdafx.h"
#pragma warning(disable:4996)
ConsoleLogger* ConsoleLogger::instance = nullptr;
ConsoleLogger::ConsoleLogger(){}

std::string getTime(){
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}
ConsoleLogger& ConsoleLogger::ChangeSeverityLevel(Level level){
	this->currentSeverityLevel = level;
	return *this;
}
void ConsoleLogger::log(std::wstring log_info, Level level){
	if (!m_disable_toggle_map_[level]){
		if (level == YOG_DEBUG){
			wchar_t buffer[128];
			wsprintf(buffer, L"%s:%s\n", this->w_get_level_str(level).c_str(), log_info.c_str());
			OutputDebugString(buffer);
		}
		wprintf(L"%s---%s:%s\n", YogString::s2ws(getTime()).c_str(), this->w_get_level_str(level).c_str(), log_info.c_str());
	}

}

void ConsoleLogger::log(Level level, std::wstring log_info){
	log(log_info, level);
}

void ConsoleLogger::hint(std::wstring hint_info, Level level){}

void ConsoleLogger::log(std::string log_info, Level level){
	if (!m_disable_toggle_map_[level])
		printf("%s---%s:%s\n", getTime().c_str(),this->get_level_str(level).c_str(), log_info.c_str());

}

void ConsoleLogger::hint(std::string hint_info, Level level){}

void ConsoleLogger::log_format(Level level, const wchar_t* log_format, ...){

	if (!m_disable_toggle_map_[level]){
		std::wstring form;
		form += YogString::s2ws(getTime())+L"---";
		form += w_get_level_str(level) + L":";
		form += log_format;
		form += L"\n";
		va_list arg_ptr;
		va_start(arg_ptr, log_format);
		if (level == YOG_DEBUG){
			wchar_t buffer[128];
			memset(buffer, 0, sizeof buffer);
			wvsprintf(buffer, form.c_str(), arg_ptr);
			OutputDebugString(buffer);
		}
		vwprintf(form.c_str(), arg_ptr);
		va_end(arg_ptr);
	}

}

void ConsoleLogger::log_format(Level level, const char* log_format, ...){
	if (!m_disable_toggle_map_[level]){
		std::string form;
		form += getTime()+"---";
		form += get_level_str(level) + ":";
		form += log_format;
		form += "\n";
		va_list arg_ptr;

		va_start(arg_ptr, log_format);

		vprintf(form.c_str(), arg_ptr);

		va_end(arg_ptr);


	}
}

ConsoleLogger::~ConsoleLogger(){}
Logger& ConsoleLogger::operator<<(std::string info){
	//log(Level,info);
	return *this;
}

Logger& ConsoleLogger::operator<<(std::wstring info){
	return *this;
}

Logger& ConsoleLogger::operator<<(IYog* iYog){
	return *this;
}
