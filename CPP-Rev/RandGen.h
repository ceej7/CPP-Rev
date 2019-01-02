#ifndef RANDGEN
#define RANDGEN
class RandGen
{

public:
	void testRand();
	void setRoot();
	int getRand();
	int getRand(int _min, int _max);
private:
	bool isInI=false;
};
#endif