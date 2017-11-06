#include "RobotController.h"



RobotController::RobotController()
{
	isViewActive[0] = false;
	isViewActive[1] = false;
	isViewActive[2] = false;
}

bool RobotController::attachModel(RobotModel *model)
{
	this->model = model;
	return true;
}
bool RobotController::hayEvento()
{
	bool retVal = false;
	if (this->allegroEG.keyPressed())
	{
		this->eventType = R_ALLEGRO_EVENT;
		retVal = true;
	}
	return retVal;
}
void RobotController::parseEvento()
{
	int nmbrPressed = this->allegroEG.getKey();
	parseKeyboardEvent((void *)&nmbrPressed);
}
void RobotController::parseKeyboardEvent(void *Event)
{
	//Aca se va a añadir o quitar las pantallas que ven al modelo.
	int nmbrOfView = *((int *)Event);
	if (nmbrOfView < VIEWS_COUNT)
	{
		if (this->isViewActive[nmbrOfView] == false) //Si dicha vista no estaba activa, se activa.
		{
			switch(nmbrOfView)
			{
			case 0:
				//allViews[nmbrOfView] = new RobotViewGroup1;
				break;
			case 1:
				allViews[nmbrOfView] = new RobotViewGroup2(model);
				break;
			case 2:
				//allViews[nmbrOfView] = new RobotViewGroup3;
				break;
			}
			model->attach(allViews[nmbrOfView]);
			this->isViewActive[nmbrOfView] = true;
		}
		else//Sino, se cierra la ventana.
		{
			model->deAttach(allViews[nmbrOfView]);
			delete allViews[nmbrOfView];
		}
	}
}
RobotController::~RobotController()
{
}
