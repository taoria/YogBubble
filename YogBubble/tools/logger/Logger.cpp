#include "Logger.h"

void Logger::close_level(Level level) {
	m_disable_toggle_map_[level] = true;
}

void Logger::open_level(Level level) {
	m_disable_toggle_map_[level] = false;
}
 std::wstring Logger::w_get_level_str(Level level) {
	switch (level) {
	case YOG_DEBUG:
		return L"Debug";
	case YOG_INFO:
		return L"Info";
	case YOG_WARN:
		return L"Warn";
	case YOG_ERROR:
		return L"Error";
	case YOG_FATAL:
		return L"Fatal";
	}
	return L"Unknown";
}

 std::string Logger::get_level_str(Level level) {
	switch (level) {
	case YOG_DEBUG:
		return "Debug";
	case YOG_INFO:
		return "Info";
	case YOG_WARN:
		return "Warn";
	case YOG_ERROR:
		return "Error";
	case YOG_FATAL:
		return "Fatal";
	}
	return "Unknown";
}

void Logger::log(std::wstring log_info, Level level) {
}

 void Logger::log(std::string log_info, Level level) {
}

void Logger::log_format(Level level, const wchar_t* log_format, ...) {
}

void Logger::log_format(Level level, const char* log_format, ...) {
}

 void Logger::hint(std::string hint_info, Level level) {
}
void Logger::hint(std::wstring hint_info, Level level) {
}

Logger::Logger() {
}