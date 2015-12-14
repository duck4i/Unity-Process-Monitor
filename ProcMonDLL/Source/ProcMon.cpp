#include "ProcMon.h"
#include "Hooker.h"

//	EXPORTED API CALLS
DLLEXPORT bool PM_Create()
{
	return Hooker::Instance()->Initialize();
}

DLLEXPORT bool PM_Destroy()
{
	return Hooker::Instance()->Shutdown();
}

DLLEXPORT bool PM_Enable(bool enable)
{
	return Hooker::Instance()->Enable(enable);
}