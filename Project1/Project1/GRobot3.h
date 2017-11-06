#pragma once
typedef struct
{
	double x;
	double y;
}pos_t;

typedef struct
{
	pos_t pos;
	double angle;
	unsigned int unit;

}robot_t;

class GRobot3
{
public:
	GRobot3();
	~GRobot3();
	pos_t GetPos();
	double GetDir();
	void SetDir(double angle);
	void SetPos(pos_t newPos);
private:
	robot_t robot;
};

