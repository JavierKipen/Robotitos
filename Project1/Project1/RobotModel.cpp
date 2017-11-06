#include "RobotModel.h"



RobotModel::RobotModel()
{
	sim = NULL;
	robotCount = DEFAULT_ROBOT_N;
	height = DEFAULT_FLOOR_H;
	width = DEFAULT_FLOOR_W;
	tickCount = 0;
	tilesCleaned = 0;
}

void RobotModel::startSym()
{
	sim = createSim(robotCount, height, width);
}

unsigned int RobotModel::getFloorHeight()
{
	return height;
}
unsigned int RobotModel::getFloorWidth()
{
	return width;
}
void RobotModel::tick()
{
	tilesCleaned += simulate(sim, &tickCount);
}
bool RobotModel::simEnded()
{
	return (tilesCleaned  < (sim->height)*(sim->width));
}
unsigned int RobotModel::getFloorWidth()
{
	return width;
}
list<TileInfo> RobotModel::getTileInfo()
{

	
}
list<RobotPos> RobotModel::getRobotsInfo()
{
	RobotPos aux;
	list<RobotPos> retVal;
	for (unsigned int i = 0; i < robotCount; i++)
	{
		robotType robot=sim->robots[i];
		aux.x = robot.pos.x;
		aux.y = robot.pos.y;
		aux.angle = robot.angulo;
		retVal.push_back(aux);
	}
	return retVal;
}

RobotModel::~RobotModel()
{
}
