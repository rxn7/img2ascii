#pragma once

#include <stb_image.h>
#include <stb_image_resize2.h>

typedef struct Image {
	uint8_t *data;
	int width;
	int height;
	int channels;
} Image;

void image_free(Image *image);
bool image_load(Image *image, const char *path, const int target_width);
uint8_t image_get_pixel_intensity(const Image *image, const int index);
