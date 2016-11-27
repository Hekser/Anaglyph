#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>

class OpenFileDialog
{
public:
	OpenFileDialog();
	~OpenFileDialog();
	bool ShowDialog();
	TCHAR *getFileName();
private:
	TCHAR *DefaultExtension;
	TCHAR *FileName;
	TCHAR *Filter;
	int FilterIndex;
	int Flags;
	TCHAR *InitialDir;
	HWND Owner;
	TCHAR *Title;
};