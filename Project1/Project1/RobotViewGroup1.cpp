#include "RobotViewGroup1.h"
#include <iostream>
using namespace std;

#define MODULO(a) ( ( (a >= 0)? a : (a * (-1)) ) )

#define DISP_W 1280
#define DISP_H 720



RobotViewGroup1::RobotViewGroup1(RobotModel *model)
{
	this->model = model;
	this->floor_width = model->getFloorWidth();
	this->floor_height = model->getFloorHeight();

	this->floor = this->model->getTileInfo();
	this->robots = this->model->getRobotsInfo();

	initOk = init_sim_graphics(&sim_graphics);
}

void RobotViewGroup1::update()
{
	floor = this->model->getTileInfo();
	robots = this->model->getRobotsInfo();

	draw_floor();
	draw_all_robots();
	
	al_flip_display();
}

RobotViewGroup1::~RobotViewGroup1()
{
	if (initOk)
		destroy_sim_graphics();
}

bool RobotViewGroup1::error()
{
	return !initOk;
}

bool RobotViewGroup1::init_al_hard()
{
	bool ret = true;

	sim_graphics.display = al_create_display(DISP_W, DISP_H);
	if (sim_graphics.display == NULL)
	{
		fprintf(stderr, "failed to create display!\n");
		ret = false;
	}
	return ret;
}

ALLEGRO_BITMAP* RobotViewGroup1::load_image(const char *image) {

	ALLEGRO_BITMAP *image_png = NULL;
	image_png = al_load_bitmap(image);
	if (!image_png)
	{
		cerr << "failed to load image" << endl;
		return nullptr;
	}
	return image_png;
}

bool RobotViewGroup1::load_sim_images() {

	bool ret = true;
	sim_graphics.sim_images.cleanTile = load_image("Images/cleanTile.png");
	if (sim_graphics.sim_images.cleanTile == nullptr)
		ret = false;

	sim_graphics.sim_images.dirtyTile = load_image("Images/dirtyTile.png");
	if (sim_graphics.sim_images.dirtyTile == nullptr)
		ret = false;

	sim_graphics.sim_images.robotBody = load_image("Images/robot.png");
	if (sim_graphics.sim_images.robotBody == nullptr)
		ret = false;

	return ret;
}

bool RobotViewGroup1::init_sim_graphics(sim_graphics_t *sim_graphics)
{
	bool aux = true;
	aux = init_al_hard();

	if (aux != false)
		aux = load_sim_images();

	return aux;
}

double RobotViewGroup1::calculate_baldosaPixel()
{
	double pixels;
	if ((DISP_W / floor_width) >= DISP_H / floor_height)
		pixels = (DISP_H - 20) / floor_height;
	else
		pixels = (DISP_W - 20) / floor_width;
	return pixels;
}

void RobotViewGroup1::calculate_FloorStart(double* x, double* y)
{
	double coord_start_x, coord_start_y;
	double baldosa_pixels = calculate_baldosaPixel();

	coord_start_x = (DISP_W - (baldosa_pixels * floor_width)) / 2;
	coord_start_y = (DISP_H - (baldosa_pixels * floor_height)) / 2;

	*x = coord_start_x;
	*y = coord_start_y;
}

void RobotViewGroup1::draw_tile(unsigned int row, unsigned int column)
{
	double floorStart_x, floorStart_y;
	calculate_FloorStart(&floorStart_x, &floorStart_y);
	double baldosaPoint_x, baldosaPoint_y;
	double pixels = calculate_baldosaPixel();
	double sw, sh;
	sw = al_get_bitmap_width(sim_graphics.sim_images.dirtyTile); // Its the same original size for both images
	sh = sw;
	bool baldosa_clean = floor[row * floor_width + column].clean;

	baldosaPoint_x = floorStart_x + (column * pixels);
	baldosaPoint_y = floorStart_y + (row * pixels);
	al_set_target_backbuffer(sim_graphics.display);
	if (!baldosa_clean)
		al_draw_scaled_bitmap(sim_graphics.sim_images.dirtyTile, 0, 0, sw, sh, baldosaPoint_x, baldosaPoint_y, pixels, pixels, 0);
	else
		al_draw_scaled_bitmap(sim_graphics.sim_images.cleanTile, 0, 0, sw, sh, baldosaPoint_x, baldosaPoint_y, pixels, pixels, 0);
}

void RobotViewGroup1::draw_floor()
{
	for (unsigned int i = 0; i < floor_height; i++)
		for (unsigned int j = 0; j < floor_width; j++)
			draw_tile(i, j);
}

void RobotViewGroup1::draw_robot(unsigned int robot)
{
	double floorStart_x, floorStart_y;
	calculate_FloorStart(&floorStart_x, &floorStart_y);
	double robotPoint_x, robotPoint_y;
	double pixels = calculate_baldosaPixel();
	double sw, sh;
	sw = al_get_bitmap_width(sim_graphics.sim_images.robotBody);
	sh = sw;

	if ((((floor_width)-(robots[robot].x))*pixels) < (pixels / 4))
		robotPoint_x = floorStart_x + (((floor_width)-0.25)*pixels) - (pixels / 4);
	else if (((robots[robot].x)*pixels) < (pixels / 4))
		robotPoint_x = floorStart_x;
	else
		robotPoint_x = floorStart_x + ((robots[robot].x)*pixels) - (pixels / 4);


	if ((((floor_height)-(robots[robot].y))*pixels) < (pixels / 4))
		robotPoint_y = floorStart_y + (((floor_height)-0.25)*pixels) - (pixels / 4);
	else if (((robots[robot].y)*pixels) < (pixels / 4))
		robotPoint_y = floorStart_y;
	else
		robotPoint_y = floorStart_y + ((robots[robot].y)*pixels) - (pixels / 4);
	al_set_target_backbuffer(sim_graphics.display);
	al_draw_scaled_bitmap(sim_graphics.sim_images.robotBody, 0, 0, sw, sh, robotPoint_x, robotPoint_y, pixels / 2, pixels / 2, 0);
}


void RobotViewGroup1::draw_all_robots()
{
	for (size_t i = 0; i < robots.size(); i++)
		draw_robot(i);
}

void RobotViewGroup1::destroy_images()
{
	if (initOk)
	{
		al_destroy_bitmap(sim_graphics.sim_images.cleanTile);
		al_destroy_bitmap(sim_graphics.sim_images.dirtyTile);
		al_destroy_bitmap(sim_graphics.sim_images.robotBody);
	}
}


void RobotViewGroup1::destroy_sim_graphics()
{
	al_destroy_display(sim_graphics.display);
	destroy_images();
}