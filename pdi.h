#ifndef pdi_h
#define pdi_h

#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;

class pdi {
	public:
		Mat openImage(char *imageName);
		void showImage(char*nome, Mat entrada);
		Mat convertBGR2Gray(Mat entrada);
		Mat convertBGR2HSV(Mat entrada);
		void splitRGB();
		void splitHSV();
		void medianAndMediaFilter();
		Mat cannyFilter(Mat entrada);
		void thresholdImage();
		void resizeImage();
		void matrixInFile();
		void manualThresholding();
		void centroidRectangle();
		void fileToImage();
		void sobelFilter();
		void captureFrame();
		void captureFrameAndCanny();
		Mat histograma(Mat entrada);
		Mat equalizer();
		Mat equalizerManual(Mat entrada);
		void laplacianAndEqualizer();
		void sobelAndGradiente();
	private:
		Mat entrada; FILE* imputFile; FILE* outputFile;
};

#endif;