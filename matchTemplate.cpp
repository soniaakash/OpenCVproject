#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "matchingMethod.h"

using namespace std;
using namespace cv;

// Input Variables.
Mat img; Mat img2 ; Mat temp; Mat result; Mat result2;
int found=0;
// Output Windows
String image_window = "Source Image";
String result_window = "Result window";
String templ_window = "Template window";

// Variables
int select_method;
int trackbar_limit = 5;


/** main */
int main( int argc, char** argv )
{
  // Accept image and template
  img = imread( argv[1], 1 ); // imread( image_file, flag )
  temp = imread( argv[2], 1 ); // flag > 0 Returns a 3-channel color image.

  // Create windows
  namedWindow( image_window, WINDOW_NORMAL  );
  //resizeWindow(image_window, 800, 600);
  namedWindow( result_window, WINDOW_NORMAL );
  //resizeWindow(result_window, 800,600);
  namedWindow( templ_window, WINDOW_AUTOSIZE   );

  // Create Trackbar
  String trackbar_name = "Method:";
  createTrackbar( trackbar_name, image_window, &select_method, trackbar_limit, matchingMethod );
  //Accept image
 for(int i=2; i < argc; i++){
  img = imread( argv[i], 1 ); // imread( image_file, flag )

  if(matchingMethod( 0, 0 ))
	  break;
  }

  if(!found){
	  cout << "No Match Found" << endl;
  }

  waitKey(0);
  return 0;
}
