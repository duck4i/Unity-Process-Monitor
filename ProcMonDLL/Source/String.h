#pragma once
#include <string>

namespace String
{
	static std::string Quoted(const std::string& input)
	{
		auto quote = std::string("\"");
		return quote + input + quote;
	}

	static bool Equals(const std::string& a, const std::string& b)
	{
		return a.compare(b) == 0;
	}

	static bool Contains(const std::string& a, const std::string& search)
	{
		return a.find(search) != a.npos;
	}
};