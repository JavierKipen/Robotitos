#include <iostream>
#include "AllegroEG.h"
#include "RobotModel.h"
#include "RobotController.h"

int main()
{
	allegro_startup();
	RobotModel model;
	RobotController controller;
	controller.attachModel(&model);
	while (!model.simEnded())
	{
		if (controller.hayEvento())
			controller.parseEvento();
	}

	allegro_shut_down();
	return 0;
}