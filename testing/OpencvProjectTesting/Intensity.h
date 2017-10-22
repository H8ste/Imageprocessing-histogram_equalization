#pragma once
#include "cmath"

class Intensity
{
	int amount = 0;
	int final_culmProbability;
	float probability, culmProbability;
public:
	void set_amount();
	void set_amount(int n_amount);
	int get_amount();
	void set_probability(int);
	float get_probability();
	float set_culmProbability(float);
	float get_culmProbability();
	void set_final_culmProbability();
	int get_final_culmProbability();
};

/*
void Intensity::set_amount() {
	amount++;
}

int Intensity::get_amount() {
	return amount;
}

void Intensity::set_probability(int pixelAmount) {
	probability = (float) amount / pixelAmount;
}

float Intensity::set_culmProbability(float prevCulmProbability) {
	culmProbability = prevCulmProbability + probability;
	set_final_culmProbability();
	return culmProbability;
}
void Intensity::set_final_culmProbability() {
	final_culmProbability = (int) floor(culmProbability) * 255;
}

int Intensity::get_final_culmProbability() {
	return final_culmProbability;
}
*/