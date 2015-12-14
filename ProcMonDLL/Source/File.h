#pragma once
#include <Windows.h>
#include <string>
#include <Shlwapi.h>
#include "MD5.h"

class File
{
public:

	static bool Exists(const std::string& path)
	{
		return PathFileExistsA(path.c_str()) == TRUE;
	}

	static bool Copy(const std::string& path, const std::string& destination)
	{
		MakeDirectory(GetDirectory(destination));
		return CopyFileA(path.c_str(), destination.c_str(), false) == TRUE;
	}

	static bool Delete(const std::string& path)
	{
		return DeleteFileA(path.c_str()) == TRUE;
	}

	static std::string GetDirectory(const std::string& path)
	{
		std::string out = "";

		const char* ptr = path.c_str();
		char tmp[200];

		while (ptr)
		{
			const char* idx = strchr(ptr, '\\');
			if (!idx)
			{
				idx = strchr(ptr, '/');
			}
			if (idx)
			{
				memset(tmp, 0, sizeof(tmp));
				strncpy(tmp, ptr, idx - ptr);
				out += std::string(tmp) + std::string("\\");
				ptr = idx + 1;
			}
			else
			{
				ptr = 0;
			}
		}

		return out;
	}

	static std::string GetFilename(const std::string& path)
	{
		std::string dir = GetDirectory(path);
		if (dir.length())
		{
			return path.substr(dir.length(), dir.length() - path.length());
		}
		return path;
	}

	static void MakeDirectory(const std::string& path)
	{
		std::string out = "";
		const char* ptr = path.c_str();
		char tmp[200];

		while (ptr)
		{
			const char* idx = strchr(ptr, '\\');
			if (!idx)
			{
				idx = strchr(ptr, '/');
			}
			if (idx)
			{
				memset(tmp, 0, sizeof(tmp));
				strncpy(tmp, ptr, idx - ptr);

				out += std::string(tmp) + std::string("\\");

				CreateDirectoryA(out.c_str(), 0);

				ptr = idx + 1;
			}
			else
			{
				ptr = 0;
			}
		}
	}

	static std::string MD5(const std::string& path)
	{
		std::string out = "";

		MD5::MD5 md5;


		char* hash = md5.digestFile((char*)path.c_str());
		if (hash)
		{
			out = hash;
		}

		return out;
	}

};