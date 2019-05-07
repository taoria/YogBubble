#pragma once

#include "../../stdafx.h"
#include <map>
#include "Logger.h"
#include <cstdarg>

class YOG_DLL_EXPORT ConsoleLogger : public Logger{
protected:
	static ConsoleLogger *instance;
	Level currentSeverityLevel;
public:
	static ConsoleLogger* get_instance() {
		if(instance==nullptr) {
			return instance = new ConsoleLogger;
		}
		return instance;
	}
	ConsoleLogger();
	ConsoleLogger& ChangeSeverityLevel(Level level);
	void log(std::wstring log_info, Level level) override;
	void log(Level level, std::wstring log_info);
	void hint(std::wstring hint_info, Level level) override;

	void log(std::string log_info, Level level) override;
	void hint(std::string hint_info, Level level) override;

	void log_format(Level level, const wchar_t* log_format, ...) override;
	void log_format(Level level, const char* log_format, ...) override;
	~ConsoleLogger();
	Logger& operator<<(std::string info);
	Logger& operator<<(std::wstring info);
	Logger& operator<<(IYog* iYog);
};

