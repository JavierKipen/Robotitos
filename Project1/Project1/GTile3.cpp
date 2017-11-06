#include "GTile3.h"



GTile3::GTile3()
{
}

bool GTile3::GetState(void)
{
	return tile.state;
}

position_t GTile3::GetLocation()
{
	return tile.ubicacion;
}

void GTile3::SetLocation(position_t newPos)
{
	tile.ubicacion = newPos;
}

void GTile3::SetState(bool state)
{
	tile.state = state;
}


GTile3::~GTile3()
{
}
