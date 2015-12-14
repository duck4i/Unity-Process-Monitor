#pragma once
#include "WordParser.h"

class InputParams
{
public:

	InputParams(const std::string& input)
	{
		m_wParser.Parse(input);
	}

	std::string GetParam(const std::string& name)
	{
		std::string lastOne = "";
		for (auto value : m_wParser.Words())
		{
			if (String::Equals(lastOne, name))
			{
				return value;
			}
			lastOne = value;
		}
		return std::string();
	}

private:

	WordParser m_wParser;
};