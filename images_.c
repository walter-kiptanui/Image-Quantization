#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_COLOR_VALUE 255

char header[4];
int width, height;
unsigned char *imageData;
unsigned char *outputData = NULL; // Initialize outputData to NULL
int i;

// Function to quantize a color value based on the given factor
unsigned char quantizeColor(unsigned char color, int factor) {
    int step = MAX_COLOR_VALUE / (factor - 1);
    int quantized = (color / step) * step + step / 2;
    return (unsigned char)quantized;
}

// Function to read a PPM image
void readPPM(const char *filename, int *width, int *height, unsigned char **imageData) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening input image file");
        exit(1);
    }

    fscanf(file, "%s %d %d %*d", header, width, height); // Use the global 'header' variable
    if (header[0] != 'P' || header[1] != '6') {
        fprintf(stderr, "Input file is not in PPM format (P6)\n");
        exit(1);
    }

    // Read the remaining PPM data
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

int main() {
    char inputFilename[100];
    int factor;

    printf("Enter input image file name: ");
    scanf("%s", inputFilename);

    printf("Enter factor value (2, 4, 8, or 16): ");
    scanf("%d", &factor);

    // Read the input PPM image
    readPPM(inputFilename, &width, &height, &imageData);

    // Allocate memory for the output image
    outputData = (unsigned char *)malloc(width * height * 3);

    // Perform color quantization
    for (i = 0; i < width * height * 3; i++) {
        outputData[i] = quantizeColor(imageData[i], factor);
    }

    // Write the output PPM image
    writePPM("out.ppm", width, height, outputData);

    // Clean up
    free(imageData);
    free(outputData);

    printf("Color quantization complete. Output image saved as 'out.ppm'\n");

    return 0;
}
