#pragma once 
#include <stdio.h>

class Hooker
{
public:

	static Hooker* Instance();

public:

	bool Initialize();

	bool Enable(bool enable);

	bool Shutdown();

private:

};