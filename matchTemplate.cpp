#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "matchingMethod.h"

using namespace std;
using namespace cv;

/* main */
int main( int argc, char** argv )
{
	Mat img;
	int found = 0;

  // Accept template
	Mat temp = imread( argv[1], 1 );

  // Accept images & then match.
  for(int i=2; i < argc; i++){
	  img = imread( argv[i], 1 ); // Accept Source Image.
	  cout << "Comparing template with image " << i-1 << " : " << argv[i] << endl;

  	  if(matchingMethod( img, temp )){ // Break loop if match found.
  		 found=1; // Set found flag.
  		 break;
  	  }
  }

  if(!found){
	  cout << "No Match Found" << endl;
  }

  waitKey(0);
  return 0;
}
