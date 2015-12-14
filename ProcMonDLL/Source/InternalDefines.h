#pragma once
#include <Windows.h>

//	DEFINITIONS
typedef
BOOL
(WINAPI
*PtrCreateProcessA)(
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
);

typedef
BOOL
(WINAPI
*PtrCreateProcessW)(
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
);