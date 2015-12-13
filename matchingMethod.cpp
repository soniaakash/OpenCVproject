/*
 * matchingMethod.cpp
 *
 *  Created on: 18-Nov-2015
 *      Author: Aakash
 */
#include<iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
// Link to global variables.
extern Mat img, temp, result;
extern String image_window;
extern String result_window;
extern String templ_window;
extern int select_method;
extern int found;
bool are_equal(Mat&, Mat&, Point&, Point&);

// Function definition.
bool matchingMethod( int, void* )
{
  // Create the result matrix
  int result_cols =  img.cols - (temp.cols - 1);
  int result_rows = img.rows - (temp.rows - 1);

  result.create( result_rows, result_cols, CV_32FC1 ); // One Channel Output image.

  // Match image and template
  // select_method = 0: SQDIFF, 1: SQDIFF NORMED, 2: TM CCORR, 3: TM CCORR NORMED, 4: TM COEFF, 5: TM COEFF NORMED
  matchTemplate( img, temp, result, select_method );

  // Normalize result.
  // Using NORM_MINMAX type to calculate normalized value over the sub-array.
  // This is useful for calculation with densed image.
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
  //dtype = -1 : the output array has the same type as src.

  // Variables for minMaxLoc function.
  double minVal; // minimum value in array.
  double maxVal; // maximum value in array.
  Point minLoc; // Location of minVal in array.
  Point maxLoc; // Location of maxVal in array.
  Point matchLoc;

  // Localizing the min/max points.
  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// SQDIFF and SQDIFF_NORMED method uses min match values.
  if( select_method  == CV_TM_SQDIFF || select_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

     Point start = matchLoc;
  Point end = Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows );

  if(are_equal(img, temp, start, end)){
	  cout << "Images Matched" << endl;

  /// Show me what you got
  rectangle( img, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );
  // Color = Scalar::all(0)
  // Line Thickness = 2
  // Line type = 8 (default)
  // Fractional bits in point coordinates = 0

  // Display Images
  imshow( image_window, img );
  imshow( result_window, result );
  imshow( templ_window, temp );
  found=1;
return 1;
  }
  else{
	  return 0;
  }


}

bool are_equal(Mat &img, Mat &img2, Point &start, Point&end){
	int src_rows = end.y - start.y;
	int src_cols = end.x - start.x;

	Vec3b clr;
	Vec3b clr_temp;

	int img_arr[3];
	int temp_arr[3];

	if ((src_rows != img2.rows) || (src_cols != img2.cols)) {
		cout << "Size mismatch." << endl;
		cout << "Image 1: " << src_cols << "x" << src_rows << endl;
		cout << "Image 2: " << img2.cols << "x" << img2.rows << endl;
		return false;
	}
	 else {
		for (int row = start.y; row < end.y; row++) {
			for (int col = start.x; col < end.x; col++) {

				clr = img.at<Vec3b>(Point(col, row));
				img_arr[0]=clr[0];
				img_arr[1]=clr[1];
				img_arr[2]=clr[2];

				clr_temp = img2.at<Vec3b>(Point(col - start.x, row - start.y));
				temp_arr[0] = clr_temp[0];
				temp_arr[1] = clr_temp[1];
				temp_arr[2] = clr_temp[2];

				if (!(  (img_arr[0] <= (temp_arr[0] + 50)) && (img_arr[0] >= (temp_arr[0] - 50)) &&
						(img_arr[1] <= (temp_arr[1] + 50)) && (img_arr[1] >= (temp_arr[1] - 50)) &&
						(img_arr[2] <= (temp_arr[2] + 50)) && (img_arr[2] >= (temp_arr[2] - 50))
						)) {
					cout << "Mismatch at img : Col x Row : " << col << "x" << row
							<< endl;
					cout << "Mismatch at img2 : Col x Row : " << col - start.x << "x" << row - start.y << endl;
					return false;
				}
			}
		}
	}

	return true;
}
