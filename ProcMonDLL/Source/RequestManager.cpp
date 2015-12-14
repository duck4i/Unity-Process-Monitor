#include "RequestManager.h"
#include "String.h"
#include "File.h"
#include "QualitySettingRequest.h"
#include "CopyOutputRequest.h"
#include "Logger.h"

RequestManager::RequestManager()
{
	m_requests.push_back(new QualitySettingRequest());
	m_requests.push_back(new CopyOutputRequest());
}

RequestManager::~RequestManager()
{
	for (auto r : m_requests)
	{
		delete r;
	}
	m_requests.clear();
}

RequestManager* RequestManager::Instance()
{
	static RequestManager manager;
	return &manager;
}

void RequestManager::ProcessRequest(RequestInfo& info)
{
	for (Request* request : m_requests)
	{
		request->Process(info);
	}
}

void RequestManager::RequestCompleted(bool success, RequestInfo& info)
{
	for (Request* request : m_requests)
	{
		request->Completed(success, info);
	}
}