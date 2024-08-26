#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "img2ascii.h"

bool load_image(Image *image, const char *path, const int target_width) {
	image->data = stbi_load(path, &image->width, &image->height, &image->channels, 3);

	if(image->data == NULL) {
		fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
		return false;
	}

	if(image->channels != 3) {
		fprintf(stderr, "Invalid number of channels: %d\n", image->channels);
		return false;
	}

	const int target_height = image->height / (image->width / (float)target_width);
	stbir_resize_uint8_srgb(image->data, image->width, image->height, image->width * image->channels, image->data, target_width, target_height, target_width * image->channels, image->channels);

	image->width = target_width;
	image->height = target_height;

	return true;
}

uint8_t get_intensity(const Image *image, const int index) {
	return image->data[index * image->channels + 0] * 0.21f + image->data[index * image->channels + 1] * 0.72f + image->data[index * image->channels + 2] * 0.07f;
}
