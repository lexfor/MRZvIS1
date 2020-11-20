#pragma once
//#include "Neuron.h"
#include "Matrix.h"
#include "CImg/CImg.h"
#include <iostream>

class neural_network
{
private:
	cimg_library :: CImg<double> im;
	cimg_library::CImg<double> rezIm;
	std::vector<Matrix> in;
	Matrix firstWeights;
	Matrix secondWeights;
	std::vector<Matrix> rez;
	int Cmax;
	int n;
	int m;
	int p;
	double a;
	double maxError;
	double Err;
public:
	neural_network();
	void setMaxErorr(double);
	void setSize();
	void initializeWeights();
	void setImg(cimg_library::CImg<double>);
	void showImg();
	void showRez();
	double Ci(double);
	void imgToMatrix();
	void learn();
	double Uk(double Xi);
	void MatrixToImg();
	void start();
	void Coef();
	void ChangeFirstWieghts(Matrix, Matrix);
	void ChangeSecondWeights(Matrix, Matrix);
};

