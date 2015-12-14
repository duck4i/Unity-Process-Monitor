#pragma once
#include "Request.h"

class CopyOutputRequest : public Request
{
public:

	void Process(RequestInfo& info) override;
	void Completed(bool success, RequestInfo& info) override;


};

