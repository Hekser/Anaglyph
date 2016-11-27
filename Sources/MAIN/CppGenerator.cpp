#include "CppGenerator.h"

CppGenerator::CppGenerator()
{
	if ((cppLib = LoadLibrary("Anaglyph_CppDll.dll")) != NULL)
	{
		generate = (cppFunc)GetProcAddress(cppLib, "generate");

		if (generate == NULL)
		{
			cout << "Cpp func \"generate\" not found!" << endl;
			system("pause");
			exit(1);
		}
	}
	else
	{
		cout << "Cpp lib \"Anaglyph_CppDll\" not found!" << endl;
		system("pause");
		exit(1);
	}
}

CppGenerator::~CppGenerator()
{
	FreeLibrary(cppLib);
}