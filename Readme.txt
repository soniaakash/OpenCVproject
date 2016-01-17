In this project we have tried and successfully implemented template matching using ‘OpenCV’ library.
The software developed is capable to identify parent image of a template image from any number of given input images.
It uses the basic template matching technique that is it simply slides the template image over the input images and compares them.
By sliding, we mean moving the patch one pixel at a time (left to right, up to down).

The program is split into 2 source files and 1 header file:
•	main.cpp: The main method accepts the input as one or multiple source image(s) and one template image. 
Each source image and template image are sent for further processing by making a call to ‘matchingMethod’ function. 
If the template is matched, then ‘matchingMethod’ function returns true, else, it returns false. 
If true, then program execution halts and result is displayed, else, the process continues for next source image. 
If no image is matched with template then the program terminates with no result.

•	matchingMethod.h: It is the header file containing declaration of ‘matchingMethod’ function.

•	matchingMethod.cpp: It is the source file which defines ‘matchingMethod’ function. 
The matchingMethod function performs: verification of proper input files, creation of result matrix, matching operation,
localization of matched area, normalization of result matrix, verification of matched result, and displaying the result.

The different image editing software uses different techniques to compress image in given format.
This compression method results in change of pixel colour information.
The change in colour information of a pixel due to compression method used by image editing software is taken into account.
We have used sufficient threshold so as to guarantee that such change in pixel information will not affect the result of our software.


