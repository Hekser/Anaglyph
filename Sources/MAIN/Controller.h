#pragma once
#include "AppView.h"
#include "AsmGenerator.h"
#include "CppGenerator.h"
#include "OpenFileDialog.h"
#include "BitMap.h"

class Controller
{
public:
	Controller();
	~Controller();
	void launch();
private:
	AppView *appView;
	OpenFileDialog *openFileDialog;
	AsmGenerator *asmGenerator;
	CppGenerator *cppGenerator;
	thread *threads;

	BitMap *leftPic;
	BitMap *rightPic;
private:
	string generate(unsigned, string, string, bool);
};