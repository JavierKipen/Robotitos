#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "Model.h"
extern "C" {
#include "simulation.h"
}

using namespace std;
#define DEFAULT_ROBOT_N 20
#define DEFAULT_FLOOR_W 20
#define DEFAULT_FLOOR_H 20
	

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

class RobotModel : public Model
{
public:
	RobotModel();
	void startSym();
	void tick();
	bool simEnded();
	list<TileInfo> getTileInfo();
	list<RobotPos> getRobotsInfo();
	unsigned int getFloorWidth();
	unsigned int getFloorHeight();
	~RobotModel();
private:
	simType * sim;
	unsigned int RobotCount;
	unsigned int Height;
	unsigned int Width;
};
#endif

