#include "stdafx.h"
//include header of this class
#include "Intensity.h"

//function that increases objects amount count
void Intensity::set_amount() {
	amount++;
}

//function that returns the count of the intensity object's amount variable
int Intensity::get_amount() {
	return amount;
}

//function that changes the Intensity object's variable histAmount with a specified int variable
void Intensity::set_histAmount(int n_amount) {
	hist_amount = n_amount;
}

//function that returns the count of the intensity object's histAmount variable
int Intensity::get_histAmount() {
	return hist_amount;
}

//function that calculates and sets the probability of an Intensity's value
//by dividing the count of the intensity-value by the given image's pixel amount
//which is passed through the function call
void Intensity::set_probability(int pixelAmount) {
	probability = (float)amount / pixelAmount;
}

//function that returns the probability of the intensity-value 
float Intensity::get_probability() {
	return probability;
}

//function that calculates and sets the culminated probability
float Intensity::set_culmProbability(float prevCulmProbability) {
	culmProbability = prevCulmProbability + probability;
	set_final_culmProbability();
	return culmProbability;
}

//function that returns the culminated probability
float Intensity::get_culmProbability() {
	return culmProbability;
}

//function that calculates and sets the final culminated probability or the new equalized value for
//the intensity-value
void Intensity::set_final_culmProbability() {
	final_culmProbability = floor(culmProbability * 255);
}

//function that returns the equalized intensity-value
int Intensity::get_final_culmProbability() {
	return final_culmProbability;
}
