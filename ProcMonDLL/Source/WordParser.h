#pragma once
#include "String.h"
#include <list>


class WordParser
{
public:

	WordParser()
	{
	}

	void Parse(const std::string& input, char token = '"')
	{
		if (input.length() < 2)
		{
			return;
		}

		m_words.clear();

		char buff[2000];

		const char* ptr = strchr(input.c_str(), token);
		while (ptr)
		{
			const char* nextPtr = strchr(ptr + 1, token);
			if (ptr)
			{
				if (nextPtr)
				{
					memset(buff, 0, sizeof(buff));
					strncpy(buff, ptr + 1, nextPtr - (ptr + 1));

					m_words.push_back(buff);

					ptr = strchr(nextPtr + 1, token);
				}
			}
		};
	}

	const std::list<std::string>& Words()
	{
		return m_words;
	}

private:

	std::list<std::string> m_words;
};