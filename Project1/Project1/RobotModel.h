#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "Model.h"

class RobotModel : public Model
{
public:
	RobotModel();
	bool simulationFinished();
	~RobotModel();
};
#endif

