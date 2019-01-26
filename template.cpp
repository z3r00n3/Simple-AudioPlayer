// Includes
#include "template.h"

// Namespace
using namespace AGK;

app App;

app::app()
{
	volume = 100;

	stime[0]    = '\0';
	sminutes[0] = '\0';
	sseconds[0] = '\0';
}

void app::Begin()
{
	agk::SetWindowTitle("Simple Audio Player");
	agk::SetWindowSize(WIN_WIDTH, WIN_HEIGHT, false);
	agk::SetWindowPosition(200, 50);
	agk::SetWindowAllowResize(true);
	agk::SetDisplayAspect(static_cast<float>(WIN_WIDTH) / WIN_HEIGHT);
	agk::SetBorderColor(101, 146, 214);
	agk::UseNewDefaultFonts(true);
	agk::SetSyncRate(60, 0);

	bgSpriteID = agk::CreateSprite(agk::LoadImage("media/images/background.png"));
	agk::SetSpriteSize(bgSpriteID, 100.0, -1);
	agk::SetSpritePosition(bgSpriteID, 0.0, 0.0);
	agk::SetSpriteDepth(bgSpriteID, 12);

	trackSpriteID = agk::CreateSprite(agk::LoadImage("media/images/track.png"));
	agk::SetSpriteSize(trackSpriteID, BUTTON_SIZE * BUTTONS_NUM - 2, -1);
	agk::SetSpriteOffset(trackSpriteID, 0, agk::GetSpriteHeight(trackSpriteID) / 2);
	agk::SetSpritePositionByOffset(trackSpriteID, BUTTON_X_POS_START + 1.0 - BUTTON_SIZE / 2, 50.0);
	agk::SetSpriteDepth(trackSpriteID, 11);

	positionSpriteID = agk::CreateSprite(agk::LoadImage("media/images/position.png"));
	agk::SetSpriteSize(positionSpriteID, 1.5, -1);
	agk::SetSpriteOffset(positionSpriteID, agk::GetSpriteWidth(positionSpriteID) / 2, agk::GetSpriteHeight(positionSpriteID) / 2);
	agk::SetSpritePositionByOffset(positionSpriteID, BUTTON_X_POS_START + 1.0 - BUTTON_SIZE / 2, 50.0);
	agk::SetSpriteDepth(positionSpriteID, 10);

	crossSpriteID = agk::CreateSprite(agk::LoadImage("media/images/cross.png"));
	agk::SetSpriteSize(crossSpriteID, 3.0, -1);
	agk::SetSpriteDepth(crossSpriteID, 8);
	agk::SetSpriteOffset(crossSpriteID, agk::GetSpriteWidth(crossSpriteID) / 2, agk::GetSpriteHeight(crossSpriteID) / 2);
	agk::SetSpritePositionByOffset(crossSpriteID, BUTTON_X_POS_START + BUTTON_SIZE * 5 + BUTTON_SIZE / 2, 70.0);
	agk::SetSpriteVisible(crossSpriteID, false);

	agk::LoadImage(ImageButtonUpID::PLAY_RESUME,    "media/images/buttons/up/play.png");
	agk::LoadImage(ImageButtonUpID::PAUSE,          "media/images/buttons/up/pause.png");
	agk::LoadImage(ImageButtonUpID::STOP,           "media/images/buttons/up/stop.png");
	agk::LoadImage(ImageButtonUpID::REPEAT,         "media/images/buttons/up/repeat.png");
	agk::LoadImage(ImageButtonUpID::SEEK_BACK,      "media/images/buttons/up/seek_back.png");
	agk::LoadImage(ImageButtonUpID::SEEK_FORWARD,   "media/images/buttons/up/seek_forward.png");
	agk::LoadImage(ImageButtonUpID::VOLUME_DOWN,    "media/images/buttons/up/volume_down.png");
	agk::LoadImage(ImageButtonUpID::VOLUME_UP,      "media/images/buttons/up/volume_up.png");
	agk::LoadImage(ImageButtonUpID::MUTE,           "media/images/buttons/up/volume_off.png");
	agk::LoadImage(ImageButtonDownID::PLAY_RESUME,  "media/images/buttons/down/play.png");
	agk::LoadImage(ImageButtonDownID::PAUSE,        "media/images/buttons/down/pause.png");
	agk::LoadImage(ImageButtonDownID::STOP,         "media/images/buttons/down/stop.png");
	agk::LoadImage(ImageButtonDownID::REPEAT,       "media/images/buttons/down/repeat.png");
	agk::LoadImage(ImageButtonDownID::SEEK_BACK,    "media/images/buttons/down/seek_back.png");
	agk::LoadImage(ImageButtonDownID::SEEK_FORWARD, "media/images/buttons/down/seek_forward.png");
	agk::LoadImage(ImageButtonDownID::VOLUME_DOWN,  "media/images/buttons/down/volume_down.png");
	agk::LoadImage(ImageButtonDownID::VOLUME_UP,    "media/images/buttons/down/volume_up.png");
	agk::LoadImage(ImageButtonDownID::MUTE,         "media/images/buttons/down/volume_off.png");

	agk::AddVirtualButton(ButtonID::PLAY_PAUSE,   BUTTON_X_POS_START,                   BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::STOP,         BUTTON_X_POS_START + BUTTON_SIZE,     BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::REPEAT,       BUTTON_X_POS_START + BUTTON_SIZE * 2, BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::SEEK_BACK,    BUTTON_X_POS_START + BUTTON_SIZE * 3, BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::SEEK_FORWARD, BUTTON_X_POS_START + BUTTON_SIZE * 4, BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::VOLUME_DOWN,  BUTTON_X_POS_START + BUTTON_SIZE * 5, BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::VOLUME_UP,    BUTTON_X_POS_START + BUTTON_SIZE * 6, BUTTON_Y_POS, BUTTON_SIZE);
	agk::AddVirtualButton(ButtonID::MUTE,         BUTTON_X_POS_START + BUTTON_SIZE * 7, BUTTON_Y_POS, BUTTON_SIZE);

	agk::SetVirtualButtonImageUp  (ButtonID::PLAY_PAUSE,   ImageButtonUpID::PLAY_RESUME);
	agk::SetVirtualButtonImageDown(ButtonID::PLAY_PAUSE,   ImageButtonDownID::PLAY_RESUME);
	agk::SetVirtualButtonImageUp  (ButtonID::STOP,         ImageButtonUpID::STOP);
	agk::SetVirtualButtonImageDown(ButtonID::STOP,         ImageButtonDownID::STOP);
	agk::SetVirtualButtonImageUp  (ButtonID::REPEAT,       ImageButtonUpID::REPEAT);
	agk::SetVirtualButtonImageDown(ButtonID::REPEAT,       ImageButtonDownID::REPEAT);
	agk::SetVirtualButtonImageUp  (ButtonID::SEEK_BACK,    ImageButtonUpID::SEEK_BACK);
	agk::SetVirtualButtonImageDown(ButtonID::SEEK_BACK,    ImageButtonDownID::SEEK_BACK);
	agk::SetVirtualButtonImageUp  (ButtonID::SEEK_FORWARD, ImageButtonUpID::SEEK_FORWARD);
	agk::SetVirtualButtonImageDown(ButtonID::SEEK_FORWARD, ImageButtonDownID::SEEK_FORWARD);
	agk::SetVirtualButtonImageUp  (ButtonID::VOLUME_DOWN,  ImageButtonUpID::VOLUME_DOWN);
	agk::SetVirtualButtonImageDown(ButtonID::VOLUME_DOWN,  ImageButtonDownID::VOLUME_DOWN);
	agk::SetVirtualButtonImageUp  (ButtonID::VOLUME_UP,    ImageButtonUpID::VOLUME_UP);
	agk::SetVirtualButtonImageDown(ButtonID::VOLUME_UP,    ImageButtonDownID::VOLUME_UP);
	agk::SetVirtualButtonImageUp  (ButtonID::MUTE,         ImageButtonUpID::MUTE);
	agk::SetVirtualButtonImageDown(ButtonID::MUTE,         ImageButtonDownID::MUTE);

	agk::SetVirtualButtonActive(ButtonID::PLAY_PAUSE,   true);
	agk::SetVirtualButtonActive(ButtonID::STOP,         false);
	agk::SetVirtualButtonActive(ButtonID::REPEAT,       false);
	agk::SetVirtualButtonActive(ButtonID::SEEK_BACK,    false);
	agk::SetVirtualButtonActive(ButtonID::SEEK_FORWARD, false);
	agk::SetVirtualButtonActive(ButtonID::VOLUME_DOWN,  true);
	agk::SetVirtualButtonActive(ButtonID::VOLUME_UP,    false);
	agk::SetVirtualButtonActive(ButtonID::MUTE,         true);

	agk::SetVirtualButtonAlpha(ButtonID::PLAY_PAUSE,   BUTTON_OPAQUE);
	agk::SetVirtualButtonAlpha(ButtonID::STOP,         BUTTON_ALPHA);
	agk::SetVirtualButtonAlpha(ButtonID::REPEAT,       BUTTON_ALPHA);
	agk::SetVirtualButtonAlpha(ButtonID::SEEK_BACK,    BUTTON_ALPHA);
	agk::SetVirtualButtonAlpha(ButtonID::SEEK_FORWARD, BUTTON_ALPHA);
	agk::SetVirtualButtonAlpha(ButtonID::VOLUME_DOWN,  BUTTON_OPAQUE);
	agk::SetVirtualButtonAlpha(ButtonID::VOLUME_UP,    BUTTON_ALPHA);
	agk::SetVirtualButtonAlpha(ButtonID::MUTE,         BUTTON_OPAQUE);

	musicID = agk::LoadMusicOGG("media/music/HapkaBasa - Dilemmas.ogg");

	blue     = agk::MakeColor(101, 146, 214);
	neonBlue = agk::MakeColor(32, 217, 228);
	gray     = agk::MakeColor(80, 80, 86);

	timeTextID = agk::CreateText("00:00");
	agk::SetTextAlignment(timeTextID, 1);
	agk::SetTextPosition(timeTextID, BUTTON_X_POS_START + 1.0 - BUTTON_SIZE / 2, 45.0);

	hTimeTextID = agk::CreateText("");
	agk::SetTextColor(hTimeTextID, 32, 217, 228);

	fontID = agk::LoadFont("media/fonts/Paladin.ttf");

	artistTextID = agk::CreateText("HapkaBasa");
	agk::SetTextFont(artistTextID, fontID);
	agk::SetTextSize(artistTextID, 10.0);
	agk::SetTextAlignment(artistTextID, 1);
	agk::SetTextPosition(artistTextID, agk::GetSpriteX(trackSpriteID) + agk::GetSpriteWidth(trackSpriteID) / 2, 25.0);

	trackTextID = agk::CreateText("Dilemmas");
	agk::SetTextFont(trackTextID, fontID);
	agk::SetTextSize(trackTextID, 6.0);
	agk::SetTextAlignment(trackTextID, 1);
	agk::SetTextPosition(trackTextID, agk::GetSpriteX(trackSpriteID) + agk::GetSpriteWidth(trackSpriteID) / 2, 35.0);

	volumeTextID = agk::CreateText(itoa(volume, svolume, 10));
	agk::SetTextAlignment(volumeTextID, 1);
	agk::SetTextPosition(volumeTextID, BUTTON_X_POS_START + BUTTON_SIZE * 5 + BUTTON_SIZE / 2, 68.0);
}

int app::Loop()
{
	// Buttons
	for (int buttoniD = 1; buttoniD <= BUTTONS_NUM; buttoniD++)
	{
		if (agk::GetVirtualButtonReleased(buttoniD))
		{
			switch (buttoniD)
			{
			// PLAY
			case ButtonID::PLAY_PAUSE:
				if (!agk::GetMusicPlayingOGG(musicID))
					agk::PlayMusicOGG(musicID);
				else
					handlePlay ? agk::PauseMusicOGG(musicID) : agk::ResumeMusicOGG(musicID);

				agk::SetVirtualButtonImageUp  (ButtonID::PLAY_PAUSE, handlePlay ? ImageButtonUpID::PLAY_RESUME   : ImageButtonUpID::PAUSE);
				agk::SetVirtualButtonImageDown(ButtonID::PLAY_PAUSE, handlePlay ? ImageButtonDownID::PLAY_RESUME : ImageButtonDownID::PAUSE);
				
				handlePlay = !handlePlay;

				agk::SetVirtualButtonActive(ButtonID::STOP,         true);
				agk::SetVirtualButtonActive(ButtonID::REPEAT,       true);
				agk::SetVirtualButtonActive(ButtonID::SEEK_BACK,    true);
				agk::SetVirtualButtonActive(ButtonID::SEEK_FORWARD, true);

				agk::SetVirtualButtonAlpha(ButtonID::STOP,         BUTTON_OPAQUE);
				agk::SetVirtualButtonAlpha(ButtonID::REPEAT,       BUTTON_OPAQUE);
				agk::SetVirtualButtonAlpha(ButtonID::SEEK_BACK,    BUTTON_OPAQUE);
				agk::SetVirtualButtonAlpha(ButtonID::SEEK_FORWARD, BUTTON_OPAQUE);

				break;

			// STOP
			case ButtonID::STOP:
				agk::StopMusicOGG(musicID);

				if (handlePlay)
				{
					agk::SetVirtualButtonImageUp  (ButtonID::PLAY_PAUSE, ImageButtonUpID::PLAY_RESUME);
					agk::SetVirtualButtonImageDown(ButtonID::PLAY_PAUSE, ImageButtonDownID::PLAY_RESUME);
					
					handlePlay = !handlePlay;
				}

				if (handleRepeat)
				{
					agk::SetVirtualButtonImageUp  (ButtonID::REPEAT, ImageButtonUpID::REPEAT);
					agk::SetVirtualButtonImageDown(ButtonID::REPEAT, ImageButtonDownID::REPEAT);
					
					handleRepeat = !handleRepeat;
				}

				agk::SetVirtualButtonActive(ButtonID::STOP,         false);
				agk::SetVirtualButtonActive(ButtonID::REPEAT,       false);
				agk::SetVirtualButtonActive(ButtonID::SEEK_BACK,    false);
				agk::SetVirtualButtonActive(ButtonID::SEEK_FORWARD, false);

				agk::SetVirtualButtonAlpha(ButtonID::STOP,         BUTTON_ALPHA);
				agk::SetVirtualButtonAlpha(ButtonID::REPEAT,       BUTTON_ALPHA);
				agk::SetVirtualButtonAlpha(ButtonID::SEEK_BACK,    BUTTON_ALPHA);
				agk::SetVirtualButtonAlpha(ButtonID::SEEK_FORWARD, BUTTON_ALPHA);

				break;

			// REPEAT
			case ButtonID::REPEAT:
				agk::SetMusicLoopCountOGG(musicID, handleRepeat ? 0 : 1);

				agk::SetVirtualButtonImageUp  (ButtonID::REPEAT, handleRepeat ? ImageButtonUpID::REPEAT   : ImageButtonDownID::REPEAT);
				agk::SetVirtualButtonImageDown(ButtonID::REPEAT, handleRepeat ? ImageButtonDownID::REPEAT : ImageButtonUpID::REPEAT);
				
				handleRepeat = !handleRepeat;

				break;

			// SEEK_BACK
			case ButtonID::SEEK_BACK:
				if (agk::GetMusicPositionOGG(musicID) > SEEK_JUMP)
					agk::SeekMusicOGG(musicID, -SEEK_JUMP, 1);
				else
					agk::SeekMusicOGG(musicID, 0, 0);
				
				if (!handlePlay)
					agk::PauseMusicOGG(musicID);

				break;

			// SEEK_FORWARD
			case ButtonID::SEEK_FORWARD:
				if (agk::GetMusicDurationOGG(musicID) - agk::GetMusicPositionOGG(musicID) > SEEK_JUMP)
					agk::SeekMusicOGG(musicID, SEEK_JUMP, 1);
				else
					agk::SeekMusicOGG(musicID, agk::GetMusicDurationOGG(musicID) - agk::GetMusicPositionOGG(musicID), 1);

				if (!handlePlay)
					agk::PauseMusicOGG(musicID);

				break;

			// VOLUME_DOWN
			case ButtonID::VOLUME_DOWN:
				if (volume == 100)
				{
					agk::SetVirtualButtonActive(ButtonID::VOLUME_UP, true);
					agk::SetVirtualButtonAlpha(ButtonID::VOLUME_UP, BUTTON_OPAQUE);
				}

				if (volume > 0)
				{
					volume -= VOLUME_JUMP;
				}
				
				if (volume == 0)
				{
					agk::SetVirtualButtonActive(ButtonID::VOLUME_DOWN, false);
					agk::SetVirtualButtonAlpha(ButtonID::VOLUME_DOWN, BUTTON_ALPHA);
				}

				if (!handleMute)
					agk::SetMusicSystemVolumeOGG(volume);

				break;

			// VOLUME_UP
			case ButtonID::VOLUME_UP:
				if (volume == 0)
				{
					agk::SetVirtualButtonActive(ButtonID::VOLUME_DOWN, true);
					agk::SetVirtualButtonAlpha(ButtonID::VOLUME_DOWN, BUTTON_OPAQUE);
				}

				if (volume < 100)
				{
					volume += VOLUME_JUMP;
				}

				if (volume == 100)
				{
					agk::SetVirtualButtonActive(ButtonID::VOLUME_UP, false);
					agk::SetVirtualButtonAlpha(ButtonID::VOLUME_UP, BUTTON_ALPHA);
				}

				if (!handleMute)
					agk::SetMusicSystemVolumeOGG(volume);

				break;

			// VOLUME_OFF
			case ButtonID::MUTE:
				agk::SetMusicSystemVolumeOGG(handleMute ? volume : 0);

				agk::SetVirtualButtonImageUp  (ButtonID::MUTE, handleMute ? ImageButtonUpID::MUTE   : ImageButtonDownID::MUTE);
				agk::SetVirtualButtonImageDown(ButtonID::MUTE, handleMute ? ImageButtonDownID::MUTE : ImageButtonUpID::MUTE);
				
				agk::SetSpriteVisible(crossSpriteID, handleMute ? false : true);

				handleMute = !handleMute;

				break;

			default:
				break;
			}
		}
	}

	// Deactivate buttons if music end and don't repeat
	if (!agk::GetMusicPlayingOGG(musicID))
	{
		if (handlePlay)
		{
			agk::SetVirtualButtonImageUp(ButtonID::PLAY_PAUSE, ImageButtonUpID::PLAY_RESUME);
			agk::SetVirtualButtonImageDown(ButtonID::PLAY_PAUSE, ImageButtonDownID::PLAY_RESUME);
			handlePlay = !handlePlay;
		}

		if (handleRepeat)
		{
			agk::SetVirtualButtonImageUp(ButtonID::REPEAT, ImageButtonUpID::REPEAT);
			agk::SetVirtualButtonImageDown(ButtonID::REPEAT, ImageButtonDownID::REPEAT);
			handleRepeat = !handleRepeat;
		}

		agk::SetVirtualButtonActive(ButtonID::STOP,         false);
		agk::SetVirtualButtonActive(ButtonID::REPEAT,       false);
		agk::SetVirtualButtonActive(ButtonID::SEEK_BACK,    false);
		agk::SetVirtualButtonActive(ButtonID::SEEK_FORWARD, false);

		agk::SetVirtualButtonAlpha(ButtonID::STOP,         BUTTON_ALPHA);
		agk::SetVirtualButtonAlpha(ButtonID::REPEAT,       BUTTON_ALPHA);
		agk::SetVirtualButtonAlpha(ButtonID::SEEK_BACK,    BUTTON_ALPHA);
		agk::SetVirtualButtonAlpha(ButtonID::SEEK_FORWARD, BUTTON_ALPHA);
	}

	// Track status bar
	positionX = agk::GetSpriteX(trackSpriteID) + agk::GetMusicPositionOGG(musicID) * agk::GetSpriteWidth(trackSpriteID) / agk::GetMusicDurationOGG(musicID);
	agk::SetSpritePositionByOffset(positionSpriteID, positionX, 50.0);

	// Seek by click on status bar
	if ((agk::GetSpriteHit(agk::GetPointerX(), agk::GetPointerY()) == trackSpriteID ||
		 agk::GetSpriteHit(agk::GetPointerX(), agk::GetPointerY()) == positionSpriteID) && 
		 agk::GetPointerPressed()) 
	{
		positionX = agk::GetPointerX();
		agk::SetSpritePositionByOffset(positionSpriteID, positionX, 50.0);
		
		agk::SeekMusicOGG(musicID, (positionX - agk::GetSpriteX(trackSpriteID)) / (agk::GetSpriteWidth(trackSpriteID) / agk::GetMusicDurationOGG(musicID)), 0);
		if (!handlePlay)
			agk::PauseMusicOGG(musicID);
	}

	// Time status
	stime[0]    = '\0';
	sminutes[0] = '\0';
	sseconds[0] = '\0';

	time = agk::GetMusicPositionOGG(musicID);
	minutes = time / 60;
	if (minutes < 10)
		strcat(stime, "0");
	strcat(stime, itoa(time / 60, sminutes, 10));

	strcat(stime, ":");

	seconds = static_cast<int>(time) % 60;
	if (seconds < 10)
		strcat(stime, "0");
	strcat(stime, itoa(static_cast<int>(time) % 60, sseconds, 10));

	agk::SetTextString(timeTextID, stime);
	agk::SetTextPosition(timeTextID, positionX, 45.0);

	// Time help status
	if (agk::GetSpriteHit(agk::GetPointerX(), agk::GetPointerY()) == trackSpriteID ||
		agk::GetSpriteHit(agk::GetPointerX(), agk::GetPointerY()) == positionSpriteID)
	{
		stime[0]    = '\0';
		sminutes[0] = '\0';
		sseconds[0] = '\0';

		time = (agk::GetPointerX() - agk::GetSpriteX(trackSpriteID)) / (agk::GetSpriteWidth(trackSpriteID) / agk::GetMusicDurationOGG(musicID));
		minutes = time / 60;
		if (minutes < 10)
			strcat(stime, "0");
		strcat(stime, itoa(time / 60, sminutes, 10));

		strcat(stime, ":");

		seconds = static_cast<int>(time) % 60;
		if (seconds < 10)
			strcat(stime, "0");
		strcat(stime, itoa(static_cast<int>(time) % 60, sseconds, 10));

		agk::SetTextString(hTimeTextID, stime);
		agk::SetTextPosition(hTimeTextID, agk::GetPointerX() + 1.0, agk::GetSpriteY(trackSpriteID) + 1.0);
	}
	else
		agk::SetTextString(hTimeTextID, "");
	
	// Volume status bar
	agk::DrawLine(BUTTON_X_POS_START + BUTTON_SIZE * 5, BUTTON_Y_POS + (((WIN_WIDTH / 100.0) * BUTTON_SIZE) / (WIN_HEIGHT / 100.0) / 2), BUTTON_X_POS_START + BUTTON_SIZE * 5, 70.0, gray, gray);
	agk::DrawLine(BUTTON_X_POS_START + BUTTON_SIZE * 6, BUTTON_Y_POS + (((WIN_WIDTH / 100.0) * BUTTON_SIZE) / (WIN_HEIGHT / 100.0) / 2), BUTTON_X_POS_START + BUTTON_SIZE * 6, 70.0, gray, gray);
	agk::DrawLine(BUTTON_X_POS_START + BUTTON_SIZE * 5, 70.0, BUTTON_X_POS_START + BUTTON_SIZE * 5 + 1.0, 70.0, gray, gray);
	agk::DrawLine(BUTTON_X_POS_START + BUTTON_SIZE * 6, 70.0, BUTTON_X_POS_START + BUTTON_SIZE * 6 - 1.0, 70.0, gray, gray);

	agk::SetTextString(volumeTextID, itoa(volume, svolume, 10));

	agk::Sync();

	return 0; // return 1 to close app
}

void app::End()
{
	agk::DeleteAllSprites();
	for (int buttonID = 1; buttonID < BUTTONS_NUM; buttonID++)
		agk::DeleteVirtualButton(buttonID);
	agk::DeleteAllImages();
	agk::DeleteMusicOGG(musicID);
	agk::DeleteFont(fontID);
	agk::DeleteAllText();
}
