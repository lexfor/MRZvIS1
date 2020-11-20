#include "Neuron.h"
Neuron::Neuron() {
	function = activation_function::linear;
}
Neuron::Neuron(std::vector<double> Inputs, std::vector<double>Weights) {
	inputs = Inputs;
	weights = Weights;
}
void Neuron::setInputs(std::vector<double>Inputs) {
	inputs = Inputs;
}
void Neuron::setReverseInputs(std::vector<double>Inputs) {
	reverseInputs = Inputs;
}
void Neuron::setWeights(std::vector<double>Weights) {
	weights = Weights;
}
void Neuron::setActivationFunction(int Choise) {
	switch (Choise)
	{
	case 1:
		function = activation_function::linear;
		break;
	default:
		break;
	}
}
double Neuron::getSumm() {
	double rez = 0;
	for (auto i = 0; i < inputs.size(); i++) {
		rez += inputs[i] * weights[i];
	}
	return rez;
}

std::vector<double> Neuron::getSplit() {
	std::vector<double> rez;
	for (auto i : reverseInputs) {
		for (auto j = 0; j < weights.size(); j++) {
			rez.push_back(i * weights[j]);
		}
	}
	return rez;
}

int Neuron::checkSizes() {
	if (inputs.size() == weights.size()) {
		return 0;
	}
	else {
		return 1;
	}
}
std::vector<double> Neuron::activate() {
	std::vector<double> rez;
	switch (function)
	{
	case activation_function::linear:
		for (auto i = 0; i < 3; i++) {
			rez.push_back(inputs[i] * weights[i]);
		}
		return rez;
		break;
	default:
		break;
	}
}

std::vector<double> Neuron::reverseActivate() {
	std::vector<double> rez;
	switch (function)
	{
	case activation_function::linear:
		rez = getSplit();
		for (auto i = 0; i < rez.size(); i++) {
			rez[i] *= weights[i];
		}
		return rez;
		break;
	default:
		break;
	}
}