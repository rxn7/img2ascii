#pragma once

#include <stb_image.h>
#include <stb_image_resize2.h>

typedef struct Image {
	uint8_t *data;
	int width;
	int height;
	int channels;
} Image;

bool load_image(Image *image, const char *path, const int target_width);
uint8_t get_intensity(const Image *image, const int index);
