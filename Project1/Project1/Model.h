#ifndef MODEL_H
#define MODEL_H

#include "Observer.h"
#include <list>


class Model {
public:
    Model();
    Model(const Model& orig);
    virtual ~Model();
    void attach(Observer * view);
    void deAttach(Observer * view);
protected:
    void notifyAllObservers(); //Donde se llamará todos los observers a updatearse
private:
    std::list<Observer *> observers;  //Todos los views que estaràn pendientes de este modelo

};

#endif /* MODEL_H */

