#include "AsmGenerator.h"

AsmGenerator::AsmGenerator() {
	if ((asmLib = LoadLibrary("Anaglyph_AsmDll.dll")) != NULL) {
		generate = (asmFunc)GetProcAddress(asmLib, "generate");

		if (generate == NULL) {
			cout << "Asm proc \"generate\" not found!" << endl;
			system("pause");
			exit(1);
		}
	} else {
		cout << "Asm lib \"Anaglyph_AsmDll\" not found!" << endl;
		system("pause");
		exit(1);
	}
}

AsmGenerator::~AsmGenerator() {
	FreeLibrary(asmLib);
}