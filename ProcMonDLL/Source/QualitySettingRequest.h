#pragma once
#include "Request.h"

class QualitySettingRequest : public Request
{
public:

	void Process(RequestInfo& request) override;

};