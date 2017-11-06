#pragma once
#include <allegro5\allegro.h>
#include "Observer.h"
#include "RobotModel.h"
class RobotViewGroup2 :
	public Observer
{
public:
	RobotViewGroup2(RobotModel *model);
	void update();
	~RobotViewGroup2();
private:
	RobotViewGroup2();
	bool loadBitmaps();
	unsigned int floorHeight;
	unsigned int floorWidth;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *dirty_tile;
	ALLEGRO_BITMAP *clean_tile;
	ALLEGRO_BITMAP *robot;
	ALLEGRO_BITMAP *arrow;
	RobotModel *model;
};

