#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include "Controller.h"
#include "RobotModel.h"
#include "AllegroEG.h"
#include "RobotViewGroup1.h"
typedef enum {R_ALLEGRO_EVENT, R_NETWORK_EVENT} EventType;

#define VIEWS_COUNT 3

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
	bool isViewActive[VIEWS_COUNT];
	Observer *allViews[VIEWS_COUNT];
};
#endif

