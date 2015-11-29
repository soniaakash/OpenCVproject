/*
 * matchingMethod.cpp
 *
 *  Created on: 18-Nov-2015
 *      Author: Aakash
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

// Link to global variables.
extern Mat img, temp, result;
extern String image_window;
extern String result_window;
extern String templ_window;
extern int select_method;

// Function definition.
void matchingMethod( int, void* )
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

  return;
}
