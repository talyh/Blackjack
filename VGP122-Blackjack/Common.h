#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <array>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>
#include "Size.h"
#include "Position.h"
#include "Textbox.h"
#include "Button.h"

using namespace std;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720
#define CARD_WIDTH 72
#define CARD_HEIGHT 96

// define layout variables
const int LINE_HEIGHT { 20 };
const int PADDING { 20 };
const Size START_MENU_BUTTON_SIZE { 383, 78 };
const Size BET_BUTTON_SIZE { 32, 32 }; 
const Size PLAY_BUTTON_SIZE { 32, 32 };
const int BUTTON_PADDING { 8 };
const int CARD_PADDING{ 15 };
const Position DEALER_HAND_POSITION{ SCREEN_WIDTH / 2 - CARD_WIDTH, PADDING };
const Position PLAYER_HAND_POSITION{ SCREEN_WIDTH / 2 - CARD_WIDTH, SCREEN_HEIGHT - CARD_HEIGHT - PADDING * 8 };

// define constants
// visual
const string BACKGROUND_IMAGE = "imgs/background.png";
const string BTN_PLAY_IMAGE = "imgs/btnPlay.png";
const string BTN_INSTRUCTIONS_IMAGE = "imgs/btnInstructions.png";
const string BTN_QUIT_IMAGE = "imgs/btnQuit.png";
const string BTN_BET_UP_IMAGE = "imgs/btnBetUp.png";
const string BTN_BET_DOWN_IMAGE = "imgs/btnBetDown.png";
const string BTN_BET_CONFIRM_IMAGE = "imgs/btnBetConfirm.png";
const string BTN_HIT_IMAGE = "imgs/btnHit.png";
const string BTN_HIT_TOOLTIP = "imgs/btnHitTooltip.png";
const string BTN_STAY_IMAGE = "imgs/btnStay.png";
const string BTN_STAY_TOOLTIP = "imgs/btnStayTooltip.png";
const string BTN_SPLIT_IMAGE = "imgs/btnSplit.png";
const string BTN_SPLIT_TOOLTIP = "imgs/btnSplitTooltip.png";
const string BTN_DOUBLE_DOWN_IMAGE = "imgs/btnDoubleDown.png";
const string BTN_DOUBLE_DOWN_TOOLTIP = "imgs/btnDoubleDownTooltip.png";
const string BTN_SURRENDER_IMAGE = "imgs/btnSurrender.png";
const string BTN_SURRENDER_TOOLTIP = "imgs/btnSurrenderTooltip.png";
const string BTN_YES_IMAGE = "imgs/btnConfirm.png";
const string BTN_NO_IMAGE = "imgs/btnPass.png";
const string CARDS_IMAGE = "imgs/cards.png";
const string CARD_BACK_IMAGE = "imgs/cardBack.png";
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
const int FONT_SIZE { 28 };

#endif

