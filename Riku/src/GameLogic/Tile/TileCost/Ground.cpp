// Kacper Walasek
#include "Ground.h"

Ground::Ground(std::string name, double mult)
	: Resource(name), mult(mult) 
{}

double Ground::getModifiedCost(double cost) const
{
	return cost * mult;
}
