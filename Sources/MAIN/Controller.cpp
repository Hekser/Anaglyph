#include "Controller.h"

Controller::Controller() :
	appView(new AppView()),
	openFileDialog(new OpenFileDialog()),
	asmGenerator(new AsmGenerator()),
	cppGenerator(new CppGenerator()),
	threads(NULL),
	leftPic(NULL),
	rightPic(NULL)
{

}

Controller::~Controller()
{
	delete this->appView;
	this->appView = NULL;
	delete this->openFileDialog;
	this->openFileDialog = NULL;
	delete this->asmGenerator;
	this->asmGenerator = NULL;
	delete this->cppGenerator;
	this->cppGenerator = NULL;
	delete [] this->threads;
	this->threads = NULL;
	delete this->leftPic;
	this->leftPic = NULL;
	delete this->rightPic;
	this->rightPic = NULL;
}

void Controller::launch()
{
	RenderWindow generatorWindow(VideoMode(appView->getScreenWidth(), appView->getScreenHeight()), "Anaglyph generator", Style::Close);
	appView->setIcon(generatorWindow);

	Event event;
	String inputString;
	AppView::ButtonID buttonID;
	bool mouseClicked;

	string leftPicPath;
	string rightPicPath;
	bool gateLeftPic = false;
	bool gateRightPic = false;
	bool dllSwitch = true;

	while (generatorWindow.isOpen())
	{
		mouseClicked = false;

		while (generatorWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				generatorWindow.close();
			}
			else if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == 8 && inputString.getSize() > 0)
				{
					inputString.erase(inputString.getSize() - 1, inputString.getSize());
				}
				else if (event.text.unicode >= 48 && event.text.unicode <= 57)
				{
					if (inputString.getSize() <= 1)
					{
						inputString += static_cast<char>(event.text.unicode);
					}
				}

				appView->setString(inputString);
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					mouseClicked = true;
				}
			}
		}

		buttonID = appView->buttonAction(Mouse::getPosition(generatorWindow), mouseClicked);

		switch (buttonID)
		{
		case AppView::ButtonID::bLEFT:
			if (openFileDialog->ShowDialog())
			{
				leftPicPath = openFileDialog->getFileName();
				appView->setPic(leftPicPath, AppView::ButtonID::bLEFT);
				gateLeftPic = true;
			}
			break;
		case AppView::ButtonID::bRIGHT:
			if (openFileDialog->ShowDialog())
			{
				rightPicPath = openFileDialog->getFileName();
				appView->setPic(rightPicPath, AppView::ButtonID::bRIGHT);
				gateRightPic = true;
			}
			break;
		case AppView::ButtonID::bGENERATE:
			if (gateLeftPic && gateRightPic && appView->areInputImagesEqual())
			{
				appView->setPic(generate(appView->getThreadsNumber(), leftPicPath, rightPicPath, dllSwitch), AppView::ButtonID::bGENERATE);
			}
			break;
		case AppView::ButtonID::bASM:
			dllSwitch = true;
			break;
		case AppView::ButtonID::bCPP:
			dllSwitch = false;
			break;
		}

		appView->draw(generatorWindow);
	}
}

string Controller::generate(unsigned threadsNumber, string leftPath, string rightPath, bool dllSwitch)
{
	threads = new thread[threadsNumber];

	leftPic = new BitMap(leftPath);
	rightPic = new BitMap(rightPath);

	if (threadsNumber > 0)
	{
		leftPic->splitInto(threadsNumber);
		rightPic->splitInto(threadsNumber);
	}

	Clock clock;

	if (threadsNumber == 0)
	{
		if (!dllSwitch)
		{
			cppGenerator->generate(leftPic->getData(), rightPic->getData(), leftPic->getWidth(), leftPic->getHeight());
		}
		else
		{
			asmGenerator->generate(leftPic->getData(), rightPic->getData(), leftPic->getWidth(), leftPic->getHeight());
		}
	}
	else
	{
		if (!dllSwitch)
		{
			for (unsigned i = 0; i < threadsNumber; ++i)
			{
				threads[i] = thread(cppGenerator->generate, leftPic->getSplitData(i), rightPic->getSplitData(i), leftPic->getWidth(), leftPic->getSplitDataHeight(i));
			}
		}
		else
		{
			for (unsigned i = 0; i < threadsNumber; ++i)
			{
				threads[i] = thread(asmGenerator->generate, leftPic->getSplitData(i), rightPic->getSplitData(i), leftPic->getWidth(), leftPic->getSplitDataHeight(i));
			}
		}

		for (unsigned i = 0; i < threadsNumber; ++i)
		{
			threads[i].join();
		}
	}

	appView->showTime(clock.getElapsedTime().asMilliseconds());

	leftPic->saveToFile("result.bmp");

	delete [] this->threads;
	this->threads = NULL;
	delete this->leftPic;
	this->leftPic = NULL;
	delete this->rightPic;
	this->rightPic = NULL;

	return "result.bmp";
}