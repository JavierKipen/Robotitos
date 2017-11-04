#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include "Controller.h"
#include "RobotModel.h"
#include "AllegroEG.h"
typedef enum {R_ALLEGRO_EVENT, R_NETWORK_EVENT} EventType;

class RobotController :
	public Controller
{
public:
	RobotController();
	bool attachModel(RobotModel *model);
	bool hayEvento();
	void parseEvento();
	void parseKeyboardEvent(void *mouseEvent);
	~RobotController();
private:
	RobotModel *model;
	AllegroEG allegroEG;
	EventType eventType;
};
#endif

