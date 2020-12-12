#include "neural_network.h"
#include "CImg/CImg.h"
#include "PictureStream.h"
#include "PixelMatrix.h"
using namespace cimg_library;
int main() {
	neural_network my_Network;
	CImg<double> image("D:\\12.bmp");
	my_Network.setImg(image);
	my_Network.showImg();
	my_Network.setSize();
	my_Network.imgToMatrix();
	my_Network.initializeWeights();
	my_Network.learn();
	my_Network.start();
	my_Network.MatrixToImg();
	my_Network.showRez();
	my_Network.Coef();
}