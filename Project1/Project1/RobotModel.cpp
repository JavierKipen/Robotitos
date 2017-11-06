#include "RobotModel.h"



RobotModel::RobotModel()
{
	sim = NULL;
	RobotCount = DEFAULT_ROBOT_N;
	Height = DEFAULT_FLOOR_H;
	Width = DEFAULT_FLOOR_W;
}

void RobotModel::startSym()
{
	sim = createSim(RobotCount, Height, Width);
}

bool RobotModel::simEnded()
{
	return 0;
}

RobotModel::~RobotModel()
{
}
