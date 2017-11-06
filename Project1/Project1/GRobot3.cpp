#include "GRobot3.h"



GRobot3::GRobot3()
{
}


GRobot3::~GRobot3()
{
}

pos_t GRobot3::GetPos()
{
	return robot.pos;
}

double GRobot3::GetDir()
{
	return robot.angle;
}

void GRobot3::SetDir(double angle)
{
	robot.angle = angle;
}

void GRobot3::SetPos(pos_t newPos)
{
	robot.pos = newPos;
}
