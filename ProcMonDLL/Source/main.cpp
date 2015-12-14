#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ProcMon.h"
#include "Logger.h"

#include <list>
#include "String.h"
#include "WordParser.h"
#include "InputParams.h"
#include "File.h"

#include <atlenc.h>

void PM_Test()
{
	USES_CONVERSION;

	STARTUPINFO si;
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;

	//CreateProcess(TEXT("AppName.exe"), TEXT("cmd.exe -c etcfastperceptual | YEY 2 "), NULL, NULL, false, 0, NULL, TEXT(""), &si, &pi);

	std::string mp = "\"C:\\Program Files\\Unity\\Editor\\Data\\Tools\\PVRTexTool.exe\" \"-flip\" \"y\" \"-f\" \"ETC1\" \"-q\" \"etcfastperceptual\" \"-i\" \"Temp\\44f243b4c20a1df48aad2713de0e126d-feed.png\" \"-o\" \"Temp\\44f243b4c20a1df48aad2713de0e126d-res.pvr\"";

	CreateProcess(TEXT("AppName.exe"), A2W(mp.c_str()), NULL, NULL, false, 0, NULL, TEXT(""), &si, &pi);
}

void TestParsers()
{
	std::list<std::string> params;
	params.push_back(String::Quoted("c\\Program Files\\"));
	params.push_back(String::Quoted("-f"));
	params.push_back(String::Quoted("ETC1"));
	params.push_back(String::Quoted("-q"));
	params.push_back(String::Quoted("etcfast"));

	std::string input = "";
	for (auto s : params)
	{
		input += s + std::string(" ");
	}

	
	std::string mp = "\"C:\\Program Files\\Unity\\Editor\\Data\\Tools\\PVRTexTool.exe\" \"-flip\" \"y\" \"-f\" \"ETC1\" \"-q\" \"etcfast\" \"-i\" \"Temp\\44f243b4c20a1df48aad2713de0e126d-feed.png\" \"-o\" \"Temp\\44f243b4c20a1df48aad2713de0e126d-res.pvr\"";

	InputParams ip(mp);
	std::string appName = ip.GetParam("");
	std::string inputName = ip.GetParam("-i");
	std::string outputName = ip.GetParam("-o");
	std::string quality = ip.GetParam("-q");
	std::string type = ip.GetParam("-f");

	bool isPvr = String::Contains(mp, "PVRTexTool2.exe");

	if (File::Exists(inputName))
	{
		std::string dest = "Cache\\" + inputName;

		if (File::Copy(inputName, dest))
		{

			bool ok = true;
		}
	}

	std::string md5 = File::MD5(inputName);

}

int main(int argc, const char* argv[])
{
	Logger::Log("Test monitor");


	//TestParsers();

	PM_Test();
	if (PM_Create())
	{
		//PM_SetOutputDirectory("./");

		PM_Test();

		PM_Enable(true);

		PM_Test();

		PM_Enable(false);

		PM_Test();

		PM_Destroy();
	}

 	system("pause");
	return 0;
}