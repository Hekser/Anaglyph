#pragma once
#include "AppView.h"

class CppGenerator {
public:
	CppGenerator();
	~CppGenerator();
private:
	typedef void (*cppFunc)(unsigned char *, unsigned char *, int, int);
	HMODULE cppLib;
public:
	cppFunc generate;
};