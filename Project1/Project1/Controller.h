#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <vector>

using namespace std;

class Controller {
public:
    Controller() {};
    virtual void parseKeyboardEvent(void *Event)=0;
    //virtual void parseTimerEvent(void *Event)=0;
	//virtual void parseMouseEvent(void *Event)=0;
	//virtual void parseNetworkEvent(void *Event)=0;
    virtual ~Controller() {};
};

#endif /* CONTROLLER_H */

