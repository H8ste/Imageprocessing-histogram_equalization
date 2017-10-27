#pragma once
#include "cmath"
//header for the class Intensity
class Intensity
{
	int amount = 0;
	int final_culmProbability, hist_amount;
	float probability, culmProbability;
public:
	void set_amount();
	int get_amount();
	void set_histAmount(int n_amount);
	int get_histAmount();
	void set_probability(int);
	float get_probability();
	float set_culmProbability(float);
	float get_culmProbability();
	void set_final_culmProbability();
	int get_final_culmProbability();
};