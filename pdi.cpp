#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>
#include <Windows.h>
#include <time.h>
#include "pdi.h"

using namespace cv;
using namespace std;

Mat gray, hsv;

char *imageName="lena.jpg";

Mat pdi::openImage(char *imageName){
	entrada = imread(imageName,1);
	return entrada;
}

void pdi::showImage(char*nome, Mat entrada){
	imshow(nome, entrada);
}

Mat pdi::convertBGR2Gray(Mat entrada){
	entrada=openImage(imageName);
	cvtColor(entrada,gray,CV_BGR2GRAY);
	return gray;
}

Mat pdi::convertBGR2HSV(Mat entrada){
	entrada=openImage(imageName);
	cvtColor(entrada,hsv,CV_BGR2HSV);
	return hsv;
}

void pdi::splitRGB(){
	
	entrada=openImage(imageName);
	
	vector<Mat>rgbChannels(3);
    split(entrada, rgbChannels); // Split the Channels BGR

	showImage("Blue",rgbChannels.at(0));
	showImage("Green",rgbChannels.at(1));
	showImage("Red", rgbChannels.at(2));

	imwrite("Blue.jpg", rgbChannels.at(0));
	imwrite("Green.jpg", rgbChannels.at(1));
	imwrite("Red.jpg", rgbChannels.at(2));
	
}

void pdi::splitHSV(){
	
	entrada=openImage(imageName);
	hsv=convertBGR2HSV(entrada);

	vector<Mat>hsvChannels(3);
    split(hsv, hsvChannels); // Split the Channels HSV

	showImage("HSV", hsv);
	showImage("H",hsvChannels.at(0));
	showImage("S",hsvChannels.at(1));
	showImage("V", hsvChannels.at(2));

	imwrite("HSV.jpg", hsv);
	imwrite("H.jpg", hsvChannels.at(0));
	imwrite("S.jpg", hsvChannels.at(1));
	imwrite("V.jpg", hsvChannels.at(2));
	
}


void pdi::medianAndMediaFilter(){
	
	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);

	int start,end,tmili;
	int i1, j1, i2, j2, order;
	float soma;

	Mat_<uchar>media(entrada.rows, entrada.cols, CV_32FC1);

	for (j1=0; j1<gray.rows; j1++){
		for (i1=0; i1<gray.cols; i1++){
			media.at<uchar>(j1, i1) = 0;
		}
	}

	printf ("\nPlease, enter the order:\t");
	scanf ("%d", &order);

	printf("\nMedia Filter in Progress...\n");

	start=(int)GetTickCount();

	for (j1=order/2; j1<gray.rows-order/2; j1++){
		for (i1=order/2; i1<gray.cols-order/2; i1++){
			soma=0;
			for (j2=-order/2; j2<=order/2; j2++){
				for (i2=-order/2; i2<=order/2; i2++){
					soma+=(float) gray.at<uchar>(j1+j2, i1+i2);
				}
			}
			media.at<uchar>(j1, i1) =(int)(soma/(order*order));
		}
	}

	end = (int)GetTickCount();
	tmili = end-start;

	printf("\nO tempo gasto para aplicar o filtro da media foi:\t%d ms\n", tmili);

	imshow ("MediaFilter", media);
	imwrite ("MediaFilter.jpg", media);

	int x1, y1, x2, y2;

	entrada = imread (imageName,1);
	cvtColor (entrada, gray, CV_RGB2GRAY);

	Mat_<uchar>median(entrada.rows, entrada.cols, CV_8UC3);

	for (y1=0; y1<gray.rows; y1++){
		for (x1=0; x1<gray.cols; x1++){
			median.at<uchar>(y1, x1) = 0;
		}
	}

	printf ("\nPlease, enter the order:\t");
	scanf ("%d", &order);

	int size = order*order;
	int* vetor = new int [size];
	int ordenador=1, i, aux;

	start=(int)GetTickCount();

	printf("\nMedian Filter in Progress...\n");

	for (y1=order/2; y1<gray.rows-order/2; y1++){
		for (x1=order/2; x1<gray.cols-order/2; x1++){
			i=0;
			ordenador=1;
			for (y2=-order/2; y2<=order/2; y2++){
				for (x2=-order/2; x2<=order/2; x2++){
					vetor [i] = gray.at<uchar>(y2+y1, x2+x1);
					i++;
				}
			}
			while ( ordenador<=size){
				for(i=0; i<size; i++){
					if(vetor[i] < vetor[i+1]){
						aux=vetor[i];
						vetor[i]=vetor[i+1];
						vetor[i+1]=aux;
					}
				}
				ordenador++;
			}
			median.at<uchar>(y1,x1)=vetor[size/2];
		}
	}

	end = (int)GetTickCount();
	tmili = end-start;
	
	printf("\nO tempo gasto para aplicar o filtro da mediana foi:\t%d ms\n", tmili);
	
	imshow("Mediana", median);
	imwrite("Mediana.jpg", median);
}

Mat pdi::cannyFilter(Mat entrada){
	
	Mat result;

	entrada=openImage(imageName);
	convertBGR2Gray(entrada);
	
	Canny(gray, result, 127, 200, 3);
	
	showImage("Canny", result);
	imwrite("Canny.jpg", result);

	return result;
}

void pdi::thresholdImage(){
	
	entrada=openImage(imageName);
	convertBGR2Gray(entrada);
	
	vector<Mat>limiarizada(5);
	
	threshold(gray,limiarizada.at(0),127,255,CV_THRESH_BINARY);      
	threshold(gray,limiarizada.at(1),127,255,CV_THRESH_BINARY_INV);  
	threshold(gray,limiarizada.at(2),127,255,CV_THRESH_TRUNC);       
	threshold(gray,limiarizada.at(3),127,255,CV_THRESH_TOZERO);      
	threshold(gray,limiarizada.at(4),127,255,CV_THRESH_TOZERO_INV);  

	showImage("LimiarBin",limiarizada.at(0));
	showImage("LimiarBinInv",limiarizada.at(1));
	showImage("LimiarTruncada",limiarizada.at(2));
	showImage("LimiarToZero",limiarizada.at(3));
	showImage("LimiarToZeroInv",limiarizada.at(4));

	imwrite("LimiarBin.jpg",limiarizada.at(0));
	imwrite("LimiarBinInv.jpg",limiarizada.at(1));
	imwrite("LimiarTrunc.jpg",limiarizada.at(2));
	imwrite("LimiarToZero.jpg",limiarizada.at(3));
	imwrite("LimiarToZeroInv.jpg",limiarizada.at(4));
}

void pdi::resizeImage(){
	 entrada=openImage(imageName);
	 convertBGR2Gray(entrada);

	 Mat maior(gray.cols*2,gray.rows*2,1);
	 Mat menor(gray.cols/2,gray.rows/2,1);
	 
	 resize(gray,maior,Size(maior.rows,maior.cols),1);
	 resize(gray,menor,Size(menor.rows,menor.cols),1);
	 
	 showImage("Maior",maior);
	 showImage("Menor",menor);
	 imwrite("Maior.jpg",maior);
	 imwrite("Menor.jpg",menor);
}

FILE* openFileWrite(FILE* file, char* nome){
	file=fopen(nome,"w");
	return file;
}

FILE* openFileRead(FILE* file, char* nome){
	file=fopen(nome,"r");
	return file;
}

void closeFile(FILE* file){
	fclose(file);
}

void pdi::matrixInFile(){
	 
	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);
	 
	outputFile=openFileWrite(outputFile,"Question9Results.txt");

	for(int y = 0; y < gray.rows; y++){
		for(int x = 0; x < gray.cols; x++){
			fprintf(outputFile,"%d  ", gray.at<uchar>(y,x));
		}
		fprintf(outputFile,"\n");
	}

	showImage("KoalaGray", gray);
	closeFile(outputFile);
}

void pdi::manualThresholding(){

	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);
	 
	outputFile=openFileWrite(outputFile,"Question10Results.txt");

	Mat_<Vec3b> img(gray.rows, gray.cols, CV_8UC3);

	for(int y = 0; y < gray.rows; y++){
		for(int x = 0; x < gray.cols; x++){
			if(gray.at<uchar>(y,x)<127){
				 img(y,x)[0]=0;
				 img(y,x)[1]=0;
				 img(y,x)[2]=0;
			 }
			 else{
				 img(y,x)[0]=255;
				 img(y,x)[1]=255;
				 img(y,x)[2]=255;
			 }
			 fprintf(outputFile,"%d ",img(y,x)[0]);
		 }
		 fprintf(outputFile,"\n");
	}

	showImage("ImageManualThresholding",img);
	imwrite("KoalaManualThresholding.jpg",img);
	closeFile(outputFile);
}
void pdi::centroidRectangle(){
	
	imageName="quadrado.jpg";
	
	Mat quadrado = openImage(imageName);
	
	gray=convertBGR2Gray(quadrado); 

	Mat_<Vec3b> img(gray.rows,gray.cols,CV_8UC3);

	for(int y=0;y<gray.rows;y++){
		for(int x=0;x<gray.cols;x++){
			if((x==gray.cols/2)&&(y==gray.rows/2)){
				img(y,x)[0]=0;
				img(y,x)[1]=0;
				img(y,x)[2]=255;
			}
			else{
				img(y,x)[0]=gray.at<uchar>(y,x);
				img(y,x)[1]=gray.at<uchar>(y,x);
				img(y,x)[2]=gray.at<uchar>(y,x);
			}
		}
	}

	showImage("Quadrado",quadrado);
	showImage("Centro",img);
	
	imwrite("Centro.jpg",img);
}

void pdi::fileToImage(){
	
	char val[5000];
	int  val2 , linhas =-1 , colunas=-1;

	imputFile=openFileRead(imputFile,"Question10Results.txt");

	while(!feof(imputFile)){
		fgets(val,5000,imputFile);
		linhas++;
	}

	closeFile(imputFile);

	imputFile=openFileRead(imputFile,"Question10Results.txt");

	while(!feof(imputFile)){
		fscanf(imputFile,"%d",&val2);
		colunas++;
	}
	colunas=colunas/linhas;
	
	closeFile(imputFile);

	imputFile=openFileRead(imputFile,"Question10Results.txt");

	Mat_<Vec3b> img(linhas,colunas,CV_8UC3);
	
	for(int y=0;y<linhas;y++){
		for(int x=0;x<colunas;x++){
			fscanf(imputFile,"%d",&val2);
			img(y,x)[0]=val2;
			img(y,x)[1]=val2;
			img(y,x)[2]=val2;
		}
	}

	showImage("GrayScaleFromFile",img);
	imwrite("GrayScaleFromFile.jpg",img);
	
	fclose(imputFile);
}

void pdi:: sobelFilter(){

	int sobelHorizontal[3][3]={-1, 0, 1, -2, 0, 2, -1, 0, 1};
	int sobelVertical[3][3]={-1, -2, -1, 0, 0, 0, 1, 2, 1};

	entrada = openImage(imageName);
	
	Mat_<uchar>gray(entrada.rows, entrada.cols, CV_8UC3) ;
	gray=convertBGR2Gray(entrada);
	
	int somaHorizontal, somaVertical, ordem=3;
	int y1, y2, x1, x2;

	Mat_<uchar>sobel(entrada.rows, entrada.cols, CV_8UC3);

	for (y1=0; y1<gray.rows; y1++){
		for (x1=0; x1<gray.cols; x1++){
			sobel.at<uchar>(y1, x1) = 0;
		}
	}

	int start,end,tmili;
	start=(int)GetTickCount();

	printf("\nSobel Filter in Progress...\n");

	for (y1=ordem/2; y1<gray.rows-ordem/2; y1++){
		for (x1=ordem/2; x1<gray.cols-ordem/2; x1++){
			somaHorizontal=0;
			somaVertical=0;
			for (y2=-ordem/2; y2<=ordem/2; y2++){
				for (x2=-ordem/2; x2<=ordem/2; x2++){
					somaHorizontal+=gray.at<uchar>(y2+y1, x2+x1)*sobelHorizontal[y2+1][x2+1];
					somaVertical+=gray.at<uchar>(y2+y1, x2+x1)*sobelVertical[y2+1][x2+1];
				}
			}
			sobel.at<uchar>(y1, x1)=(uchar)(sqrt(pow(somaHorizontal,2)+pow(somaVertical,2)));
		}
	}

	end = (int)GetTickCount();
	tmili = end-start;

	printf("\nO tempo gasto para aplicar o filtro Sobel foi:\t%d ms\n", tmili);

	imshow ("Sobel Filter", sobel);
	imwrite ("Sobel.jpg", sobel);
}

void pdi::captureFrame(){
	
	VideoCapture cap(1); 
	Mat frame;

	while (1){
		cap >> frame; 
		Mat cinza = convertBGR2Gray(frame); 
		showImage("VideoCapture", cinza);
		cvWaitKey(10);
	}
}

void pdi::captureFrameAndCanny(){
	
	Mat frame;
	VideoCapture cap(1);
	//namedWindow("VideoCapture",CV_WINDOW_AUTOSIZE);
	 
	while (1){
		cap >> frame;
		Mat canny = cannyFilter(frame);
		imshow("VideoCapture",canny);
		cvWaitKey(10);
	}
}

Mat pdi::histograma(Mat entrada){

	int cont;
	int vector[256];
	int ma , me , norma ;
	
	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);

	for(int x=0;x<256;x++){
		vector[x]=0;
	}

	for(int y=0;y<gray.rows;y++){
		for(int x=0;x<entrada.cols;x++){
			cont=0;
			cont=gray.at<uchar>(y,x);
			vector[cont]++;
		}
	}

	for(int x=0;x<256;x++){
		if(x==0){
			ma=vector[x];
			me=vector[x];
		}
		else if(ma<vector[x]){
			ma=vector[x];
		}
		else if(me>vector[x]){
			me=vector[x];
		}
	}

	norma=ma/192+3;
	
	for(int x=0;x<256;x++){
		vector[x]=vector[x]/norma;
	}

	Mat_<Vec3b> hist(192,256,CV_8UC3);

	for(int y=0;y<hist.rows;y++){
		for(int x=0;x<hist.cols;x++){
			if(y>=hist.rows-vector[x]){
				hist(y,x)[0]=0;
				hist(y,x)[1]=0;
				hist(y,x)[2]=0;
			}
			else{
				hist(y,x)[0]=255;
				hist(y,x)[1]=255;
				hist(y,x)[2]=255;
			}
		}
	}

	showImage("Histograma", hist);
	imwrite("Histograma.jpg", hist);
	
	return hist;
}

Mat pdi::equalizer(){
	
	Mat equalizada, histEqualizada;

	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);

	equalizeHist(gray,equalizada);
	//histEqualizada=histograma(equalizada);

	showImage("Equalizado", equalizada);
	imwrite("Equalizado.jpg", equalizada);
	
	return equalizada;
}

Mat pdi::equalizerManual(Mat entrada){
	
	entrada=openImage(imageName);
	gray=convertBGR2Gray(entrada);

	int x, y, ma=0, me=0;
	
	for(y=0;y<gray.rows;y++){
		for(x=0;x<gray.cols;x++){
			if((y==0)&&(x==0)){
				ma=gray.at<uchar>(y,x);
				me=gray.at<uchar>(y,x);
			}
			else if(gray.at<uchar>(y,x)>ma){
				ma=gray.at<uchar>(y,x);
			}
			else if(gray.at<uchar>(y,x)<me){
				me=gray.at<uchar>(y,x);
			}
		}
	}

	printf("O MAIOR VALOR DE PIXEL NA IMAGEM E : %d\n", ma);
	printf("O MENOR VALOR DE PIXEL NA IMAGEM E : %d\n\n", me);
	
	Mat_<Vec3b> equalized(gray.rows,gray.cols,CV_8UC3);
	
	for(y=0;y<gray.rows;y++){
		for(x=0;x<gray.cols;x++){
			equalized(y,x)[0] = (255*(gray.at<uchar>(y,x)-me)/(ma-me));
			equalized(y,x)[1] = equalized(y,x)[0];
			equalized(y,x)[2] = equalized(y,x)[0];
		}
	}
	
	showImage("Equalizada", equalized);
	imwrite("EqualizadaManual.jpg", equalized);

	return equalized;
}

void pdi::laplacianAndEqualizer(){
	
	entrada=openImage(imageName);
	
	Mat laplaciano, absLaplaciano, equalized;

	GaussianBlur(entrada, entrada, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(entrada,gray,CV_RGB2GRAY);
	Laplacian(gray, laplaciano, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(laplaciano, absLaplaciano);

	equalized=equalizerManual(absLaplaciano);

	showImage("Laplace",laplaciano);
	imwrite("Laplace.jpg",laplaciano);
	showImage("LaplaceEqualizada",laplaciano);
	imwrite("LaplaceEqualizada.jpg",laplaciano);
}

void pdi::sobelAndGradiente(){
	
	entrada = openImage(imageName);
	gray=convertBGR2Gray(entrada);

	Mat hist, hist2;

	hist=histograma(gray);

	long int dx, dy;
	
	Mat_<Vec3b> mat = openImage(imageName);
	Mat_<Vec3b> gradiente(gray.rows,gray.cols,CV_8UC3);
	 
	for(int y=0;y<gradiente.rows;y++){
		for(int x=0;x<gradiente.cols;x++){
			gradiente(y,x)[0]=0;
			gradiente(y,x)[1]=0;
			gradiente(y,x)[2]=0;
		}
	}
	 
	for(int y=1;y< gradiente.rows -1 ;y++){
		for(int x=1;x< gradiente.cols -1 ;x++){
			dx = (1)*mat(y-1,x-1)[0] + (2)*mat(y-1,x)[0] + (1)*mat(y-1,x+1)[0] + (-1)*mat(y+1,x-1)[0] + (-2)*mat(y+1,x)[0] + (-1)*mat(y+1,x+1)[0]; 
			dy = (1)*mat(y-1,x-1)[0] + (-1)*mat(y-1,x+1)[0] + (2)*mat(y,x-1)[0] + (-2)*mat(y,x+1)[0] + (1)*mat(y+1,x-1)[0] + (-1)*mat(y+1,x+1)[0];
			gradiente(y,x)[0] = (int)sqrt(pow(dx,2)+pow(dy,2));
			gradiente(y,x)[1] = gradiente(y,x)[0];
			gradiente(y,x)[2] = gradiente(y,x)[0];
		}
	}

	hist2=histograma(gradiente);

	showImage("Histograma", hist);
	imwrite("Histograma.jpg", hist);
	
	showImage("HistogramaSobel", hist2);
	imwrite("HistogramaSobel.jpg", hist2);
	
	showImage("Sobel19", gradiente);
	imwrite("Sobel19.jpg", gradiente);

}

