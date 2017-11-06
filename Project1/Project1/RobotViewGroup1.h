#pragma once
#include "Observer.h"
#include "RobotModel.h"
#include <vector>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct {
	ALLEGRO_BITMAP *dirtyTile;
	ALLEGRO_BITMAP *cleanTile;
	ALLEGRO_BITMAP *robotBody;
} sim_images_t;

typedef struct {
	ALLEGRO_DISPLAY *display;
	sim_images_t sim_images;
} sim_graphics_t;


class RobotViewGroup1 :
	public Observer
{
public:
	RobotViewGroup1(RobotModel *model);
	void update();
	bool error();
	~RobotViewGroup1();
private:
	RobotViewGroup1();
	sim_graphics_t sim_graphics;
	unsigned int floor_width;
	unsigned int floor_height;
	bool initOk;

	vector<TileInfo> floor;
	vector<RobotPos> robots;
	RobotModel* model;
	// init_sim_graphics: loads allegro hardware and images, if not returns 0
	bool init_sim_graphics(sim_graphics_t *sim_graphics);

	// init_al_hard: initializes allegro display and addons
	bool init_al_hard();

	// load_sim_images: loads images for simulation mode 1
	bool load_sim_images();

	// load_image: loads an image from resources. If not, returns 0
	ALLEGRO_BITMAP* load_image(const char *image);

	// draw_floor: draws the actual floor into allegro display
	void draw_floor();

	// draw_robots: draws all the robots into allegro display
	void draw_all_robots();


	// draw_tile: draws one tile into given position
	void draw_tile(unsigned int fil, unsigned int col);

	// draw_robot: draws one robot in new position
	void draw_robot(unsigned int robot);

	void calculate_FloorStart(double* x, double* y);

	double calculate_baldosaPixel();

	// destroy_sim_graphics: destroys simulation graphics
	void destroy_sim_graphics();

	// destroy_images: destroy tiles and robot images
	void destroy_images();
};
