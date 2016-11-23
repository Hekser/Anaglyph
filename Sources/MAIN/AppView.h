#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class AppView {
public:
	enum ButtonID {
		NONE,
		bLEFT,
		bRIGHT,
		bGENERATE,
		bASM,
		bCPP
	};
	AppView();
	~AppView();
	unsigned getConcurentThreadsSupported();
	unsigned getScreenWidth();
	unsigned getScreenHeight();
	void setIcon(RenderWindow &);
	void draw(RenderWindow &);
	AppView::ButtonID buttonAction(const Vector2i, bool);
	void setPic(string, AppView::ButtonID);
	void showTime(Int32);
private:
	const unsigned concurentThreadsSupported;

	unsigned screenWidth;
	unsigned screenHeight;

	Image icon;
	Font font;
	Text textThreads;
	Text textDll;
	Text textTime;

	const Vector2f anaglyphSize;
	const Vector2f anaglyphPosition;

	const Vector2f leftPicSize;
	const Vector2f leftPicPosition;

	const Vector2f rightPicSize;
	const Vector2f rightPicPosition;

	const Vector2f resultPicSize;
	const Vector2f resultPicPosition;

	const Vector2f buttonSmallSize;
	const Vector2f buttonLEFTPosition;
	const Vector2f buttonRIGHTPosition;

	const Vector2f buttonBigSize;
	const Vector2f buttonGENERATEPosition;

	const Vector2f buttonDllSize;
	const Vector2f buttonASMPosition;
	const Vector2f buttonCPPPosition;

	RectangleShape backgroundLeft;
	RectangleShape backgroundRight;
	RectangleShape anaglyph;
	RectangleShape leftPic;
	RectangleShape rightPic;
	RectangleShape resultPic;
	RectangleShape buttonLEFT;
	RectangleShape buttonRIGHT;
	RectangleShape buttonGENERATE;
	RectangleShape buttonASM;
	RectangleShape buttonCPP;

	Texture backgroundLeftTexture;
	Texture backgroundRightTexture;
	Texture anaglyphTexture;
	Texture leftPicTexture;
	Texture rightPicTexture;
	Texture resultPicTexture;
	Texture buttonSmallTexture;
	Texture buttonOnSmallTexture;
	Texture buttonGENERATETexture;
	Texture buttonOnGENERATETexture;
	Texture buttonASMTexture;
	Texture buttonOnASMTexture;
	Texture buttonCPPTexture;
	Texture buttonOnCPPTexture;

	bool gateResultPic;
};