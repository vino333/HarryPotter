#include "Energy.h"



Energy::Energy(int i, int j)
	:Collectable("energy",i,j)
{
}


Energy::~Energy()
{
}

// registering to factory
bool Energy::m_registerit = Factory<StaticObject,char,int>::registerit('P',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Energy>(i,j); });