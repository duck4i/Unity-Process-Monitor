#pragma once
#include <string>
#include <list>
#include "Request.h"
#include "RequestInfo.h"


class RequestManager
{
public:

	static RequestManager* Instance();
	
	~RequestManager();

	void ProcessRequest(RequestInfo& info);

	void RequestCompleted(bool success, RequestInfo& info);

private:

	RequestManager();

	std::list<Request*> m_requests;
};
