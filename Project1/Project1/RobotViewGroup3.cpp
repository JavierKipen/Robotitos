#include "RobotViewGroup3.h"
#define _USE_MATH_DEFINES
#include <math.h>



#define AXIS_COLOR "white"
#define BAR_COLOR "green"
#define BACKGROUND_COLOR "black"
#define FONT_COLOR "hotpink"
#define REFERENCE_COLOR "lightblue"
#define VECTOR_COLOR "red"



#define BALDOSA_SUCIA "../Imagenes/dirtytile.png"
#define BALDOSA_LIMPIA "../Imagenes/limpio2.png"
#define ROBOT "../Imagenes/robot.png"
#define ROBOT_SIZE(u) (((u)/2.0))
#define RADIAN(x) (((x)*(M_PI))/180.0)
#define UNIT 800 /*ni en el codigo ni en el comentario del trabajo se explica de donde se obtiene
o que es este numero, se deja asi al igual que el resto de los magic numbers*/

#define DISP_WIDTH3 1080
#define	DISP_HEIGHT3 900


using namespace std;

RobotViewGroup3::RobotViewGroup3(RobotModel *model)
{
	initOk = false;
	display = nullptr;
	if (model != nullptr)
	{
		if (attachModel(model))
		{
			unit = (UNIT) / (((double)model->getFloorWidth() + (double)model->getFloorHeight()) / 2.0);
			if (SetImages())
			{
				display = al_create_display(DISP_WIDTH3,DISP_HEIGHT3);
				if (display != nullptr)
					initOk = true;
				else {}
			}
			else{}
		}
		else{}
	}
	else{}
}

bool RobotViewGroup3::attachModel(RobotModel * model)
{
	bool retVal = false;
	if (model != nullptr)
	{
		this->model = model;
		retVal = true;
	}
	return retVal;
}

void RobotViewGroup3::update()
{
	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	ActualizarBaldosas();
	ActualizarBaldosas();


	al_flip_display();
}
RobotViewGroup3::~RobotViewGroup3()
{
	if (initOk)
	{
		al_destroy_bitmap(imgs.b_limpia);
		al_destroy_bitmap(imgs.b_sucia);
		al_destroy_bitmap(imgs.robot);
	}
}

bool RobotViewGroup3::SetImages(void)
{
	bool retVal = false;
	imgs.b_limpia= load_image_at_size(BALDOSA_LIMPIA, unit, unit);
	imgs.b_sucia= load_image_at_size(BALDOSA_SUCIA, unit, unit);
	imgs.robot= load_image_at_size(ROBOT, ROBOT_SIZE(unit), ROBOT_SIZE(unit));


	if ((imgs.b_limpia != nullptr) && (imgs.b_sucia != nullptr) && (imgs.robot != nullptr))
		retVal =true;
	return retVal;
}

ALLEGRO_BITMAP * RobotViewGroup3::load_image_at_size(char* image_name, int size_x, int size_y)
{
	ALLEGRO_BITMAP * image = nullptr;
	ALLEGRO_BITMAP * current_target = nullptr;
	ALLEGRO_BITMAP * resized_image = nullptr;

	current_target = al_get_target_bitmap(); //salva el target original para no perderlo

	image = al_load_bitmap(image_name);
	if (image == nullptr)
	{
		return nullptr;
	}

	resized_image = al_create_bitmap(size_x, size_y);
	if (resized_image == nullptr)
	{
		al_destroy_bitmap(image);
		return nullptr;


	}

	al_set_target_bitmap(resized_image);
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
		0, 0, size_x, size_y, 0);

	al_set_target_bitmap(current_target); //vuelve al target original
	al_destroy_bitmap(image);
	return resized_image;
}

void RobotViewGroup3::ActualizarRobots(void)
{
	ModifyRobots();
	pos_t cord = { 0.0 , 0.0 };
	pos_t vector = { 0.0 , 0.0 };
	pos_t vector_head1 = { 0.0 , 0.0 }; //Representan los tres vertices del triangulo que forma
	pos_t vector_head2 = { 0.0 , 0.0 }; //la cabeza del vector.
	pos_t vector_head3 = { 0.0 , 0.0 };
	double angle = 0.0;

	for (unsigned int i = 0; i < robots.size(); i++)
	{
		cord = robots[i].GetPos();
		angle = robots[i].GetDir();
		angle = RADIAN(angle);
		al_draw_bitmap(imgs.robot, cord.x, cord.y, 0); //dibuja el robot en su posicion del display

		(vector.x) = (cord.x) + (unit)*cos(angle);
		(vector.y) = (cord.y) - (unit)*sin(angle);

		al_draw_line((cord.x) + (ROBOT_SIZE(unit)) / 2.0, (cord.y) + (ROBOT_SIZE(unit)) / 2.0, vector.x, vector.y, al_color_name(VECTOR_COLOR), 1.0);

		vector_head1.x = (vector.x) - ((unit) / 10.0)*cos(M_PI / 4.0);
		vector_head1.y = (vector.y) - ((unit) / 10.0)*sin(M_PI / 4.0);

		vector_head2.x = (vector.x) + ((unit) / 10.0)*cos(M_PI / 4.0);
		vector_head2.y = (vector.y) + ((unit) / 10.0)*sin(M_PI / 4.0);

		vector_head3.x = (vector.x) + ((unit) / 10.0)*cos(angle);
		vector_head3.y = (vector.y) - ((unit) / 10.0)*sin(angle);

		al_draw_filled_triangle(vector_head1.x, vector_head1.y, vector_head2.x, vector_head2.y, vector_head3.x, vector_head3.y, al_color_name(VECTOR_COLOR));
		//Dibuja el vector que indica la direccion del robot.Tiene modulo UNIT y parte del centro del robot.
	}
}
void RobotViewGroup3::ModifyRobots(void)
{
	vector<RobotPos > modelRobots = model->getRobotsInfo();
	for (int i = 0; i < modelRobots.size(); ++i)
	{
		robots[i].SetPos( {modelRobots[i].x, modelRobots[i].y } );
		robots[i].SetDir(modelRobots[i].angle);
	}
}


void RobotViewGroup3:: ActualizarBaldosas(void)
{
	ModifyTiles();
	bool state;
	position_t cord;
	for (unsigned int i = 0; i<model->getFloorHeight(); i++) //actualiza todas las baldosas segun sus estados.
	{
		for (unsigned int j = 0; j < model->getFloorWidth(); j++)
		{

			state = tiles[i*(model->getFloorWidth())+j].GetState();
			cord = tiles[i*(model->getFloorWidth()) + j].GetLocation();

			if (state == true)
			{
				al_draw_bitmap(imgs.b_limpia, cord.x, cord.y, 0); //dibuja la baldosa limpia.
			}
			else
			{
				al_draw_bitmap(imgs.b_sucia, cord.x, cord.y, 0); //dibuja la baldosa sucia.
			}
		}

	}
}

void RobotViewGroup3::ModifyTiles(void)
{
	vector<TileInfo> modelTiles = model->getTileInfo();
	for (int i = 0; i < modelTiles.size(); ++i)
	{
		tiles[i].SetLocation({(double) modelTiles[i].x, (double) modelTiles[i].y });
		tiles[i].SetState(modelTiles[i].clean);
	}
}
