#include "Model.h"

#include <algorithm>
using namespace std;

Model::Model() {
}

Model::Model(const Model& orig) {
}

Model::~Model() {
}

void Model::attach(Observer * view)
{
    if(view != nullptr)
        observers.push_back(view);
}
void Model::deAttach(Observer * view)
{
	list<Observer *>::iterator it = find(observers.begin(),observers.end(),view);
	if (it != observers.end())
		observers.erase(it);
}

void Model::notifyAllObservers() 
{
    for(auto& ob : observers)
        ob->update();
}