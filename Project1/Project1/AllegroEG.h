#ifndef ALLEGROEG_H
#define ALLEGROEG_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define AL_STARTUP_ERROR -1
#define AL_STARTUP_SUCCESS 0

int allegro_startup(void);
void allegro_shut_down(void);

class AllegroEG
{
public:
	AllegroEG();
	bool keyPressed();
	int getKey();
	~AllegroEG();
private:
	ALLEGRO_EVENT_QUEUE *EventQueue;
	bool error;
	int prevKey;
};
#endif

