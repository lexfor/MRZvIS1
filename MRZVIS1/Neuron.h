#pragma once
#include <vector>
#include <assert.h>
#include "CImg/CImg.h"
class Neuron
{
private:
	std::vector<double> inputs;
	std::vector<double> reverseInputs;
	std::vector<double> weights;
	enum class activation_function
	{
		linear
	}function;
public:
	Neuron();
	Neuron(std::vector<double>, std::vector<double>);
	void setInputs(std::vector<double>Inputs);
	void setReverseInputs(std::vector<double>);
	void setWeights(std::vector<double>Weights);
	void setActivationFunction(int);
	double getSumm();
	std::vector<double> getSplit();
	int checkSizes();
	std::vector<double> activate();
	std::vector<double> reverseActivate();
};

