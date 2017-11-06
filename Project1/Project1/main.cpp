#include <iostream>
#include <chrono>
#include <thread>
#include "AllegroEG.h"
#include "RobotModel.h"
#include "RobotController.h"

int main()
{
	allegro_startup();
	RobotModel model;
	RobotController controller;
	controller.attachModel(&model);
	model.startSym();
	while (!model.simEnded())
	{
		model.tick();
		if (controller.hayEvento())
			controller.parseEvento();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//list<RobotPos> robots= model.getRobotsInfo();
		//list<TileInfo> tileinfo = model.getTileInfo();
	}

	allegro_shut_down();
	return 0;
}