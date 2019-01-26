#pragma once

// Link to GDK libraries
#include "AGK.h"

#define DEVICE_WIDTH 1024
#define DEVICE_HEIGHT 768
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false

// used to make a more unique folder for the write path
#define COMPANY_NAME "My Company"

#define WIN_WIDTH          960
#define WIN_HEIGHT         600
#define BUTTON_SIZE		   7.0
#define BUTTON_OPAQUE      255
#define BUTTON_ALPHA       85
#define BUTTON_X_POS_START 5.0
#define BUTTON_Y_POS       60.0
#define BUTTONS_NUM        8
#define SEEK_JUMP          10.0
#define VOLUME_JUMP        10

//#define TRACK_NAME "Attack On Titan Season 2 OST - Barricades.ogg"

namespace ButtonID
{
	enum ButtonID
	{
		PLAY_PAUSE = 1,
		STOP,
		REPEAT,
		SEEK_BACK,
		SEEK_FORWARD,
		VOLUME_DOWN,
		VOLUME_UP,
		MUTE,
	};
}

namespace ImageButtonUpID
{
	enum ImageButtonUpID
	{
		PLAY_RESUME = 1,
		PAUSE,
		STOP,
		REPEAT,
		SEEK_BACK,
		SEEK_FORWARD,
		VOLUME_DOWN,
		VOLUME_UP,
		MUTE,
	};
}

namespace ImageButtonDownID
{
	enum ImageButtonDownID
	{
		PLAY_RESUME = 11,
		PAUSE,
		STOP,
		REPEAT,
		SEEK_BACK,
		SEEK_FORWARD,
		VOLUME_DOWN,
		VOLUME_UP,
		MUTE,
	};
}

// Global values for the app
class app
{
private:
	int bgSpriteID, trackSpriteID, positionSpriteID, crossSpriteID;
	int musicID;
	int timeTextID, hTimeTextID, artistTextID, trackTextID, volumeTextID;
	int fontID;
	bool handlePlay, handleRepeat, handleMute;
	int volume;
	unsigned int blue, neonBlue, gray;
	float positionX;
	float time;
	int minutes, seconds;
	char stime[16], sminutes[4], sseconds[4], svolume[4];

public:

	// constructor
	app();

	// main app functions - mike to experiment with a derived class for this..
	void Begin();
	int Loop();
	void End();
};

extern app App;

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif