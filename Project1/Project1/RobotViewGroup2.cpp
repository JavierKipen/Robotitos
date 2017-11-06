#include "RobotViewGroup2.h"
#include <algorithm>
#define G2_SCREEN_WIDTH 800
#define G2_SCREEN_HEIGHT 600
#define ROBOT_FACTOR_SIZE_CONST  0.5


RobotViewGroup2::RobotViewGroup2(RobotModel *model)
{
	this->model = model;
	display = al_create_display(G2_SCREEN_WIDTH, G2_SCREEN_HEIGHT);
	loadBitmaps();
	floorHeight = model->getFloorHeight();
	floorWidth= model->getFloorWidth();
	screen_width = G2_SCREEN_WIDTH;
	screen_height = G2_SCREEN_HEIGHT;
	update();
}

void RobotViewGroup2::update()
{
	vector<TileInfo> tileData = model->getTileInfo();
	vector<RobotPos> RobotPos = model->getRobotsInfo();

	double height = al_get_bitmap_width(clean_tile);
	double width = al_get_bitmap_height(clean_tile);
	tile_size = min((double)screen_width / (double)floorWidth, (double)screen_height / (double)height);

	for (int i = 0; i < (int)screen_height; i++) {
		for (int j = 0; j < (int)screen_width; j++) {
			double new_size = tile_size;
			double pos_y = screen_height / 2.0 - tile_size*floorHeight / 2.0 + (double)i * tile_size + tile_size / 2;
			double pos_x = screen_width / 2.0 - tile_size*floorWidth / 2.0 + (double)j * tile_size + tile_size / 2;
			ALLEGRO_BITMAP *bitmap_use = tileData[i*floorWidth+j].clean ? clean_tile : dirty_tile;
			al_draw_scaled_bitmap(bitmap_use,
				0, 0, width, height,
				pos_x - new_size / 2, pos_y - new_size / 2,
				new_size, new_size, 0);
		}
	}
	for (int i = 0; i < (int)RobotPos.size(); i++) {
		drawRobots(RobotPos[i]);
	}

}

void RobotViewGroup2::drawRobots(RobotPos robotInfo)
{

	double height = al_get_bitmap_width(robot);
	double width = al_get_bitmap_height(robot);

	double new_size = tile_size  * ROBOT_FACTOR_SIZE_CONST;

	double unit_x = robotInfo.x;
	double unit_y = robotInfo.y;

	double start_x = screen_width / 2.0 - tile_size*floorWidth / 2.0;
	double start_y = screen_height / 2.0 - tile_size*floorHeight / 2.0;

	double pos_x = start_x + unit_x * tile_size;
	double pos_y = start_y + unit_y * tile_size;

	if (pos_x - new_size / 2 <= start_x) {
		pos_x = start_x + new_size / 2;
	}
	if (pos_y - new_size / 2 <= start_y) {
		pos_y = start_y + new_size / 2;
	}
	if (pos_x + new_size / 2 >= start_x + floorWidth *tile_size) {
		pos_x = start_x + floorWidth *tile_size - new_size / 2;
	}
	if (pos_y + new_size / 2 >= start_y + floorHeight*tile_size) {
		pos_y = start_y + floorHeight*tile_size - new_size / 2;
	}

	/*** Draw arrow ***/
	uint32_t bitmap_height = al_get_bitmap_height(arrow);
	uint32_t bitmap_width = al_get_bitmap_width(arrow);

	al_draw_scaled_rotated_bitmap(arrow,
		0, bitmap_height / 2, pos_x, pos_y, tile_size / bitmap_width, tile_size / bitmap_height / 2,
		robotInfo.angle, 0);

	/*** Draw robot ***/
	al_draw_scaled_bitmap(robot,
		0, 0, width, height,
		pos_x - new_size / 2, pos_y - new_size / 2,
		new_size, new_size, 0);
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
