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
	//Mat img = imread("low-contrast.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img = imread("grayscale.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	char* source_image = "Source image";
	namedWindow(source_image, CV_WINDOW_AUTOSIZE);
	imshow(source_image, img);
	Intensity* histogram[255];

	for (int i = 0; i < 256; i++) {
		histogram[i] = new Intensity();
	}

	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++)
		{
			histogram[img.at<uchar>(j, i)]->set_amount();
		}
	}

	//testing
	for (int i = 0; i < 256; i++) {
	}

	for (int i = 0; i < 256; i++) {
		histogram[i]->set_probability(img.rows*img.cols);
	}

	float temp = 0;
	for (int i = 0; i < 256; i++) {
		temp = histogram[i]->set_culmProbability(temp);
	}

	for (int i = 0; i < 256; i++) {
		histogram[i]->set_final_culmProbability();
	}

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	int max = histogram[0]->get_amount();
	for (int i = 1; i < 256; i++) {
		if (max < histogram[i]->get_amount()) {
			max = histogram[i]->get_amount();
		}
	}

	for (int i = 0; i < 256; i++) {
		int temp = ((double)histogram[i]->get_amount() / max)*histImage.rows;
		histogram[i]->set_amount(temp);
	}

	for (int i = 0; i < 256; i++)
	{
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

