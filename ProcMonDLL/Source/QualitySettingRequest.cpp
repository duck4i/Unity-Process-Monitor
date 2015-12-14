#include "QualitySettingRequest.h"
#include "RequestInfo.h"
#include "Logger.h"

void QualitySettingRequest::Process(RequestInfo& info)
{
	Logger::Log("QualitySettingRequest:OnProcess:Start");

	size_t index = info.value.find("etcfastperceptual");
	if (index != info.value.npos)
	{
		info.value.replace(index, 17, "etcfast");
		Logger::Log("Patching ETC ....");
		Logger::Log(info.value.c_str());

		info.modified = true;
	}

	index = info.value.find("pvrtcnormal");
	if (index != info.value.npos)
	{
		info.value.replace(index, 11, "pvrtcfastest");
		Logger::Log("Patching PVRTC ....");
		Logger::Log(info.value.c_str());

		info.modified = true;
	}

	Logger::Log("QualitySettingRequest:OnProcess:End");
}