#include "stdafx.h"
#include "Intensity.h"
/*
class Intensity
{
	int amount = 0;
	int final_culmProbability;
	float probability, culmProbability;
public:
	void set_amount();
	void set_probability(int);
	int set_culmProbability(int);
	void set_final_culmProbability();
};
*/

void Intensity::set_amount() {
	amount++;
}

void Intensity::set_amount(int n_amount) {
	amount = n_amount;
}

int Intensity::get_amount() {
	return amount;
}

void Intensity::set_probability(int pixelAmount) {
	probability = (float)amount / pixelAmount;
}

float Intensity::get_probability() {
	return probability;
}

float Intensity::set_culmProbability(float prevCulmProbability) {
	culmProbability = prevCulmProbability + probability;
	set_final_culmProbability();
	return culmProbability;
}

float Intensity::get_culmProbability() {
	return culmProbability;
}
void Intensity::set_final_culmProbability() {
	final_culmProbability = floor(culmProbability * 255);
}

int Intensity::get_final_culmProbability() {
	return final_culmProbability;
}
