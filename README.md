
# NTU Computer Vision 

## HW1
### Use B_PIX to write a program to generate
(a)  upside-down lena.im [upsideDown.jpg](hw1/upsideDown.jpg)

(b)  right-side-left lena.im [rightSideLeft.jpg](hw1/rightSideLeft.jpg)

(c)  diagonally mirrored lena.im [diagonallyMirrored.jpg](hw1/diagonallyMirrored.jpg)

***

## HW2
### Write a program to generate:
(a)  a binary image (threshold at 128) [thresholding.jpg](hw2/thresholding.jpg)

(b)  a histogram [lena_histogram.png](hw2/lena_histogram.png) 

(c)  connected components (regions with + at centroid, bounding box) [connectedComponentsLena.jpg](hw2/connectedComponentsLena.jpg) 

*** 

## HW3 
### Write a program to do histogram 
(1)  Before Lena [HistogramEqualization_before.jpg](hw3/HistogramEqualization_before.jpg)

(2)  Before histogram [histogram of lena](hw3/301.png)

(3)  After Lena [HistogramEqualization_after.jpg](hw3/HistogramEqualization_after.jpg)

(4)  After histogram [histogram of lena](hw3/302.png)

***

## HW4
### Write programs which do binary morphological dilation, erosion, opening, closing, and hit-and-miss transform on a binary image
(1)  dilation [Dilation.jpg](hw4/Dilation.jpg)

(2)  erosion [Erosion.jpg](hw4/Erosion.jpg)

(3)  opening [Opening.jpg](hw4/Opening.jpg)

(4)  closing [Closing.jpg](hw4/Closing.jpg)

(5)  hit-and-miss [hitAndMiss.jpg](hw4/hitAndMiss.jpg)

***


## HW5

### Write programs which do gray scale morphological dilation, erosion, opening, and
closing on a gray scale image

(1)  dilation_gray [Dilation_gray.jpg](hw5/Dilation_gray.jpg)

(2)  erosion_gray [Erosion_gray.jpg](hw5/Erosion_gray.jpg)

(3)  opening_gray [Opening_gray.jpg](hw5/Opening_gray.jpg)

(4)  closing_gray [Closing_gray.jpg](hw5/Closing_gray.jpg)


## HW6

### Write a program to generate Yokoi connectivity number
Down sample lena.bmp from 512*512 to64*64 first.
Sample pixels positions at each 8*8 top-left corner, so everyone will get the same answer .

(1)  Yokoi connectivity number [lena.txt](hw6/lena.txt)


## HW7

### Write a program to generate thinned image.
Down sample lena.bmp from 512*512 to 64*64 first.
Sample pixels positions at each 8*8 top-left corner, so everyone will get the same answer .

(1)  thinned txt [lena.txt](hw7/lena.txt)

(2)  thinned image [thinning.jpg](hw7/thinning.jpg)


# NTU Computer Vision 

## HW8

### Write the following programs
Generate additive white Gaussian noise 
Generate salt-and-pepper noise 
Run box filter (3X3, 5X5) on all noisy images
Run median filter (3X3, 5X5) on all noisy images
Run opening followed by closing or closing followed by opening


(1)  Generate additive white Gaussian noise 

![GaussianNoise10.bmp](hw8/GaussianNoise10.bmp)
![GaussianNoise30.bmp](hw8/GaussianNoise30.bmp)

(2)  Generate salt-and-pepper noise

![SaltandPepper1.bmp](hw8/SaltandPepper1.bmp)
![SaltandPepper05.bmp](hw8/SaltandPepper05.bmp)

(3)  Run box filter (3X3, 5X5) on all noisy images
Run box filter 3X3

![boxfilter3x3GN10.bmp](hw8/boxfilter3x3GN10.bmp)
![boxfilter3x3GN30.bmp](hw8/boxfilter3x3GN30.bmp)
![boxfilter3x3SP1.bmp](hw8/boxfilter3x3SP1.bmp)
![boxfilter3x3SP05.bmp](hw8/boxfilter3x3SP05.bmp)

Run box filter 5X5

![boxfilter5x5GN10.bmp](hw8/boxfilter5x5GN10.bmp)
![boxfilter5x5GN30.bmp](hw8/boxfilter5x5GN30.bmp)
![boxfilter5x5SP1.bmp](hw8/boxfilter5x5SP1.bmp)
![boxfilter5x5SP05.bmp](hw8/boxfilter5x5SP05.bmp)

(4)  Run median filter (3X3, 5X5) on all noisy images
Run median filter 3X3

![medianfilter3x3GN10.bmp](hw8/medianfilter3x3GN10.bmp)
![medianfilter3x3GN30.bmp](hw8/medianfilter3x3GN30.bmp)
![medianfilter3x3SP1.bmp](hw8/medianfilter3x3SP1.bmp)
![medianfilter3x3SP05.bmp](hw8/medianfilter3x3SP05.bmp)

Run median filter 5X5

![medianfilter5x5GN10.bmp](hw8/medianfilter5x5GN10.bmp)
![medianfilter5x5GN30.bmp](hw8/medianfilter5x5GN30.bmp)
![medianfilter5x5SP1.bmp](hw8/medianfilter5x5SP1.bmp)
![medianfilter5x5SP05.bmp](hw8/medianfilter5x5SP05.bmp)

(5)  Run opening followed by closing or closing followed by opening
Run opening followed by closing

![openingClosingGN10.bmp](hw8/openingClosingGN10.bmp)
![openingClosingGN30.bmp](hw8/openingClosingGN30.bmp)
![openingClosingSP1.bmp](hw8/openingClosingSP1.bmp)
![openingClosingSP05.bmp](hw8/openingClosingSP05.bmp)

closing followed by opening

![closingOpeningGN10.bmp](hw8/closingOpeningGN10.bmp)
![closingOpeningGN30.bmp](hw8/closingOpeningGN30.bmp)
![closingOpeningSP1.bmp](hw8/closingOpeningSP1.bmp)
![closingOpeningSP05.bmp](hw8/closingOpeningSP05.bmp)



## HW9

### Write programs to generate the following gradient magnitude images
and choose proper thresholds to get the binary edge images:
Roberts operator
Prewitt edge detector
Sobel edge detector
Frei and Chen gradient operator
Kirsch compass operator
Robinson compass operator
Nevatia-Babu 5X5 operator


(1)  Roberts operator

![robertOperator.bmp](hw9/robertOperator.bmp)

(2)  Prewitt edge detector

![prewittEdgeDetector.bmp](hw9/prewittEdgeDetector.bmp)

(3)  Sobel edge detector

![sobelEdgeDetector.bmp](hw9/sobelEdgeDetector.bmp)

(4)  Frei and Chen gradient operator

![freiandChenGradientOperator.bmp](hw9/freiandChenGradientOperator.bmp)

(5)  Kirsch compass operator

![kirschCompassOperator.bmp](hw9/kirschCompassOperator.bmp)

(6)  Robinson compass operator

![robinsonCompassOperator.bmp](hw9/robinsonCompassOperator.bmp)

(7)  Nevatia-Babu 5X5 operator

![nevatiaBabu55Operator.bmp](hw9/nevatiaBabu55Operator.bmp)


