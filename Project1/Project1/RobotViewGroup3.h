#pragma once
#include "Observer.h"
#include <iostream>
#include "RobotModel.h"
#include "GRobot3.h"
#include "GTile3.h"
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
//#include <allegro5\allegro_color.h>
//#include <allegro5\allegro_ttf.h>
//#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>




typedef struct
{
	ALLEGRO_BITMAP* b_limpia;
	ALLEGRO_BITMAP* b_sucia;
	ALLEGRO_BITMAP* robot;
}imagenes_t;



class RobotViewGroup3 :
	public Observer
{
public:
	RobotViewGroup3(RobotModel *model );
	void update();
	~RobotViewGroup3();
private:
	bool initOk;
	unsigned int unit;
	RobotViewGroup3();
	bool attachModel(RobotModel *model);
	bool SetImages(void);

	void ModifyRobots();
	void ActualizarRobots(void);
	void ModifyTiles(void);
	void ActualizarBaldosas(void);
	
	ALLEGRO_BITMAP* load_image_at_size(char* image_name, int size_x, int size_y);
	ALLEGRO_DISPLAY *display;
	RobotModel *model;
	GRobot3* robots;
	GTile3* tiles;
	imagenes_t imgs;
	unsigned int robotNumber;
};

