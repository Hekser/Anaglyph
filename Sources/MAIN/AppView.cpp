#include "AppView.h"

AppView::AppView() :
	concurentThreadsSupported(thread::hardware_concurrency()),
	screenWidth((unsigned)(VideoMode::getDesktopMode().width * 0.75)),
	screenHeight((unsigned)(VideoMode::getDesktopMode().height * 0.75)),

	backgroundLeft(Vector2f(screenWidth * 0.4f, (float)screenHeight)),
	backgroundRight(Vector2f(screenWidth * 0.6f, (float)screenHeight)),

	anaglyphSize(screenWidth * 0.3f, screenHeight * 0.15f),
	anaglyphPosition(screenWidth * 0.05f, screenHeight * 0.1f),
	anaglyph(anaglyphSize),

	leftPicSize(screenWidth * 0.2f, screenHeight * 0.25f),
	leftPicPosition(screenWidth * 0.475f, screenHeight * 0.1f),
	leftPic(leftPicSize),

	rightPicSize(screenWidth * 0.2f, screenHeight * 0.25f),
	rightPicPosition(screenWidth * 0.725f, screenHeight * 0.1f),
	rightPic(rightPicSize),

	resultPicSize(screenWidth * 0.4f, screenHeight * 0.425f),
	resultPicPosition(screenWidth * 0.5f, screenHeight * 0.465f),
	resultPic(resultPicSize),

	buttonSmallSize(screenWidth * 0.06f, screenHeight * 0.04f),
	buttonLEFTPosition(screenWidth * 0.55f, screenHeight * 0.37f),
	buttonRIGHTPosition(screenWidth * 0.8f, screenHeight * 0.37f),
	buttonLEFT(buttonSmallSize),
	buttonRIGHT(buttonSmallSize),

	buttonBigSize(screenWidth * 0.125f, screenHeight * 0.06f),
	buttonGENERATEPosition(screenWidth * 0.64f, screenHeight * 0.91f),
	buttonGENERATE(buttonBigSize),

	buttonDllSize(screenWidth * 0.075f, screenHeight * 0.075f),		//
	buttonASMPosition(screenWidth * 0.1f, screenHeight * 0.575f),		//
	buttonCPPPosition(screenWidth * 0.225f, screenHeight * 0.575f),		//
	buttonASM(buttonDllSize),
	buttonCPP(buttonDllSize),

	gateResultPic(false)
{
	if (!icon.loadFromFile("textures\\logo.png")) {
		system("pause");
		exit(1);
	}

	if (!font.loadFromFile("textures\\sansation.ttf")) {
		system("pause");
		exit(1);
	}

	if (!backgroundLeftTexture.loadFromFile("textures\\background.png")) {
		system("pause");
		exit(1);
	}

	if (!backgroundRightTexture.loadFromFile("textures\\background.png")) {
		system("pause");
		exit(1);
	}

	if (!anaglyphTexture.loadFromFile("textures\\anaglyph.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonSmallTexture.loadFromFile("textures\\load.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonOnSmallTexture.loadFromFile("textures\\loadOn.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonGENERATETexture.loadFromFile("textures\\generate.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonOnGENERATETexture.loadFromFile("textures\\generateOn.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonASMTexture.loadFromFile("textures\\asm.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonOnASMTexture.loadFromFile("textures\\asmOn.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonCPPTexture.loadFromFile("textures\\cpp.png")) {
		system("pause");
		exit(1);
	}

	if (!buttonOnCPPTexture.loadFromFile("textures\\cppOn.png")) {
		system("pause");
		exit(1);
	}

	textThreads.setFont(font);
	textThreads.setColor(Color::Black);
	textThreads.setString("Your computer has " + to_string(concurentThreadsSupported) + " threads.");
	textThreads.setPosition(screenWidth * 0.05f, screenHeight * 0.3f);

	textDll.setFont(font);
	textDll.setColor(Color::Black);
	textDll.setString("Choose dll:");
	textDll.setPosition(screenWidth * 0.05f, screenHeight * 0.5f);

	textTime.setFont(font);
	textTime.setColor(Color::Black);
	textTime.setPosition(screenWidth * 0.05f, screenHeight * 0.9f);

	backgroundLeft.setTexture(&backgroundLeftTexture);
	backgroundLeft.setPosition(0, 0);

	backgroundRight.setTexture(&backgroundRightTexture);
	backgroundRight.setPosition(screenWidth * 0.4f, 0);

	anaglyph.setTexture(&anaglyphTexture);
	anaglyph.setPosition(anaglyphPosition);

	leftPic.setPosition(leftPicPosition);
	leftPic.setFillColor(Color(255, 255, 255, 90));
	leftPic.setOutlineColor(Color(100, 100, 100));
	leftPic.setOutlineThickness(screenWidth * 0.002172f);

	rightPic.setPosition(rightPicPosition);
	rightPic.setFillColor(Color(255, 255, 255, 90));
	rightPic.setOutlineColor(Color(100, 100, 100));
	rightPic.setOutlineThickness(screenWidth * 0.002172f);

	resultPic.setPosition(resultPicPosition);
	resultPic.setFillColor(Color(255, 255, 255, 90));
	resultPic.setOutlineColor(Color(100, 100, 100));
	resultPic.setOutlineThickness(screenWidth * 0.002172f);

	buttonLEFT.setTexture(&buttonSmallTexture);
	buttonLEFT.setPosition(buttonLEFTPosition);

	buttonRIGHT.setTexture(&buttonSmallTexture);
	buttonRIGHT.setPosition(buttonRIGHTPosition);

	buttonGENERATE.setTexture(&buttonGENERATETexture);
	buttonGENERATE.setPosition(buttonGENERATEPosition);

	buttonASM.setTexture(&buttonOnASMTexture);
	buttonASM.setPosition(buttonASMPosition);

	buttonCPP.setTexture(&buttonCPPTexture);
	buttonCPP.setPosition(buttonCPPPosition);
}

AppView::~AppView() {

}

unsigned AppView::getConcurentThreadsSupported() {
	return this->concurentThreadsSupported;
}

unsigned AppView::getScreenWidth() {
	return this->screenWidth;
}

unsigned AppView::getScreenHeight() {
	return this->screenHeight;
}

void AppView::setIcon(RenderWindow &renderWindow) {
	renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void AppView::draw(RenderWindow &renderWindow) {
	renderWindow.clear(Color::White);
	renderWindow.draw(backgroundLeft);
	renderWindow.draw(backgroundRight);
	renderWindow.draw(anaglyph);
	renderWindow.draw(leftPic);
	renderWindow.draw(rightPic);
	renderWindow.draw(resultPic);
	renderWindow.draw(buttonLEFT);
	renderWindow.draw(buttonRIGHT);
	renderWindow.draw(buttonGENERATE);
	renderWindow.draw(buttonASM);
	renderWindow.draw(buttonCPP);
	renderWindow.draw(textThreads);
	renderWindow.draw(textDll);
	renderWindow.draw(textTime);
	renderWindow.display();
}

AppView::ButtonID AppView::buttonAction(const Vector2i mousePosition, bool mouseClicked)
{
	if (mousePosition.x >= buttonLEFTPosition.x && mousePosition.y >= buttonLEFTPosition.y && mousePosition.x <= (buttonLEFTPosition.x + buttonSmallSize.x) && mousePosition.y <= (buttonLEFTPosition.y + buttonSmallSize.y)) {
		buttonLEFT.setTexture(&buttonOnSmallTexture);
		buttonRIGHT.setTexture(&buttonSmallTexture);
		buttonGENERATE.setTexture(&buttonGENERATETexture);
		resultPic.setOutlineColor(Color(100, 100, 100));
		resultPic.setOutlineThickness(screenWidth * 0.002172f);

		if (mouseClicked) {
			return AppView::ButtonID::bLEFT;
		}
	} else if (mousePosition.x >= buttonRIGHTPosition.x && mousePosition.y >= buttonRIGHTPosition.y && mousePosition.x <= (buttonRIGHTPosition.x + buttonSmallSize.x) && mousePosition.y <= (buttonRIGHTPosition.y + buttonSmallSize.y)) {
		buttonRIGHT.setTexture(&buttonOnSmallTexture);
		buttonLEFT.setTexture(&buttonSmallTexture);
		buttonGENERATE.setTexture(&buttonGENERATETexture);
		resultPic.setOutlineColor(Color(100, 100, 100));
		resultPic.setOutlineThickness(screenWidth * 0.002172f);

		if (mouseClicked) {
			return AppView::ButtonID::bRIGHT;
		}
	} else if (mousePosition.x >= buttonGENERATEPosition.x && mousePosition.y >= buttonGENERATEPosition.y && mousePosition.x <= (buttonGENERATEPosition.x + buttonBigSize.x) && mousePosition.y <= (buttonGENERATEPosition.y + buttonBigSize.y)) {
		buttonGENERATE.setTexture(&buttonOnGENERATETexture);
		buttonLEFT.setTexture(&buttonSmallTexture);
		buttonRIGHT.setTexture(&buttonSmallTexture);
		resultPic.setOutlineColor(Color(100, 100, 100));
		resultPic.setOutlineThickness(screenWidth * 0.002172f);

		if (mouseClicked) {
			return AppView::ButtonID::bGENERATE;
		}
	} else if (gateResultPic && (mousePosition.x >= resultPicPosition.x && mousePosition.y >= resultPicPosition.y && mousePosition.x <= (resultPicPosition.x + resultPicSize.x) && mousePosition.y <= (resultPicPosition.y + resultPicSize.y))) {
		buttonLEFT.setTexture(&buttonSmallTexture);
		buttonRIGHT.setTexture(&buttonSmallTexture);
		buttonGENERATE.setTexture(&buttonGENERATETexture);
		resultPic.setOutlineColor(Color(46, 73, 250));
		resultPic.setOutlineThickness(screenWidth * 0.004172f);

		if (mouseClicked) {
			RectangleShape pic(Vector2f((float)VideoMode::getDesktopMode().width, (float)VideoMode::getDesktopMode().height));
			pic.setTexture(&resultPicTexture);

			RenderWindow renderWindow(VideoMode::getDesktopMode(), "3D", Style::Fullscreen);
			Event event;
			while (renderWindow.isOpen()) {
				while (renderWindow.pollEvent(event)) {
					if (event.type == Event::MouseButtonPressed) {
						renderWindow.close();
					}
				}
				renderWindow.clear(Color::White);
				renderWindow.draw(pic);
				renderWindow.display();
			}
		}
	} else if (mousePosition.x >= buttonASMPosition.x && mousePosition.y >= buttonASMPosition.y && mousePosition.x <= (buttonASMPosition.x + buttonDllSize.x) && mousePosition.y <= (buttonASMPosition.y + buttonDllSize.y)) {

		if (mouseClicked) {
			buttonASM.setTexture(&buttonOnASMTexture);
			buttonCPP.setTexture(&buttonCPPTexture);
			return AppView::ButtonID::bASM;
		}
	} else if (mousePosition.x >= buttonCPPPosition.x && mousePosition.y >= buttonCPPPosition.y && mousePosition.x <= (buttonCPPPosition.x + buttonDllSize.x) && mousePosition.y <= (buttonCPPPosition.y + buttonDllSize.y)) {

		if (mouseClicked) {
			buttonASM.setTexture(&buttonASMTexture);
			buttonCPP.setTexture(&buttonOnCPPTexture);
			return AppView::ButtonID::bCPP;
		}
	} else {
		buttonLEFT.setTexture(&buttonSmallTexture);
		buttonRIGHT.setTexture(&buttonSmallTexture);
		buttonGENERATE.setTexture(&buttonGENERATETexture);
		resultPic.setOutlineColor(Color(100, 100, 100));
		resultPic.setOutlineThickness(screenWidth * 0.002172f);
	}

	return AppView::ButtonID::NONE;
}

void AppView::setPic(string path, AppView::ButtonID buttonID) {
	switch (buttonID) {
	case AppView::ButtonID::bLEFT:
		// to do: double pic load error
		if (!leftPicTexture.loadFromFile(path)) {
			system("pause");
			exit(1);
		}
		leftPic.setFillColor(Color(255, 255, 255, 255));
		leftPic.setTexture(&leftPicTexture);
		break;
	case AppView::ButtonID::bRIGHT:
		if (!rightPicTexture.loadFromFile(path)) {
			system("pause");
			exit(1);
		}
		rightPic.setFillColor(Color(255, 255, 255, 255));
		rightPic.setTexture(&rightPicTexture);
		break;
	case AppView::ButtonID::bGENERATE:
		if (!resultPicTexture.loadFromFile(path)) {
			system("pause");
			exit(1);
		}
		resultPic.setFillColor(Color(255, 255, 255, 255));
		resultPic.setTexture(&resultPicTexture);
		gateResultPic = true;
		break;	
	}
}

void AppView::showTime(Int32 time) {
	this->textTime.setString("Elapsed time: " + to_string(time) + " ms");
}