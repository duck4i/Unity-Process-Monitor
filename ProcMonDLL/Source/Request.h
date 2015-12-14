#pragma once
#include "RequestInfo.h"

class Request
{
public:

	virtual void Process(RequestInfo& request) {};

	virtual void Completed(bool success, RequestInfo& request) {};

};