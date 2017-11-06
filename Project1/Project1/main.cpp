#include <iostream>
#include <chrono>
#include <thread>
#include "AllegroEG.h"
#include "RobotModel.h"
#include "RobotController.h"

int main()
{
	allegro_startup(); //Em este ejemplo se debe inicializar allegro por fuera debido a que los eventos son de allegro.
	RobotModel model;			//El modelo y el controlador van a ser siempre los mismos
	RobotController controller;
	controller.attachModel(&model);
	model.startSym();			//Se iniciará la simulación
	ALLEGRO_DISPLAY *displayAtrapaEventos = al_create_display(1000, 800);  //Este display tiene que estar para que sucedan los eventos de allegro.
	while (!model.simEnded()) //Mientras que no se haya terminado la simulación
	{
		model.tick();				//Se moverá una posición los robotitos
		if (controller.hayEvento())		//Y se le dará el control de los eventos al controller
			controller.parseEvento();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	allegro_shut_down();
	return 0;
}