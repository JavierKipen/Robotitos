#include "AllegroEG.h"
#include <iostream>
#define ALLEGRO_STATICLINK

using namespace std;


int allegro_startup(void)
{
	if (al_init())
	{
		if (al_init_primitives_addon())
		{
			if (al_install_keyboard())
			{
				if (al_install_mouse())
				{
					if (al_init_image_addon())
					{
						al_init_font_addon();
						if (al_init_ttf_addon())
						{
							if (al_install_audio())
							{
								if (al_init_acodec_addon())               //No tiene funcion para desinicializar
									return AL_STARTUP_SUCCESS;
								else
									cout << "ERROR: Failed to init acodec addon\n";
								al_uninstall_audio();
							}
							else
								cout << "ERROR: Failed to install audio\n";
						}
						else
							cout << "ERROR: Failed to initialize ttf addon\n";
						al_shutdown_font_addon();
						al_shutdown_image_addon();
					}
					else
						cout << "ERROR: Failed to initialize image addon\n";
					al_uninstall_mouse();
				}
				else
					cout << "ERROR: Failed to initialize mouse\n";
				al_uninstall_keyboard();
			}
			else
				cout << "ERROR: Failed to install keyboard\n";
			al_shutdown_primitives_addon();
		}
		else
			cout << "ERROR: Failed to load primitives addon\n";

	}
	else
		cout << "ERROR: Failed to initialize allegro system\n";
	return AL_STARTUP_ERROR;
}
void allegro_shut_down(void)
{
	al_uninstall_audio();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_primitives_addon();


}

AllegroEG::AllegroEG()
{
	this->EventQueue = al_create_event_queue(); //Creamos una event queue donde se guardarán nuestros eventos
	if (EventQueue != nullptr)
	{
		al_register_event_source(EventQueue, al_get_keyboard_event_source());
	}
	else 
		error = true;
}

bool AllegroEG::keyPressed()
{
	bool retVal = false;
	ALLEGRO_EVENT rawEvent;

	if (al_get_next_event(EventQueue, &rawEvent))
	{
		if (rawEvent.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (rawEvent.keyboard.keycode >= ALLEGRO_KEY_0 && rawEvent.keyboard.keycode <= ALLEGRO_KEY_2) //Solo nos interesan las teclas 0, 1 y 2
			{
				this->prevKey = rawEvent.keyboard.keycode - ALLEGRO_KEY_0;
				retVal = true;
			}
		}
	}
	return retVal;
}

int AllegroEG::getKey()
{
	return prevKey;
}

AllegroEG::~AllegroEG()
{
}
