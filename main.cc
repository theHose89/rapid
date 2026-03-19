#define STB_IMAGE_IMPLEMENTATION
#include "mat.h"
#include <iostream>
#include "stb_image.h"
#include <time.h>
#include <stdio.h>

void print_ascii(Mat m){
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j = 0; j < m.cols; j++){
            if(*m.at(i, j) == 255){
                printf("- ");
            }else if(*m.at(i, j) == 0){
                printf("@ ");
            }else{
                printf("? ");
            }
        }
        printf("\n");
    }
}


int main(int argc, char *argv[]){
    srand(time(0));

    int width = 32;
    int height = 32;
    int channels = 3;
    uint8_t *imageData = stbi_load(argv[1], &width, &height, &channels, 1);
    if (!imageData) {
        printf("Failed to load image\n");
        return 1;
    }

    Mat input(height, width);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            *input.at(i, j) = imageData[(i * width + j)];
            // *r.at(i, j) = imageData[(i * width + j) * channels];
            // *g.at(i, j) = imageData[(i * width + j) * channels + 1];
            // *b.at(i, j) = imageData[(i * width + j) * channels + 2];
        }
    }
    stbi_image_free(imageData);

    print_ascii(input);


    return 0;
}