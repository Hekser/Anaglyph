#include "OpenFileDialog.h"

OpenFileDialog::OpenFileDialog()
{
	this->DefaultExtension = NULL;
	this->FileName = new TCHAR[MAX_PATH];
	this->Filter = "BitMap Files (*bmp)\0*.bmp\0";
	this->FilterIndex = 1000;
	this->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	this->InitialDir = NULL;
	this->Owner = NULL;
	this->Title = NULL;
}

OpenFileDialog::~OpenFileDialog()
{
	delete this->FileName;
	this->FileName = NULL;
}

bool OpenFileDialog::ShowDialog()
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = this->Owner;
	ofn.lpstrDefExt = this->DefaultExtension;
	ofn.lpstrFile = this->FileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = this->Filter;
	ofn.nFilterIndex = this->FilterIndex;
	ofn.lpstrInitialDir = this->InitialDir;
	ofn.lpstrTitle = this->Title;
	ofn.Flags = this->Flags;

	GetOpenFileName(&ofn);

	if (_tcslen(this->FileName) == 0)
	{
		return false;
	}

	return true;
}

TCHAR * OpenFileDialog::getFileName()
{
	return this->FileName;
}