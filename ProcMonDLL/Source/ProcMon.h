#include <Windows.h>

#define DLLEXPORT __declspec(dllexport)

extern "C"
{

	DLLEXPORT bool PM_Create();
	DLLEXPORT bool PM_Destroy();
	DLLEXPORT bool PM_Enable(bool enable);

}