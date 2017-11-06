#include "RobotController.h"



RobotController::RobotController()
{
	isViewActive[0] = false; //Se comienza la simulación sin robots.
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
	if (this->allegroEG.keyPressed()) //El unico evento que daremos importancia es si hay una tecla que nos importe presionada
	{
		this->eventType = R_ALLEGRO_EVENT; //Podriamos tener eventos de distintas fuentes, por lo cual se guarda la fuente del mismo.
		retVal = true;
	}
	return retVal;
}
void RobotController::parseEvento()
{
	int nmbrPressed = this->allegroEG.getKey(); //Como en este caso, el único evento es por presionar una tecla, se parseará el keyboardEvent
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
			{	//Se creará el view correspondiente, attacheandole el model.
			case 0:
				allViews[nmbrOfView] = new RobotViewGroup1(model);
				break;
			case 1:
				allViews[nmbrOfView] = new RobotViewGroup2(model);
				break;
			case 2:
				allViews[nmbrOfView] = new RobotViewGroup3(model);
				break;
			}
			model->attach(allViews[nmbrOfView]); //Se lo attachea al modelo para que pueda updatear al mismo
			this->isViewActive[nmbrOfView] = true; 
		}
		else//Sino, se cierra la ventana.
		{
			model->deAttach(allViews[nmbrOfView]);
			delete allViews[nmbrOfView];
			this->isViewActive[nmbrOfView] = false;
		}
	}
}
RobotController::~RobotController()
{
}
