#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main()
{
    int input;
    CvCapture* webcam = cvCreateCameraCapture(0);
    if (!webcam)
    {
        puts("The program couldn't detect a webcam, Please troubleshoot your webcam and run again.");
        exit(-1);
    }
    else 
    {
        puts("Webcam detected. Press spacebar to save the current frame or F to change the filter.");
    }
    puts("Press ESC at any time to exit the program.");
    cvNamedWindow("Output", 0);

    IplImage* image;
    IplImage* imgGray;
    int filter = 0;
    while (1)
    {
        image = cvQueryFrame(webcam);
        if (image)
        {
            imgGray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
            cvCvtColor(image, imgGray, CV_RGB2GRAY);
         
            if (!filter)
            {
                cvShowImage("Output", image);
            }
            else
            {
                cvShowImage("Output", imgGray);
            }
        }

        input = cvWaitKey(10);
        if (input == 27) // If user hits escape, exit program.
        {
            break;
        }
        else if (input == 32) // hits space
        {
            if (!filter)
            {
                cvSaveImage("saved images/image.jpg", image, 0);
            }
            else
            {
                cvSaveImage("saved images/image.jpg", imgGray, 0);
            }
            puts("Image saved.");
        }
        else if (input == 102) // hits 'f'
        {
            if (!filter)
            {
                filter = 1;
                puts("Grayscale");
            }
            else
            {
                filter = 0;
                puts("RGB");
            }
        }
    }
    cvReleaseCapture(&webcam);
    cvDestroyWindow("Output");

    return 0;
}
