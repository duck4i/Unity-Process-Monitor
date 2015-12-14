#pragma once
#include <string>

class Logger
{
public:

	Logger();
	~Logger();

	static Logger* Instance();		

	static void Log(const char* text);
	static void Log(const std::string& text) { Log(text.c_str()); }

	static void Log(const char* text, const char* text2);
	static void Log(const std::string& text, const std::string& text2) { Log(text.c_str(), text2.c_str()); }

private:

	FILE* m_file;

	void Open();
	void Close();

	void LogInternal(const char* text);
	void LogInternal(const char* text, const char* text2);

};