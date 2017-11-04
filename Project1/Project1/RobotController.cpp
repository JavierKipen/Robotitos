#include "RobotController.h"



RobotController::RobotController()
{
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
}
RobotController::~RobotController()
{
}
