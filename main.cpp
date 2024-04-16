#include "Image_Class.h"
#include <windows.h>
#include <regex>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
/*
CS112_A3_Part2B_S24_20230541_20230581_20230583
Program overview: Ne3na3 is a program developed by Mohammed Hany, Ahmed Samir, and Loay Medhat
supervised by Dr Mohamed El-Ramely. Utilizing the class developed by the professor's team,
we devised 20 image processing filters to do basic image manipulation processes such as
crop or lighten, as well as other advanced processes like edge detection, merge, and oil painting.
Further, the program has a great and user friendly GUI that took a lot of Mohammed's time to finish.
I worked with Loay on the remaining tasks collaboratively until we got satisfying results.
Mohammed Hany|| ID: 20230581|| Email: 20230581@stud.fci-cu.edu.eg|| His worK:
*Filters: 2,5,8,10,11,12 + 2 bonus filters: Color Balancer and Glitch
*GUI
*Whole Code connection
*Wrote raise exceptions to increase defensive programming stability
Ahmed Samir|| ID: 20230541|| Email: 20230541@stud.fci-cu.edu.eg|| His worK:
*Filters: 13,14,15,16,17,18
*Code edits and comments
*Github repository handeling    
Loay Medhat|| ID: 20230583|| Email: 20230583@stud.fci-cu.edu.eg|| His worK::
*Filters: 1,3,4,6,7,9
*/
Image ImageLoading(){
    string filename;
    Image image;
    bool flag;
    do
    {   
        flag = false;
        cout << "Please enter colored image name: ";
        getline(cin, filename);
        cout << endl;
        try
        {
            image.loadNewImage(filename);
        }
        catch(const invalid_argument)
        {
            flag = true;
        }
    } while (flag);
    return image;
}

Image SaveImage(Image& image){
    bool error;
    string filename;
    cin.clear();
    do
    {
        error = false;
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        getline(cin, filename);
        try
        {
            image.saveImage(filename);
        }
        catch(const invalid_argument)
        {
            cout << "Please insert a valid name to save the image name:" << endl;
            error = true;
        }
    } while (error);
    return image;
}

Image grayscale(Image& image){
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int avg = 0;
            for (int c = 0; c < image.channels; c++)
            { // Per concept, gray pixel means equal channels, so we are measuring the average.
                avg += image(i, j, c)/3;
            }
            for (int c = 0; c < image.channels; c++)
            { // Assigning the average to each channel will result in the gray scale.
                image(i, j, c) = avg;
            }
        }
    }
    return image;
}

Image BlackAndWhite(Image& image){
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {   
            //Store the sum of the RGB colors of each pixel.
            int sum = 0;
            for (int k = 0; k < image.channels; k++)
            {
                sum += image(i, j, k);
            }
            // Make the RGB color of each pixel depending on whether it is dark or bright to be black or white.
            for (int k = 0; k < image.channels; k++)
            {   // If the average of the 3 pixels less than 128 (half of 256), then it's dark.
                if (sum/3 < 128)
                {
                    image(i, j, k) = 0;
                }
                // Otherwise, it is bright.
                else{
                    image(i, j, k) = 255;
                }
            }
        }
    }
    return image;
}

Image inverted_Image(Image& image){
    //Loop through the image pixels and invert them (subtract them from 255).
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = 255 - image(i, j, 0);
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
    return image;
}

Image flipVertically(Image& image){
    int width = image.width;
    int height = image.height;

    //Loop in the opposite directions in the two images through the height dimension
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height/2; j++)
        {
            for (int c = 0; c < 3; c++)
            {

                swap(image(i, height-1-j, c), image(i, j, c));

            }
        }
    }
    return image;
}

Image flipHorizontally(Image& image){
    int width1 = image.width;
    int height1 = image.height;

    //Loop in the opposite directions in the two images through the width dimension
    for (int i = 0; i < width1; i++)
    {
        for (int j = 0; j < height1; j++)
        {
            for (int c = 0; c < 3; c++)
            {
                image(width1-1-i, j, c) = image(i, j, c);
            }
        }
    }
    return image;
}

Image rotateImage90(Image& image){
    // Initialize a new image to modify.
    Image rotated(image.height, image.width);
    for (int i = 0; i < rotated.width; i++) {
        for (int j = 0; j < rotated.height; j++) {
            // Assign each rotated pixel to the image's original pixel.
            rotated(rotated.width-i-1, j, 0) = image(j, i, 0);
            rotated(rotated.width-i-1, j, 1) = image(j, i, 1);
            rotated(rotated.width-i-1, j, 2) = image(j, i, 2);
        }
    }
    return rotated;
}

Image rotateImage180(Image& image){
    Image rotated(image.width, image.height);
    for (int j = 0; j < rotated.height; j++) {
        for (int i = 0; i < rotated.width; i++) {
            rotated(rotated.width-1-i, rotated.height - 1 - j, 0) = image(i, j, 0);
            rotated(rotated.width-1-i, rotated.height - 1 - j, 1) = image(i, j, 1);
            rotated(rotated.width-1-i, rotated.height - 1 - j, 2) = image(i, j, 2);
        }
    }
    return rotated;
}

Image rotateImage270(Image& image){
    Image rotated(image.height, image.width);
    for (int i = 0; i < rotated.width; i++) {
        for (int j = 0; j < rotated.height; j++) {
            rotated( i, rotated.height-1-j, 0) = image(j, i, 0);
            rotated( i, rotated.height-1-j, 1) = image(j, i, 1);
            rotated( i, rotated.height-1-j, 2) = image(j, i, 2);
        }
    }
    return rotated;
}

Image croppingImage(Image& image){
    cout << "Enter the starting point to crop the image (" << image.width << " x " << image.height << ") as position (x, y) " << endl;;
    string x;
    bool flag;  
    regex limits("^[0-9]+$");    
    do
    {   
        flag = false;
        cout << "Enter x: ";
        getline(cin, x);
        if (!regex_match(x, limits))
        {
            flag = true;
            continue;
        }
        try
        {
            stoi(x);
        }
        catch(const invalid_argument)
        {
            flag = true;
            continue;
        }
        if (stoi(x) >= image.width-1)
        {
            flag = true;
            continue;
        }
    } while (flag);


    cin.clear();

    //If x is out of the image boundaries, ask the user to input valid x
    string y;
    do
    {   
        flag = false;
        cout << "Enter y: ";
        getline(cin, y);
        if (!regex_match(y, limits))
        {
            flag = true;
            continue;
        }
        try
        {
            stoi(y);
        }
        catch(const invalid_argument)
        {
            flag = true;
            continue;
        }
        if (stoi(y) >= image.height-1)
        {
            flag = true;
            continue;
        }
    } while (flag);

    cin.clear();

    cout << "Enter the dimensions of the cropped image (W x H)" << endl;
    string W;
    do
    {   
        flag = false;
        cout << "Enter W: ";
        getline(cin, W);
        if (!regex_match(W, limits))
        {
            flag = true;
            continue;
        }
        try
        {
            stoi(W);
        }
        catch(const invalid_argument)
        {
            flag = true;
            continue;
        }
        if (stoi(W) <= 0 || stoi(x) + stoi(W) >= image.width)
        {
            flag = true;
            continue;
        }
    } while (flag);

    cin.clear();

    string H;
    do
    {   
        flag = false;
        cout << "Enter H: ";
        getline(cin, H);
        if (!regex_match(H, limits))
        {
            flag = true;
            continue;
        }
        try
        {
            stoi(H);
        }
        catch(const invalid_argument)
        {
            flag = true;
            continue;
        }
        if (stoi(H) <= 0 || stoi(y) + stoi(H) >= image.height)
        {
            flag = true;
            continue;
        }
    } while (flag);

    Image cropped_Image(stoi(W), stoi(H));

    for (int i = stoi(x); i < stoi(W)+stoi(x); i++)
    {
        for (int j = stoi(y); j < stoi(H)+stoi(y); j++)
        {
            for (int c = 0; c < cropped_Image.channels; c++)
            {
                cropped_Image(i-stoi(x), j-stoi(y), c) = image(i, j, c);
            }
        }
    }

    cin.clear();
    return cropped_Image;
}

Image edgesDetection(Image& image) {
    // Create temporary image for storing intermediate results.
    Image temp(image.width, image.height);

    // Sobel kernels for horizontal and vertical edge detection.
    int sobelHorizontal[3][3] = { {-1, 0, 1},
                                  {-2, 0, 2},
                                  {-1, 0, 1} };
    int sobelVertical[3][3] = { {-1, -2, -1},
                                { 0,  0,  0},
                                { 1,  2,  1} };

    // Apply Sobel operator to calculate gradients.
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int gx = 0, gy = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    gx += sobelHorizontal[dy + 1][dx + 1] * image(x + dx, y + dy, 0);
                    gy += sobelVertical[dy + 1][dx + 1] * image(x + dx, y + dy, 0);
                }
            }
            // Compute gradient magnitude and set pixel value.
            int magnitude = sqrt(gx * gx + gy * gy);
            magnitude = min(255, max(0, magnitude)); 
            temp(x, y, 0) = temp(x, y, 1) = temp(x, y, 2) = magnitude;
        }
    }

    // Copy the result back to the input image.
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = temp(x, y, c);
            }
        }
    }
    return image;
}

Image resize(Image& image){

    int newWidth, newHeight;
    cout << "Decide you want to enter new dimensions or resize based on a ratio: ";
    cout << "A) new dimensions" << endl;
    cout << "B) ratio" << endl;
    string x;
    bool flag;  
    regex limits("^[0-9]+(?:\\.[0-9]+)?$");    
    do
    {   
        flag = false;
        cout << "Enter the number of desired operation: ";
        getline(cin, x);
        if (x != "a" && x != "b" && x != "A" && x != "B")
        {
            flag = true;
        }
    } while (flag);
    if (x == "a" || x == "A")
    {
        string newW, newH;
        bool flag;  
        regex limits("^[0-9]+$");    
        do
        {   
            flag = false;
            cout << "Enter new width dimension: ";
            getline(cin, newW);
            if (!regex_match(newW, limits))
            {
                flag = true;
                continue;
            }
        } while (flag);
        do
        {   
            flag = false;
            cout << "Enter new height dimension: ";
            getline(cin, newH);
            if (!regex_match(newH, limits))
            {
                flag = true;
            }
        } while (flag);
        newWidth = stoi(newW);
        newHeight = stoi(newH);
    }
    else if (x == "b" || x == "B")
    {
        string ratio;
        bool flag;  
        regex limits("^[0-9]+(?:\\.[0-9]+)?$");    
        do
        {   
            flag = false;
            cout << "Enter the desired ratio to make operations on: ";
            getline(cin, ratio);
            if (!regex_match(ratio, limits));
            {
                flag = true;
                continue;
            }
        } while (flag);
        newWidth = stod(ratio) * image.width;
        newHeight = stod(ratio) * image.height;
    }
    Image resizedImage(newWidth, newHeight);
    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            float i_original = (float)i/(newWidth - 1) * (image.width - 1);
            float j_original = (float)j/(newHeight - 1) * (image.height - 1);

            int x = floor(i_original);
            int y = floor(j_original);

            float dx = i_original - x;
            float dy = j_original - y;

            x = max(0, min(x, image.width - 2));
            y = max(0, min(y, image.height - 2));

            int r = 0, g = 0, b =0;
            for (int c = 0; c < image.channels; c++)
            {
                int topLeft = image(x, y, c);
                int topRight = image(x + 1, y, c);
                int bottomLeft = image(x, y + 1, c);
                int bottomRight = image(x + 1, y + 1, c);

                float interpolated = (1 - dx) * (1 - dy) * topLeft + dx * (1 - dy) * topRight + (1 - dx) * dy * bottomLeft + dx * dy * bottomRight;

                int colorValue = max(0, min(255, (int)(round(interpolated))));

                if (c == 0)
                {
                    r = colorValue;
                }
                else if (c == 1)
                {
                    g = colorValue;
                }
                else if (c == 2)
                {
                    b = colorValue;
                }
            }
            resizedImage(i, j, 0) = r;
            resizedImage(i, j, 1) = g;
            resizedImage(i, j, 2) = b;
        }
    }
    return resizedImage;
}
Image imageBlurring(Image& image){

    int kernelSize = 21;
    int radiusKernel = kernelSize/2;

    Image image2(image.width, image.height);

    for (int i = radiusKernel; i < image.width - radiusKernel; i++)
    {
        for (int j = radiusKernel; j < image.height - radiusKernel; j++)
        {
            int rSum = 0, gSum = 0, bSum = 0;
            int nNeighbors = 0;

            for (int x = -radiusKernel; x <= radiusKernel; x++)
            {
                for (int y = -radiusKernel; y <= radiusKernel; y++)
                {
                    int xNeighbor = x + i;
                    int yNeighbor = y + j;
                    if (xNeighbor >= 0 && xNeighbor < image.width && yNeighbor >= 0 && yNeighbor < image.height)
                    {
                        rSum += image(xNeighbor, yNeighbor, 0);
                        gSum += image(xNeighbor, yNeighbor, 1);
                        bSum += image(xNeighbor, yNeighbor, 2);
                        nNeighbors++;
                    }
                }
            }
            int rAvg, gAvg, bAvg;
            if (nNeighbors > 0)
            {
                rAvg = rSum/nNeighbors;
                gAvg = gSum/nNeighbors;
                bAvg = bSum/nNeighbors;
            }
            else
            {
                rAvg = image(i, j, 0);
                gAvg = image(i, j, 1);
                bAvg = image(i, j, 2);
            }
            image2(i, j, 0) = rAvg; 
            image2(i, j, 1) = gAvg;
            image2(i, j, 2) = bAvg;
        }
    }

    Image blurredImage(image2.width - radiusKernel*2, image2.height - radiusKernel*2);
    
    for (int i = 0; i < blurredImage.width; i++)
    {
        for (int j = 0; j < blurredImage.height; j++)
        {
            for (int c = 0; c < image.channels; c++)
            {
                blurredImage(i, j, c) = image2(i + radiusKernel, j + radiusKernel, c);
            }
        }
    }
    return blurredImage;
}

Image SunLight (Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int r = min(255, image(i, j, 0) + 25);  // Increase red channel more
            int g = min(255, image(i, j, 1) + 35);  // Increase green channel more
            int b = max(0, image(i, j, 2) - 25);     // Decrease blue channel slightly
            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
            }
    }
    return image;
}

Image purplizer(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int r = min(255, image(i, j, 0) + 20);  // Increase red channel more
            int g = max(0, image(i, j, 1) - 50);  // Decrease green channel more
            int b = min(255, image(i, j, 2) + 20);     // Increase blue channel slightly
            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
        }
    }
    return image;
}

Image Oil(Image &image) {
    int originalW = image.width;
    int originalH = image.height;
    // j and i are starting from 1, which represents the radius of the effect area.
    // It also serves as a boundary to avoid errors such as 'Out-of-boundaries'.
    for (int j = 1; j < originalH - 1; ++j) {
        for (int i = 1; i < originalW - 1; ++i) {
        // Initiallize arrays to store the values of current intensity of each pixel.
        // Assigning their values to 0 was added later to avoid random data restored in the memory.
        long intensitycount[256] = {0}, SumR[256] = {0}, SumG[256] = {0}, SumB[256] = {0};
            // Looping in the negative of the radius to have four direction and complete a square of effect.
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int r = image((x + i), (y + j), 0);
                    int g = image((x + i), (y + j), 1);
                    int b = image((x + i), (y + j), 2);
                    int currentintensity =  ( ( ( r + g + b ) / 3.0 ) * 10 ) / 255;
                    if( currentintensity > 255 )
                        {currentintensity = 255;}
                    int k = currentintensity;
                    // For each current intesity, those values will increase:
                    intensitycount[k]++; // Count of intesity for each pixel to use later to find the most common intensity.
                    // Assigning the array a pixel with its channel value.
                    SumR[k] = SumR[k] + r; 
                    SumG[k] = SumG[k] + g;
                    SumB[k] = SumB[k] + b;
                }
            }
            int maxintensity = 0;
            int maxindex = 0;
            for( int z = 0; z < 256; z++ )
            {
                if( intensitycount[z] > maxintensity )
                {
                    maxintensity = intensitycount[z];
                    maxindex = z;
                }
            }
            if (maxintensity == 0/*meaning that we cannot divide on it, 
                so we wrote a condition to avoid black pixels by assigning them the average value*/ ) {
                int origR = image(i, j, 0);
                int origG = image(i, j, 1);
                int origB = image(i, j, 2);
                image(i, j, 0) = (origR + origG + origB) / 3;
                image(i, j, 1) = (origR + origG + origB) / 3;
                image(i, j, 2) = (origR + origG + origB) / 3;
            } else/*The main condition, which gives the pixels in the area the most common color*/ {
                image(i, j, 0) = SumR[maxindex] / maxintensity;
                image(i, j, 1) = SumG[maxindex] / maxintensity;
                image(i, j, 2) = SumB[maxindex] / maxintensity;
            }
        }
    }
    return image;
}

Image Infrared(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // The effect is imitated by setting the red channel to its max and inverting the other channels.
            int r = 255;
            int g = 255 - image(i, j, 1);
            int b = 255 - image(i, j, 2);
            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
        }
    }
    return image;
}


Image colorBalance(Image& image){
  string red, blue, green;
  bool flag;
  regex limits(R"([-\+]?\d+)");
  do
  {   
      flag = false;
      cout << "Enter the red channel factor you want to insert: ";
      getline(cin, red);
      if (!regex_match(red, limits))
      {
          flag = true;
          continue;
      }
      try
      {
          stoi(red);
      }
      catch(const invalid_argument)
      {
          flag = true;
          continue;
      }
      if (stoi(red) < -100 || stoi(red) > 100)
      {
          flag = true;
          continue;
      }
  } while (flag);
  
  do
  {   
      flag = false;
      cout << "Enter the green channel factor you want to insert: ";
      getline(cin, green);
      if (!regex_match(green, limits))
      {
          flag = true;
          continue;
      }
      try
      {
          stoi(green);
      }
      catch(const invalid_argument)
      {
          flag = true;
          continue;
      }
      if (stoi(green) < -100 || stoi(green) > 100)
      {
          flag = true;
          continue;
      }
  } while (flag);

  do
  {   
      flag = false;
      cout << "Enter the blue channel factor you want to insert: ";
      getline(cin, blue);
      if (!regex_match(blue, limits))
      {
          flag = true;
          continue;
      }
      try
      {
          stoi(blue);
      }
      catch(const invalid_argument)
      {
          flag = true;
          continue;
      }
      if (stoi(blue) < -100 || stoi(blue) > 100)
      {
          flag = true;
          continue;
      }
  } while (flag);

  for (int i = 0; i < image.width; i++)
  {
    for (int j = 0; j < image.height; j++)
    {
      image(i, j, 0) = max(0, min(255, image(i, j, 0) + stoi(red)));
      image(i, j, 1) = max(0, min(255, image(i, j, 1) + stoi(green)));
      image(i, j, 2) = max(0, min(255, image(i, j, 2) + stoi(blue)));
    }
  }
  return image;
}

Image glitchedImage(Image& image){
    return image;
}

Image skewed(Image& image) {
    int angle;
    cout << "Enter angle: ";
    cin >> angle;
    cout << angle << endl;
    // Users are usually familiar with degrees, but math functions are built on radian.
    double radians = angle * M_PI / 180.0;
    // max required width is used to have a limit that the skewed image won't overcome.
    double max_required_width = image.width + abs(image.height * tan(radians));
    // Hence, the min function takes the lowermost value between max width and the normal calculation, a necessary measure to avoid errors.
    int newWidth = static_cast<int>(min(image.width + abs(image.height * tan(radians)), max_required_width));
    int newHeight = image.height;
    Image skewed = Image(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the corresponding position in the image.
            double srcX = 0;
            // A condition in case the user wanted to skew left or right.
            if (angle>0){ 
                srcX = x - (newWidth) / 2.0;}
            else if (angle<0){ 
                srcX = x - (newWidth - 2*image.width) / 2.0;} 
            double srcY = y;
            // Reverse skewing to find the position in the image.
            double srcXimage = srcX - srcY * tan(-radians);
            double srcYimage = srcY;
            // Interpolate pixel value from surrounding pixels in the image 
            if (srcXimage >= 0 && srcXimage < image.width &&
                srcYimage >= 0 && srcYimage < image.height) {
                // Get the integer and fractional parts of the position
                int x0 = static_cast<int>(srcXimage);
                int y0 = static_cast<int>(srcYimage);
                double dx = srcXimage - x0;
                double dy = srcYimage - y0;
                // Perform bilinear interpolation
                for (int c = 0; c < image.channels; ++c) {
                    unsigned char v00 = image(x0, y0, c);
                    unsigned char v01 = image(x0, y0 + 1, c);
                    unsigned char v10 = image(x0 + 1, y0, c);
                    unsigned char v11 = image(x0 + 1, y0 + 1, c);

                    unsigned char interpolatedValue = static_cast<unsigned char>(
                        (1 - dx) * (1 - dy) * v00 +
                        dx * (1 - dy) * v10 +
                        (1 - dx) * dy * v01 +
                        dx * dy * v11);

                    // Set the pixel value in the skewed image
                    skewed(x, y, c) = interpolatedValue;
                }
            }
            else {
                // Second option for out of bounds cases by setting the pixel to white; could also be set to black.
                for (int c = 0; c < image.channels; ++c) {
                    skewed(x, y, c) = 255;
                }
            }
        }
    }

    cout << "...." << endl;
    return skewed;
}
/*
void skewedImage() {
    string filename;
    int angle;
    cout << "Please enter image name to apply skewing filter: ";
    cin >> filename;
    cout << "Enter Skewing angle: ";
    cin >> angle;
    Image image(filename);
    double radians = angle * M_PI / 180.0;
    double max_required_width = image.width + abs(image.height * tan(radians));
    int newWidth = static_cast<int>(min(image.width + abs(image.height * tan(radians)), max_required_width));
    int newHeight = image.height;
    Image skewed = Image(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the corresponding position in the image
            double srcX = 0;
            if (angle>0){ srcX = x - (newWidth) / 2.0;}
            else if (angle<0){ srcX = x - (newWidth - 2*image.width) / 2.0;} 
            double srcY = y;
            // Reverse skewing to find the position in the image 
            double srcXimage = srcX - srcY * tan(-radians);
            double srcYimage = srcY;
            // Interpolate pixel value from surrounding pixels in the image 
            if (srcXimage >= 0 && srcXimage < image.width &&
                srcYimage >= 0 && srcYimage < image.height) {
                // Get the integer and fractional parts of the position
                int x0 = static_cast<int>(srcXimage);
                int y0 = static_cast<int>(srcYimage);
                double dx = srcXimage - x0;
                double dy = srcYimage - y0;
                // Perform bilinear interpolation
                for (int c = 0; c < image.channels; ++c) {
                    unsigned char v00 = image(x0, y0, c);
                    unsigned char v01 = image(x0, y0 + 1, c);
                    unsigned char v10 = image(x0 + 1, y0, c);
                    unsigned char v11 = image(x0 + 1, y0 + 1, c);

                    unsigned char interpolatedValue = static_cast<unsigned char>(
                        (1 - dx) * (1 - dy) * v00 +
                        dx * (1 - dy) * v10 +
                        (1 - dx) * dy * v01 +
                        dx * dy * v11);

                    // Set the pixel value in the skewed image
                    skewed(x, y, c) = interpolatedValue;
                }
            }
            else {
                // Second option for out of bounds cases by setting the pixel to black; could also be set to white.
                for (int c = 0; c < image.channels; ++c) {
                    skewed(x, y, c) = 255;
                }
            }
        }
    }
    cout << "Please enter image name to store skewed image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    skewed.saveImage(filename);
}
*/

Image tv(Image& image) {
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      // A condition to have scanlines.
      if (y % 2 == 0) {
        // Simulate a flickering scanline by randomly modifying the brightness of the pixels.
        // The higher the division value, the darker the scanlines become.
        int offset = rand() % 30;
        int red = min(255, image.getPixel(x, y, 0) + offset);
        int green = min(255, image.getPixel(x, y, 1) + offset);
        int blue = min(255, image.getPixel(x, y, 2) + offset);
        image.setPixel(x, y, 0, red);
        image.setPixel(x, y, 1, green);
        image.setPixel(x, y, 2, blue);
      }
    }
  }
    // Adding noise randomly to simulate the old tv effect. It was made using cathode ray tubes.
    srand(static_cast<unsigned int>(time(nullptr)));
    int noiseLevel = 20;
    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            // adding noise to each color channel.
            for (int c = 0; c < image.channels; ++c) {
                // random noise within the specified noise level.
                int randomNoise = rand() % (noiseLevel * 2 + 1) - noiseLevel;
                int newValue = static_cast<int>(image(i, j, c)) + randomNoise;
                // clamp the new value to the valid range [0, 255].
                newValue = max(0, min(255, newValue));
                image(i, j, c) = static_cast<unsigned char>(newValue);
            }
        }
    }
    return image;
}

void Menu(Image& image) {
    Image modified = image;
    cout << "Please enter the number of the desired operation (or exit):" << endl;
    cout << "1- Load new image" << endl;
    cout << "2- Grayscale Conversion" << endl;
    cout << "3- Black and White" << endl;
    cout << "4- Invert Image" << endl;
    cout << "5- Merge Image" << endl;
    cout << "6- Flip Image" << endl;
    cout << "7- Rotate Image" << endl;
    cout << "8- Darken and Lighten Image" << endl;
    cout << "9- Crop Image" << endl;
    cout << "10- Adding a Frame to the Image" << endl;
    cout << "11- Detect Image Edges" << endl;
    cout << "12- Resizing Images" << endl;
    cout << "13- Blur Images" << endl;
    cout << "14- Sun light" << endl;
    cout << "15- Oil painting" << endl;
    cout << "16- Den Den Mushi Television Image" << endl;
    cout << "17- Purplizer" << endl;
    cout << "18- Infrared" << endl;
    cout << "19- Skewing filter" << endl;
    cout << "20- Color Balancer" << endl;
    cout << "21- Glitch filter" << endl;
    cout << "22- Save Image" << endl;
    cout << "23- Exit" << endl;
    string a;
    bool flag;
    regex limits("^[0-9]+$");
    do
    {   
        flag = false;
        cout << "Enter a valid number: ";
        getline(cin, a);
        if (!regex_match(a, limits))
        {
            flag = true;
            continue;
        }
        try
        {
            stoi(a);
        }
        catch(const invalid_argument)
        {
            flag = true;
            continue;
        }
        if (stoi(a) < 1 || stoi(a) > 23)
        {
            flag = true;
            continue;
        }
    } while (flag);
    
    if (stoi(a) == 23) {
        cout << "Thank you for using our program." << endl;
    }
    if (stoi(a) == 1)
    {
        image = ImageLoading();
        cout << "Loaded Successfully" << endl;
        Sleep(500);
        Menu(image);
    }
    if (stoi(a) == 2)
    {
        modified = grayscale(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 3) {
        modified = BlackAndWhite(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 4)
    {
        modified = inverted_Image(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 6)
    {
        //Make the user choose from two options: horizontally or vertically.
        string ans2;
        cout << "Please select whether you want to flip it (v)ertically or (h)orizontally: ";
        cin >> ans2;
        //Check the user input
        while (ans2 != "v" && ans2 != "V" && ans2 != "h" && ans2 != "H")
        {
            cout << "Please insert a valid option: ";
            cin >> ans2;
        }
        if (ans2 == "H" || ans2 == "h")
        {
            modified = flipHorizontally(image);
            cout << "Done Successfully" << endl;
            Sleep(500);
            Menu(modified);
        }
        else if (ans2 == "V" || ans2 == "v")
        {
            modified = flipVertically(image);
            cout << "Done Successfully" << endl;
            Sleep(500);
            Menu(modified);
        }
    }
    else if (stoi(a) == 7)
    {
        string angleOfRotation;
        bool flag;
        regex limits("^[0-9]+$");
        do
        {   
            flag = false;
            cout << "Enter the angle of rotation: ";
            getline(cin, angleOfRotation);
            if (!regex_match(angleOfRotation, limits))
            {
                flag = true;
                continue;
            }
            try
            {
                stoi(angleOfRotation);
            }
            catch(const invalid_argument)
            {
                flag = true;
                continue;
            }
            if (stoi(angleOfRotation) != 90 && stoi(angleOfRotation) != 180 && stoi(angleOfRotation) != 270)
            {
                flag = true;
                continue;
            }
        } while (flag);
        
        if (stoi(angleOfRotation) == 90)
        {
            modified = rotateImage90(image);
        }
        else if (stoi(angleOfRotation) == 180)
        {
            modified = rotateImage180(image);
        }
        else if (stoi(angleOfRotation) == 270)
        {
            modified = rotateImage270(image);
        }
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 9)
    {
        cin.clear();
        modified = croppingImage(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        cin.clear();
        Menu(modified);
    }
    else if (stoi(a) == 11)
    {
        modified = edgesDetection(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 12)
    {
        modified = resize(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 13)
    {
        modified = imageBlurring(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 14)
    {
        modified = SunLight(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 15)
    {
        modified = Oil(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 16)
    {
        modified = tv(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 17)
    {
        modified = purplizer(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 18)
    {
        modified = Infrared(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 19)
    {
        skewedImage();
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 20)
    {
        modified = colorBalance(image);
        cout << "Done Successfully" << endl;
        Sleep(500);
        Menu(modified);
    }
    else if (stoi(a) == 22)
    {
        SaveImage(modified);
        cout << "Saved Successfully, check your directory" << endl;
        Sleep(500);
        Menu(modified);
    }
}

int main(){
    cout << "Welcome Ya user ya danaya" << endl;
    Image image = ImageLoading();
    Menu(image);    
    return 0;
}










































