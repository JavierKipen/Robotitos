#pragma once


typedef struct
{
	double x;
	double y;
}position_t;

typedef struct
{
	unsigned int heigth;
	unsigned int width;
	position_t ubicacion; //se considera la ubicacion respecto del centro de la baldosa.
	bool state;
}piso_t;



class GTile3
{
public:
	GTile3();
	bool GetState(void);
	position_t GetLocation();
	void SetLocation(position_t newPos);
	void SetState(bool state);
	~GTile3();
private:
	piso_t tile;

};

