#include "RobotViewGroup2.h"
#include <algorithm>
#define G2_SCREEN_WIDTH 800
#define G2_SCREEN_HEIGHT 600


RobotViewGroup2::RobotViewGroup2(RobotModel *model)
{
	this->model = model;
	display = al_create_display(G2_SCREEN_WIDTH, G2_SCREEN_HEIGHT);
	loadBitmaps();
	floorHeight = model->getFloorHeight();
	floorWidth= model->getFloorWidth();
}

void RobotViewGroup2::update()
{
	vector<TileInfo> tileData = model->getTileInfo();
	vector<RobotPos> RobotPos = model->getRobotsInfo();

	double height = al_get_bitmap_width(clean_tile);
	double width = al_get_bitmap_height(clean_tile);
	double screen_width = G2_SCREEN_WIDTH;
	double screen_height = G2_SCREEN_HEIGHT;
	double tile_size = min((double)G2_SCREEN_WIDTH / (double)floorWidth, (double)G2_SCREEN_HEIGHT / (double)height);

	for (int i = 0; i < (int)screen_height; i++) {
		for (int j = 0; j < (int)screen_width; j++) {
			double new_size = tile_size;
			double pos_y = screen_height / 2.0 - tile_size*floorHeight / 2.0 + (double)i * tile_size + tile_size / 2;
			double pos_x = screen_width / 2.0 - tile_size*floorWidth / 2.0 + (double)j * tile_size + tile_size / 2;
			/*ALLEGRO_BITMAP *bitmap_use = tileData[i*floorWidth+j] ? clean_bitmap : dirty_bitmap;
			al_draw_scaled_bitmap(bitmap_use,
				0, 0, width, height,
				pos_x - new_size / 2, pos_y - new_size / 2,
				new_size, new_size, 0);*/
		}
	}


}


bool RobotViewGroup2::loadBitmaps()
{
	bool retVal = false;
	dirty_tile = al_load_bitmap("sucia.png");
	clean_tile = al_load_bitmap("limpia.png");
	robot = al_load_bitmap("robot.png");
	arrow = al_load_bitmap("arrow.png");
	if (dirty_tile != NULL && clean_tile != NULL && robot != NULL && arrow != NULL)
		retVal = true;
	return retVal;
}

RobotViewGroup2::~RobotViewGroup2()
{
	al_destroy_display(display);
}
