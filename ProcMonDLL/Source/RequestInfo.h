#pragma once
#include <string>

struct RequestInfo
{
	/* Input value */
	std::string value;

	/* Should cancel this request */
	bool cancel;

	/* Input value was modified */
	bool modified;

	/* Wait for the process to complete */
	bool wait;

	RequestInfo()
	{
		cancel = false;
		modified = false;
		wait = false;
	}
};