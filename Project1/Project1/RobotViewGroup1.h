#pragma once
#include "Observer.h"
#include "RobotModel.h"
class RobotViewGroup1 :
	public Observer
{
public:
	RobotViewGroup1();
	void attachModel(RobotModel *model);
	void update();
	~RobotViewGroup1();
private:
	RobotModel model;
};

