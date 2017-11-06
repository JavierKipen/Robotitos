#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#include "Controller.h"
#include "RobotModel.h" //Debe conocer al modelo que controlará, así como a los views que le asignará
#include "AllegroEG.h"
#include "RobotViewGroup1.h"
#include "RobotViewGroup2.h"
#include "RobotViewGroup3.h"
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
	void parseKeyboardEvent(void *mouseEvent); //Decide que hacer con un evento de keyboard
	~RobotController();
private:
	RobotModel *model;
	AllegroEG allegroEG;
	EventType eventType;
	bool isViewActive[VIEWS_COUNT];
	Observer *allViews[VIEWS_COUNT];
};
#endif

