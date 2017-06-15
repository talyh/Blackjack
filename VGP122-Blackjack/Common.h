#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <array>
#include <cstdlib>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>
#include "Size.h"

using namespace std;

#define SCREEN_WIDTH GameRender::SCREEN_WIDTH
#define SCREEN_HEIGHT GameRender::SCREEN_HEIGHT
#define CARD_WIDTH CARD_H::SIZE.width
#define CARD_HEIGHT CARD_H::SIZE.height

struct Position
{
	int xPos { 0 };
	int yPos { 0 };

	Position& Position::operator+= (const int rhs)
	{
		xPos += rhs;
		yPos += rhs;
		return *this;
	}
	friend Position operator+(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z += rhs;
		return z;
	}

	Position& Position::operator-= (const int rhs)
	{
		xPos -= rhs;
		yPos -= rhs;
		return *this;
	}
	friend Position operator-(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z -= rhs;
		return z;
	}

	Position& Position::operator*= (const int rhs)
	{
		xPos *= rhs;
		yPos *= rhs;
		return *this;
	}
	friend Position operator*(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z *= rhs;
		return z;
	}

	Position& Position::operator/= (const int rhs)
	{
		xPos /= rhs;
		yPos /= rhs;
		return *this;
	}
	friend Position operator/(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z /= rhs;
		return z;
	}
};

struct Textbox 
{
	string name { "" };
	Position position { 0, 0 }; 
	Size size { 0, 0 };
	string value { "" };
};

class Sprite;

struct Button
{
	string name { "" };
	Position position { 0, 0 };
	Size size { 0, 0 };
	string src { "" };
	Sprite* image{ nullptr };
	string sfxSrc { "" };
};

// define layout variables
const int LINE_HEIGHT{ 20 };
const int PADDING{ 20 };
const Size START_MENU_BUTTON_SIZE{ 383, 78 };


// protoype functions
void ListenForGameEvents(bool listening);
void LoadStartMenu();
void ShowInstructions();

// define constants
// visual
const string BACKGROUND_IMAGE = "imgs/background.png";
const string BTN_PLAY_IMAGE = "imgs/btnPlay.png";
const string BTN_INSTRUCTIONS_IMAGE = "imgs/btnInstructions.png";
const string BTN_QUIT_IMAGE = "imgs/btnQuit.png";
const string BTN_BET_UP_IMAGE = "imgs/btnBetUp.png";
const string BTN_BET_DOWN_IMAGE = "imgs/btnBetDown.png";
const string BTN_BET_CONFIRM_IMAGE = "imgs/btnBetConfirm.png";
const string CARDS_IMAGE = "imgs/cards.png";
// audio
const string MUSIC = "snds/music.mid";
const string SFX_BUTTON_CLICK = "snds/jump.wav";
const string SFX_START = "snds/";
const string SFX_BET = "sdns/";
const string SFX_HIT = "sdns/";
const string SFX_STAY = "sdns/";
const string SFX_SPLIT = "sdns/";
const string SFX_DOUBLE_DOWN = "sdns/";
const string SFX_RECEIVE_BET = "sdns/";
const string SFX_PAY_BET = "sdns/";
const string SFX_GAME_OVER = "sdns/";
// font
const string FONT = "fnts/amer_typewriter.ttf";
const int FONT_SIZE = 28;

class Common
{
public:
	static void FlushInput()
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
#endif

