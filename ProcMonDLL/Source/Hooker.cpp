#include "Hooker.h"
#include "../MinHook/MinHook.h"
#include "InternalDefines.h"
#include "Logger.h"
#include <string>
#include <algorithm>
#include "String.h"
#include "RequestManager.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "MinHook.x86.lib")
#endif

//	Texture performance
//	https://gist.github.com/zeux/77c9ef7703b621d992e0

PtrCreateProcessA g_origCreateProcessA = NULL;

//	HOOK IMPLEMENTATION
BOOL
WINAPI
ImpCreateProcessA(
_In_opt_ LPCSTR lpApplicationName,
_Inout_opt_ LPSTR lpCommandLine,
_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
_In_ BOOL bInheritHandles,
_In_ DWORD dwCreationFlags,
_In_opt_ LPVOID lpEnvironment,
_In_opt_ LPCSTR lpCurrentDirectory,
_In_ LPSTARTUPINFOA lpStartupInfo,
_Out_ LPPROCESS_INFORMATION lpProcessInformation
)
{
	Logger::Log("Woa multibyte one !:D");

	return g_origCreateProcessA(
		lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation
		);
}

//	UNICODE
PtrCreateProcessW g_origCreateProcessW = NULL;

#include <atlbase.h>


BOOL
WINAPI
ImpCreateProcessW(
_In_opt_ LPCWSTR lpApplicationName,
_Inout_opt_ LPWSTR lpCommandLine,
_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
_In_ BOOL bInheritHandles,
_In_ DWORD dwCreationFlags,
_In_opt_ LPVOID lpEnvironment,
_In_opt_ LPCWSTR lpCurrentDirectory,
_In_ LPSTARTUPINFOW lpStartupInfo,
_Out_ LPPROCESS_INFORMATION lpProcessInformation
)
{
	USES_CONVERSION;

	std::string cmdLine = lpCommandLine ? W2A(lpCommandLine) : "";

	Logger::Log("\nHooker::Hook New process:");
	Logger::Log(cmdLine.c_str());
	Logger::Log("");

	//	Process requests
	RequestInfo request;
	request.value = cmdLine;

	RequestManager::Instance()->ProcessRequest(request);

	if (request.cancel)
	{
		Logger::Log("Aborting by request...");
		return FALSE;
	}

	bool success = g_origCreateProcessW(
		lpApplicationName,
		request.modified ? A2W(request.value.c_str()) : lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation
		);

	if (request.wait)
	{
		Logger::Log("Waiting process...");
		WaitForSingleObject(lpProcessInformation->hProcess, INFINITE);
		Logger::Log("Process completed...");
	}

	//	Forward to processors
	RequestManager::Instance()->RequestCompleted(success, request);

	Logger::Log("");
	Logger::Log(success ? "Request executed OK!" : "Request FAILED!");

	return success;
}

Hooker* Hooker::Instance()
{
	static Hooker shared;
	return &shared;
}

bool Hooker::Initialize()
{
	MH_STATUS ms = MH_Initialize();
	if (ms == MH_OK)
	{
		do
		{
			//	Create hooks
			if (MH_CreateHook(&CreateProcessW, &ImpCreateProcessW, reinterpret_cast<LPVOID*>(&g_origCreateProcessW)) != MH_OK)
				break;
			if (MH_CreateHook(&CreateProcessA, &ImpCreateProcessA, reinterpret_cast<LPVOID*>(&g_origCreateProcessA)) != MH_OK)
				break;

			Logger::Log("Hooker::Initialize Complete!!!");

			return true;
		} while (false);
	}
	return false;
}

bool Hooker::Shutdown()
{
	Logger::Log("Hooker::Shutdown");

	return MH_Uninitialize() == MH_OK;
}

bool Hooker::Enable(bool enable)
{
	typedef MH_STATUS(WINAPI *HMET)(LPVOID);
	HMET method = enable ? MH_EnableHook : MH_DisableHook;

	Logger::Log(enable ? "Hooker::Enable(true)" : "Hooker::Enable(false)");

	do
	{
		if (method(&CreateProcessA) != MH_OK)
			break;
		if (method(&CreateProcessW) != MH_OK)
			break;

		return true;
	} while (false);


	return false;
}

