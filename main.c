#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

IplImage* image;
IplImage* imgGray;
int filter = 0;
int running = 0;

void *timed_screenshot(void *vargp)
{
    int *seconds = (int *)vargp;

    for (int i = 0; i < *seconds; i++)
    {
        printf("%i\n", *seconds - i);
        sleep(1);
    }
    if (!filter)
    {
        cvSaveImage("saved images/image.jpg", image, 0);
    }
    else
    {
        cvSaveImage("saved images/image.jpg", imgGray, 0);
    }
    puts("Image saved.");
    running = 0;
}

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
        puts("Webcam detected.\nPress spacebar to save the current frame or F to change the filter.\nPress 1 - 9 on the number row to activate a timed screenshot.");
    }
    puts("Press ESC at any time to exit the program.");
    cvNamedWindow("Output", 0);
    
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
        else if (input == 32 && !running) // hits space
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
        else if (input == 102 && !running) // hits 'f'
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
        else if (input >= 49 && input <= 57 && !running)
        {
            running = 1;
            int seconds = input - 48;
            pthread_t thread_id;
            pthread_create(&thread_id, NULL, timed_screenshot, &seconds);
            //pthread_join(thread_id, NULL);
        }
    }
    cvReleaseCapture(&webcam);
    cvDestroyWindow("Output");

    return 0;
}
