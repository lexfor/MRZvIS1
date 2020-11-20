#include "neural_network.h"
#include <thread>
neural_network::neural_network() {
	Cmax = 255;
	n = 2;
	m = 2;
	a = 0.00001;
	maxError = 100;
	Err = 0;
	p = 3;
}

void neural_network::setImg(cimg_library::CImg<double> Im) {
	im = Im;
}

void neural_network::showImg() {
	im.display("Image");
}

void neural_network::showRez() {
	rezIm.display("Image");
}

double neural_network::Ci(double Cijk) {
	double rez = 2 * Cijk;
	rez /= Cmax;
	rez -= 1;
	return rez;
}

void neural_network::imgToMatrix() {
	int tempWidth = im.width() / m;
	int tempHeight = im.height() / n;
	for (int i = 0, q = 0; i < tempWidth * m; i += m) {
		for (int j = 0; j < tempHeight * n; j += n, q++) {
			std::vector<std::vector<double>> input;
			for (auto k = j; k < j + n; k++) {
				for (auto o = i; o < i + m; o++) {
					std::vector<double> imag;
					for (auto t = 0; t < 3; t++) {
						imag.emplace_back(Ci(im(o, k, 0,t)));
					}
					input.emplace_back(imag);
				}
			}
			in.emplace_back(Matrix(input));
		}
	}
}

void neural_network::learn() {
	int count = 0;
	int matCount;
	do {
		Err = 0;
		matCount = 0;
		for (auto i : in) {
			matCount++;
			i.toInput();
			Matrix y, z,u, deltaX, deltaY;
			y = i * firstWeights;
			z = y * secondWeights;
			u = z * firstWeights;
			deltaX = z - i;
			deltaY = u - y;
			//std::thread th1(&neural_network::ChangeFirstWieghts, this, z, deltaY);
			//std::thread th2(&neural_network::ChangeSecondWeights, this, y, deltaX);

			firstWeights = firstWeights - z.Transposition() * a * deltaY;
			secondWeights = secondWeights - y.Transposition() * a * deltaX;
			/*deltaY = u - y;
			firstWeights = firstWeights - i.Transposition() * a * deltaY;
			secondWeights = secondWeights - y.Transposition() * a * deltaX;*/
			Err += deltaX.square();
			//th1.join();
			//th2.join();
		}
		count++;
		std::cout<<"Error : "<< Err / in.size() << std::endl;
		std::cout<<"Epoch : "<< count << std::endl;
	} while (Err / in.size() > 0.05);//(Err / in.size() > 0.3)(count < 10);
}

void neural_network::setMaxErorr(double Err) {
	maxError = Err;
}

double neural_network :: Uk(double Xi) {
	double rez = Cmax * (Xi + 1) / 2;
	if (rez < 0) {
		rez = 0;
	}
	if (rez > 255) {
		rez = 255;
	}
	return rez;
}

void neural_network::initializeWeights() {

	std::vector<std::vector<double>> Mat;
	for (auto j = 0; j < n * m *3; j++) {
		std::vector<double> Weights;
		for (auto i = 0; i < p; i++) {
			Weights.emplace_back((double)(rand()) / RAND_MAX);
		}
		Mat.emplace_back(Weights);
	}
	firstWeights.setData(Mat);
	secondWeights = firstWeights.Transposition();
	firstWeights.print();
	secondWeights.print();
}

void neural_network::MatrixToImg() {
	cimg_library::CImg<double> image(im.width(), im.height(), 1, 3);
	int tempWidth = im.width() / m;
	int tempHeight = im.height() / n;
	for (int i = 0, q = 0; i < tempWidth * m; i += m) {
		for (int j = 0; j < tempHeight * n; j += n,q++) {
			std::vector<std::vector<double>> rezult;
			rezult = rez[q].getData();
			for (auto k = j,w = 0; k < j + n; k++) {
				for (auto o = i; o < i + m; o++) {
					for (auto t = 0; t < 3; t++, w++) {
						image(o, k, 0, t) = Uk(rezult[0][w]);
					}
				}
			}
		}
	}
	rezIm = image;
	rezIm.save("D:\\rez.bmp");
}

void neural_network::start() {
	for (auto i : in) {
		Matrix y, z;
		i.toInput();
		y = i * firstWeights;
		z = y * secondWeights;
		rez.emplace_back(z);
	}

}

void neural_network::Coef() {
	double k;
	k = (n * m * 3 * in.size() )/( (n * m * 3 + in.size()) * p + 2);
	std::cout << "compression ratio : " << k << std::endl;;
}

void neural_network::setSize() {
	std::cout << "m : ";
	std::cin >> m;
	std::cout << std::endl;
	std::cout << "n : ";
	std::cin >> n;
	std::cout << std::endl;
}

void neural_network::ChangeFirstWieghts(Matrix x,Matrix delta) {
	firstWeights = firstWeights - x.Transposition() * a * delta;
}

void neural_network::ChangeSecondWeights(Matrix x, Matrix delta) {
	secondWeights = secondWeights - x.Transposition() * a * delta;
}