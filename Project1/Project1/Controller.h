#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <vector>

using namespace std;

class Controller {
public:
    Controller() {};
    virtual void parseKeyboardEvent(void *mouseEvent)=0;
    virtual void parseTimerEvent(void *mouseEvent)=0;
    virtual ~Controller() {};
};

#endif /* CONTROLLER_H */

