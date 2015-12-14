#include "Logger.h"

#define LOG_ENABLED

Logger* Logger::Instance()
{
	static Logger shared;
	return &shared;
}

Logger::Logger()
{
	m_file = NULL;

#ifdef LOG_ENABLED
	Open();
#endif
}

Logger::~Logger()
{
	Close();
}

void Logger::Log(const char* text)
{
	Instance()->LogInternal(text);
}

void Logger::Log(const char* text, const char* text2)
{
	Instance()->LogInternal(text, text2);
}

void Logger::LogInternal(const char* text, const char* text2)
{
#ifdef LOG_ENABLED

	char total[2000];
	sprintf(total, "%s %s", text, text2);

	LogInternal(total);

#endif
}

void Logger::LogInternal(const char* text)
{
#ifdef LOG_ENABLED

	//	Log to console
	printf("%s\r\n", text);

	//	Log to file
	fwrite(text, sizeof(char), strlen(text), m_file);

	//	Add newline
	char nl = '\n';
	fwrite(&nl, sizeof(char), 1, m_file);

	//	Flush
	fflush(m_file);
#endif
}

void Logger::Open()
{
	if (m_file == NULL)
	{
		m_file = fopen("ProcMonDLL.txt", "w");
	}
}

void Logger::Close()
{
	if (m_file)
	{
		fflush(m_file);
		fclose(m_file);
		m_file = NULL;
	}
}