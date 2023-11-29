# Image-Quantization
Implementation of a program to generate a color quantized image for an input image using  uniform quantization

**Requirements**
Input image file (square size, .ppm format)
Factor value (2, 4, 8, or 16)
****Usage****
**Input Image Selection:**

Enter the input image file name including its square size in .ppm format when prompted.
**Factor Value:**

Enter the factor value for color quantization (2, 4, 8, or 16) when prompted.
**Program Execution**:

The program performs the following steps:
Reads the input image using 'ReadPPM'.
Creates an output image using 'CreatePPM'.
Initializes all pixel values of the output image as white (255).
Quantizes each pixel's color value based on the entered factor value and places it into the output image using 'PutRPixel', 'PutGPixel', and 'PutBPixel'.
The quantization process follows specific rules based on the factor value entered (refer to Note04.pptx).
Writes the resulting output image in .ppm format using 'WritePPM'.

**Output:**
The program generates an output image file named 'out.ppm' as a result of color quantization.
**Color Quantization Rules******
**Factor Value 2 (8-colors):**

**Quantized value:**
If R, G, or B value is between 0 and 127, the quantized value is 64.
If R, G, or B value is between 128 and 255, the quantized value is 192.
Factor Value 4 (64-colors):

**Quantized value:**
If R, G, or B value is between 0 and 63, the quantized value is 32.
If R, G, or B value is between 64 and 127, the quantized value is 96.
If R, G, or B value is between 128 and 191, the quantized value is 160.
If R, G, or B value is between 192 and 255, the quantized value is 224, and so on.
