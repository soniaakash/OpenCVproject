/*
 * matchingMethod.cpp
 *
 *  Created on: 18-Nov-2015
 *      Author: Aakash
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

bool are_equal(Mat&, Mat&, Point&, Point&);

// Function definition.
bool matchingMethod( Mat &img, Mat &temp )
{
	if((img.rows < temp.rows) || (img.cols < temp.cols)){ // Compare image size.
		cout << "ERROR: Template larger than source image." << endl;
		cout << endl;
		return false;
	}

  // Create the result matrix
  Mat result;
  int result_cols =  img.cols - (temp.cols - 1);
  int result_rows = img.rows - (temp.rows - 1);

  result.create( result_rows, result_cols, CV_32FC1 ); // One Channel Output image.

  // Match image and template
  matchTemplate( img, temp, result, 0 ); // 0: SQDIFF algorithm

  // Variables for minMaxLoc function.
  double minVal; // minimum value of result array.
  double maxVal; // maximum value of result array.
  Point minLoc; // Location of minVal in result array.
  Point maxLoc; // Location of maxVal in result array.
  Point matchLoc;

  // Localizing the min/max points.
  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  // Normalize result.
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// SQDIFF algorithm returns min value for matched location.
  matchLoc = minLoc;

  // Set variables for verification process.
  Point start = matchLoc;
  Point end = Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows );

  // Verify matched area.
  if(are_equal(img, temp, start, end)){
	  cout << "Template Matched" << endl;

	// Show me what you got
	rectangle( img, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(255), 2, 8, 0 );
	rectangle( result, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );

	// Windows variables.
	  String image_window = "Source Image";
	  String result_window = "Result window";
	  String templ_window = "Template window";

	  // Create windows
	  namedWindow( image_window, WINDOW_NORMAL  );
	  resizeWindow(image_window, 800, 600);
	  namedWindow( result_window, WINDOW_NORMAL );
	  resizeWindow(result_window, 480,320);
	  namedWindow( templ_window, WINDOW_AUTOSIZE   );


	// Display Images
	imshow( image_window, img );
	imshow( result_window, result );
	imshow( templ_window, temp );
	return true;
  }
  else{
	  return false;
  }
}

// Compare/Verify selected area with template image.
bool are_equal(Mat &img, Mat &img2, Point &start, Point&end){

	// Declare/Define variables.
	int src_rows = end.y - start.y;
	int src_cols = end.x - start.x;

	Vec3b clr;
	Vec3b clr_temp;

	int img_arr[3];
	int temp_arr[3];

	// Match Size.
	if ((src_rows != img2.rows) || (src_cols != img2.cols)) {
		cout << "Size mismatch." << endl;
		cout << "Image 1: " << src_cols << "x" << src_rows << endl;
		cout << "Image 2: " << img2.cols << "x" << img2.rows << endl;
		return false;
	}
	 else { // Match images.
		for (int row = start.y; row < end.y; row++) {
			for (int col = start.x; col < end.x; col++) {

				// Extract source image color information.
				clr = img.at<Vec3b>(Point(col, row));
				img_arr[0]=clr[0];
				img_arr[1]=clr[1];
				img_arr[2]=clr[2];

				// Extract template image color information.
				clr_temp = img2.at<Vec3b>(Point(col - start.x, row - start.y));
				temp_arr[0] = clr_temp[0];
				temp_arr[1] = clr_temp[1];
				temp_arr[2] = clr_temp[2];

				// Compare extracted data.
				if (!(  (img_arr[0] <= (temp_arr[0] + 50)) && (img_arr[0] >= (temp_arr[0] - 50)) &&
						(img_arr[1] <= (temp_arr[1] + 50)) && (img_arr[1] >= (temp_arr[1] - 50)) &&
						(img_arr[2] <= (temp_arr[2] + 50)) && (img_arr[2] >= (temp_arr[2] - 50))
						)) {
					cout << "Image Mismatch" << endl;
					cout << endl;
					return false;
				}
			}
		}
	}

	return true;
}
