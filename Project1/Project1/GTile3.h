#pragma once


typedef struct
{
	double x;
	double y;
}pos_t;

typedef struct
{
	unsigned int heigth;
	unsigned int width;
	pos_t ubicacion; //se considera la ubicacion respecto del centro de la baldosa.
	bool state;
}piso_t;





class GTile3
{
public:
	GTile3();
	bool GetState(void);
	pos_t GetLocation();
	void SetLocation(pos_t newPos);
	void SetState(bool state);
	~GTile3();
private:
	piso_t tile;

};

