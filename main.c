#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char *image_data = stbi_load(argv[1], &width, &height, &channels, 0);

    if (!image_data) {
        printf("Error loading image.\n");
        return 1;
    }

    int resized_width = 80;
    int resized_height = height * resized_width / width / 2;
    unsigned char *resized_data = malloc(resized_width * resized_height * channels);
    stbir_resize_uint8(image_data, width, height, 0, resized_data, resized_width, resized_height, 0, channels);

    stbi_image_free(image_data);

    const char *ascii_chars = " .:-=+*%@#";

    for (int y = 0; y < resized_height; y++) {
        for (int x = 0; x < resized_width; x++) {
            unsigned char *pixel = &resized_data[(y * resized_width + x) * channels];
            int gray_value = 0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2];
            int intensity = (gray_value * strlen(ascii_chars)) / 256;
            printf("%c", ascii_chars[intensity]);
        }
        printf("\n");
    }

    free(resized_data);

    return 0;
}
