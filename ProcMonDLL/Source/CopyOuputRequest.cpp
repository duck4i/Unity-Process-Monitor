#include "CopyOutputRequest.h"
#include "Logger.h"
#include "InputParams.h"
#include "RequestInfo.h"
#include "File.h"

void CopyOutputRequest::Process(RequestInfo& info)
{
	if (String::Contains(info.value, "PVRTexTool.exe"))
	{
		info.wait = true;
	}
}

void CopyOutputRequest::Completed(bool success, RequestInfo& info)
{
	Logger::Log("CopyOutputRequest:OnCompleted:Start");

	if (success)
	{
		InputParams params(info.value);
		std::string input  = params.GetParam("-i");
		std::string output = params.GetParam("-o");

		if (File::Exists(output))
		{
			std::string out = std::string("Cache\\") + File::MD5(input) + std::string("-") + File::GetFilename(output);

			if (File::Copy(output.c_str(), out))
			{
				Logger::Log("CopyFile success", out);
			}
			else
			{
				Logger::Log("Copy file fail", out);
			}
		}
	}

	Logger::Log("CopyOutputRequest:OnCompleted:End");
}