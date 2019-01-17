#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>
#include <stdio.h>
#include "pdi.h"

using namespace cv;
using namespace std;


Mat entrada;
pdi image; 
Mat hist, histEqualizada;
int control=1, opcao;

int main(){


	printf("           \tPara visualizar os resultados encerre o programa.\n");
	printf("           \tA imagem Resultante ficara na tela por 5 segundos.\n\n");

	do{
		do{
			printf("\nEnter the processing you want to apply the image\n\n1 - Convert the image to grayscale\t2 - Split channels BGR\n");
			printf("3 - Split channels HSV\t\t\t4 - apply the median filter\n5 - Apply the Canny filter\t\t6 - Apply a thresholding\n");
			printf("7 - Resize Image\t\t\t8 - Extract pixels to a File\n9 - Apply a Manual Thresholding\t\t10 - Find the Centroid (Rectangle)\n");
			printf("11 - Extract the file to image\t\t12 - Apply the Sobel filter\n13 - Capture Video on WebCam\t\t14 - Capture Video");
			printf(" and apply the Canny\n15 - Generate Histogram\t\t\t16 - Equalize Image\n17 - Equalize manually\t\t\t18 - Laplace and Equalize");
			printf("\n19 - Sobel and Gradiente\t\t20 - End The Program\n\n");
			scanf_s("%d", &opcao);
			if (opcao<1 || opcao>20){
				printf("\nPlease, enter a valid option!\n");
			}
		} while (opcao<1 || opcao>20);

		switch (opcao){
		
			case 1:
				image.convertBGR2Gray(entrada);
			break;

			case 2:
				image.splitRGB();
			break;
			
			case 3:
				image.splitHSV();
			break;

			case 4:
				image.medianAndMediaFilter();
			break;

			case 5:
				image.cannyFilter(entrada);
			break;

			case 6:
				image.thresholdImage();
			break;

			case 7:
				image.resizeImage();
			break;

			case 8:
				image.matrixInFile();
			break;

			case 9:
				image.manualThresholding();
			break;

			case 10:
				image.centroidRectangle();
			break;

			case 11:
				image.fileToImage();
			break;

			case 12:
				image.sobelFilter();
			break;

			case 13:
				printf("\n\nCaso nao abra a janela com a captura de video, certifique-se que o seu software de antivirus nao reconhece esse");
				printf("processo como malicioso\n\n");
				image.captureFrame();
			break;

			case 14:
				printf("\n\nCaso nao abra a janela com a captura de video, certifique-se que o seu software de antivirus nao reconhece esse");
				printf("processo como malicioso\n\n");
				image.captureFrameAndCanny();
			break;

			case 15:
				image.histograma(entrada);
			break;
				
			case 16:
				image.equalizer();
			break;

			case 17:
				image.equalizerManual(entrada);
			break;

			case 18:
				image.laplacianAndEqualizer();
			break;

			case 19:
				image.sobelAndGradiente();
			break;

			case 20:
				control=0;
			break;
		}

	} while (control==1);
	
	printf("\n");
	
	cvWaitKey(5000);
	system("pause");
	return 0;
}