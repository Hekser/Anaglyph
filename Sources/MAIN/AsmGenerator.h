#pragma once
#include "AppView.h"

class AsmGenerator
{
public:
	AsmGenerator();
	~AsmGenerator();
private:
	typedef void(*asmFunc)(unsigned char*, unsigned char*, int, int);
	HMODULE asmLib;
public:
	asmFunc generate;
};