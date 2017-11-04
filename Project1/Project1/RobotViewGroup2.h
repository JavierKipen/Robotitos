#pragma once
#include "Observer.h"
#include "RobotModel.h"
class RobotViewGroup2 :
	public Observer
{
public:
	RobotViewGroup2();
	void attachModel(RobotModel *model);
	void update();
	~RobotViewGroup2();
private:
	RobotModel model;
};

