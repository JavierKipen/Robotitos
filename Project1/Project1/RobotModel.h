#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H
#include <vector>
#include "Model.h"
extern "C" {
#include "simulation.h"
}

using namespace std;
#define DEFAULT_ROBOT_N 20
#define DEFAULT_FLOOR_W 20
#define DEFAULT_FLOOR_H 20
	
/*Estructuras definidas comunes para todos los views*/
typedef struct
{
	double x;
	double y;
	double angle;
}RobotPos;
typedef struct
{
	unsigned int x;
	unsigned int y;
	bool clean;
}TileInfo;
/****************************************************/

class RobotModel : public Model
{
public:
	RobotModel();
	void startSym();	//Para inicializar toda la simulación.
	void tick();		//Se calcula un paso de la simulacion
	bool simEnded();	//Devuelve si la simulación termino
	/*Funciones para entregarle datos a los observadores*/
	vector<TileInfo> getTileInfo();
	vector<RobotPos> getRobotsInfo();
	unsigned int getFloorWidth();
	unsigned int getFloorHeight();
	~RobotModel();
private:
	simType * sim;
	unsigned int robotCount;
	unsigned int height;
	unsigned int width;
	unsigned int tickCount;
	unsigned int tilesCleaned;
};
#endif

