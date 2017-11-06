#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "Model.h"

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
};
#endif

