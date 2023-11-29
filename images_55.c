#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_COLOR_VALUE 255

char header[4];
int width, height;
unsigned char *imageData;
unsigned char *outputImage1, *outputImage2;

// Function to read a PPM image
void readPPM(const char *filename, int *width, int *height, unsigned char **imageData) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening input image file");
        exit(1);
    }

    fscanf(file, "%s %d %d %*d", header, width, height);
    if (header[0] != 'P' || header[1] != '6') {
        fprintf(stderr, "Input file is not in PPM format (P6)\n");
        exit(1);
    }

    *imageData = (unsigned char *)malloc(*width * *height * 3);
    fread(*imageData, 1, *width * *height * 3, file);
    fclose(file);
}

// Function to write a PPM image
void writePPM(const char *filename, int width, int height, unsigned char *imageData) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating output image file");
        exit(1);
    }

    fprintf(file, "P6\n%d %d %d\n", width, height, MAX_COLOR_VALUE);
    fwrite(imageData, 1, width * height * 3, file);
    fclose(file);
}

// Function to perform convolution with a sharpening filter
void applyFilter(unsigned char *inputData, unsigned char *outputData, int width, int height, int centerX) {
    int filter[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	int y, x, i, j;
	int centerPixelIndex;
    for (y = 1; y < height - 1; y++) {
        for (x = 1; x < width - 1; x++) {
            int sumR = 0, sumG = 0, sumB = 0;

            for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    int pixelIndex = ((y + i) * width + (x + j)) * 3;
                    int filterValue = filter[i + 1][j + 1];

                    sumR += inputData[pixelIndex] * filterValue;
                    sumG += inputData[pixelIndex + 1] * filterValue;
                    sumB += inputData[pixelIndex + 2] * filterValue;
                }
            }

            centerPixelIndex = (y * width + x) * 3;
            outputData[centerPixelIndex] = inputData[centerPixelIndex] + (centerX ? sumR : 0);
            outputData[centerPixelIndex + 1] = inputData[centerPixelIndex + 1] + (centerX ? sumG : 0);
            outputData[centerPixelIndex + 2] = inputData[centerPixelIndex + 2] + (centerX ? sumB : 0);
        }
    }
}

int main() {
    char inputYourFilename[256]; // Adjust the buffer size as needed
    int centerX, i;

    printf("Enter the full file path and name of the input image: ");
    scanf("%255s", inputYourFilename); // Limit the input to 255 characters

    printf("Enter center value (0 for Y, 1 for X): ");
    scanf("%d", &centerX);

    readPPM(inputYourFilename, &width, &height, &imageData);

    outputImage1 = (unsigned char *)malloc(width * height * 3);
    outputImage2 = (unsigned char *)malloc(width * height * 3);

    for (i = 0; i < width * height * 3; i++) {
        outputImage1[i] = MAX_COLOR_VALUE; // Initialize outputData1 as white
        outputImage2[i] = MAX_COLOR_VALUE; // Initialize outputData2 as white
    }

    applyFilter(imageData, outputImage1, width, height, centerX);
    applyFilter(imageData, outputImage2, width, height, centerX);

    writePPM("sharp1.ppm", width, height, outputImage1);
    writePPM("sharp2.ppm", width, height, outputImage2);

    free(imageData);
    free(outputImage1);
    free(outputImage2);

    printf("Sharpening complete. Output images saved as 'sharp1.ppm' and 'sharp2.ppm'\n");

    return 0;
}
