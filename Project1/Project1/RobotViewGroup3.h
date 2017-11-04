#pragma once
#include "Observer.h"
#include "RobotModel.h"
class RobotViewGroup3 :
	public Observer
{
public:
	RobotViewGroup3();
	void attachModel(RobotModel *model);
	void update();
	~RobotViewGroup3();
private:
	RobotModel model;
};

