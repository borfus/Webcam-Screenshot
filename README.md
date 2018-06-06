# Webcam-Screenshot
Program that uses OpenCV 2.4.9 to display webcam output and allows you to take screenshots.

You can download current or previous OpenCV releases [here.](https://opencv.org/)

Compile using gcc: 
```gcc main.c -I./opencv/build/include/opencv -I./opencv/build/include -L./opencv/build/x64/vc12/bin -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249 -o main```