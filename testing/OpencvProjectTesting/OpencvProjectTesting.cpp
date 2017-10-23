// OpencvProjectTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include "Intensity.h"
#include "cmath"

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("grayscale.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	char* source_image = "Source image";
	namedWindow(source_image, CV_WINDOW_AUTOSIZE);
	imshow(source_image, img);

	//Creates a spaceholder for the various bins[0, 255] in a histogram made up from the previous loaded image
	Intensity* histogram[255];

	//Goes through spaceholder and instantiates a Intensity object which holds the variables: 
	//(int) amount, (float) probability, (float) culmProbability, and (int) final_culmProbability.
	for (int i = 0; i < 256; i++) {
		histogram[i] = new Intensity();
	}

	//Goes through spaceholder. Depending on the value (intensity) of the pixel at: img.at<uchar>(j, i)
	//an array element is selected and the function set_amount() is called upon this element. 
	//Meaning if the pixel's intensity is 5, element histogram[5] will be chosen.
	//set_amount() increases the count of the various independent intensity.
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++)
		{
			histogram[img.at<uchar>(j, i)]->set_amount();
		}
	}
	//The histogram array now knows the amount of each intensity in the loaded image


	//Goes through spaceholder. For each element, the respective probability is calcuted. This is calcuted by taking the
	//amount of pixels which had the respective intensity and dividing by amount of pixels in the image (this information is sent
	//through the function call: set_probability(image_size))
	for (int i = 0; i < 256; i++) {
		histogram[i]->set_probability(img.rows*img.cols);
	}
	//The histogram now knows the probability of each intensity value in the loaded image

	//Goes through spaceholder. A culminated probability is calculated. To start the calculation a temp variable is passed through
	//the method call set_culmProbability(previous_culminated_probability). To begin the calculation this variable is initiliased as 0.
	float variableholder = 0;
	for (int i = 0; i < 256; i++) {
		variableholder = histogram[i]->set_culmProbability(variableholder);
	}
	//The histogram now knows the culminated probability of each intensity value in the loaded image

	//Goes through spaceholder. Based on each intensity value's culminated probability, a look up table is created
	//by multiplying each cumlniated probability with the intented maximum value. In this case 255.
	for (int i = 0; i < 256; i++) {
		histogram[i]->set_final_culmProbability();
	}


	//Creating the visualization of the histogram from the loaded image
	int hist_w = 512; int hist_h = 400;
	//bin_w is the amount of bins in the histogram. As it is intended to depict the various intensity's with their
	//respective pixel amount's, the length of the depicted histogram is devided by this value.
	int bin_w = cvRound((double)hist_w / 256);

	//Initialising the Mat object named histImage (The basic Image container). This is an object that will store the information 
	//of the visual representation of the histogram for the loaded image. 
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
	//CV: CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
	//So a image container with 8 bits per pixel, unsigned, and 1 channel is created

	//Goes through spaceholder. Finds the intensity with the highest amount of pixels with the respective intensity.
	int max = histogram[0]->get_amount();
	for (int i = 1; i < 256; i++) {
		if (max < histogram[i]->get_amount()) {
			max = histogram[i]->get_amount();
		}
	}

	//Goes through spaceholder. With the knowledge of the highest amount, a normalisation of the histogram array is done to vertically fit within
	//the visualisation of the histogram.
	for (int i = 0; i < 256; i++) {
		int temp = ((double)histogram[i]->get_amount() / max)*histImage.rows;
		histogram[i]->set_amount(temp);
	}

	
	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - histogram[i]->get_amount()),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	char* histogram_window = "Source image - histogram";
	namedWindow(histogram_window, CV_WINDOW_AUTOSIZE);
	imshow(histogram_window, histImage);

	//NEW IMAGE
	char* equalization_window = "Equalization image";
	namedWindow(equalization_window, CV_WINDOW_AUTOSIZE);


	Mat equalizationImage(img.rows, img.cols, CV_8UC1, Scalar(255, 255, 255));
	
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			int prev_intensity = (int)img.at<uchar>(i, j);
			int new_intensity = histogram[prev_intensity]->get_final_culmProbability();
			equalizationImage.at<uchar>(i, j) = new_intensity;
		}
	}

	imshow(equalization_window, equalizationImage);


	Intensity* eq_histogram[255];

	for (int i = 0; i < 256; i++) {
		eq_histogram[i] = new Intensity();
	}

	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++)
		{
			eq_histogram[equalizationImage.at<uchar>(j, i)]->set_amount();
		}
	}

	int eq_hist_w = 512; int eq_hist_h = 400;
	int eq_bin_w = cvRound((double)hist_w / 256);

	Mat eq_histImage(eq_hist_h, eq_hist_w, CV_8UC1, Scalar(255, 255, 255));

	int eq_max = eq_histogram[0]->get_amount();
	for (int i = 1; i < 256; i++) {
		if (eq_max < eq_histogram[i]->get_amount()) {
			eq_max = eq_histogram[i]->get_amount();
		}
	}

	for (int i = 0; i < 256; i++) {
		int eq_temp = ((double)eq_histogram[i]->get_amount() / eq_max)*eq_histImage.rows;
		eq_histogram[i]->set_amount(eq_temp);
	}

	for (int i = 0; i < 256; i++)
	{
		line(eq_histImage, Point(eq_bin_w*(i), eq_hist_h),
			Point(eq_bin_w*(i), eq_hist_h - eq_histogram[i]->get_amount()),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	char* eq_histogram_window = "Equalization image - histogram";
	namedWindow(eq_histogram_window, CV_WINDOW_AUTOSIZE);
	imshow(eq_histogram_window, eq_histImage);






	waitKey(0);
	
	return 1;

}

