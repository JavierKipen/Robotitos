//// ------------------ ////
//// SIMULATION LIBRARY ////
//// ------------------ ////
#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ONE_STEP 1
#define ALL_STEPS 2

#include <stdbool.h>

typedef struct
{
	unsigned int mode;
	unsigned int width;
	unsigned int height;
	unsigned int robots_count;
}paramsType; // Userdata parametros

typedef struct
{
	double x;
	double y;
}posType; // Estructura de coordenadas

typedef struct
{
	posType pos;
	double angulo; // 0 <Angulo < 360
}robotType; // Estructura del robot

typedef bool tileType; // Tipo de dato de baldosa

typedef struct
{
	unsigned int width;
	unsigned int height;
	tileType * baldosas;
}pisoType; // Estructura de piso

typedef struct
{
	robotType * robots;
	unsigned int robotCount;
	pisoType * piso;
	unsigned int width;
	unsigned int height;
	unsigned long int tickCount;
}simType; // Estructura de la simulacion



// Others

double deg2rad(double angulo_deg);

// Robot Managment

robotType * createRobot(unsigned int  count, unsigned int height, unsigned int width); //se asume que se inicializa el seed para el random

void moveRobot(robotType * robots, unsigned int height, unsigned int width); 

void moveRobots(robotType * robots, unsigned int height, unsigned int width, unsigned int robotCount);

posType getRobotPos(robotType * robot);

void destroyRobots(robotType * robot);

// Floor Managment

pisoType * createFloor(unsigned int width, unsigned int height);

bool getTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna);

void changeTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna, bool value);

void destroyFloor(pisoType * piso);

// Simulation Managment

simType * createSim(unsigned int robotCount, unsigned int height, unsigned int width);

void destroySim(simType * simulation);

void clean_floor(simType * sim, unsigned int * floorCleaned);

void init_arr(double * ptr2arr, unsigned int size);

unsigned int simulate(simType * sim, unsigned int * tickCount);

unsigned int simulate_quick(simType * sim);

#endif /* SIMULATION_H */

