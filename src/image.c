#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "image.h"

void image_free(Image *image) {
	stbi_image_free((void*)image->data);
}

bool image_load(Image *image, const char *path, int target_width) {
	image->data = stbi_load(path, &image->width, &image->height, &image->channels, 0);

	if(image->data == NULL) {
		fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
		return false;
	}

	if(image->width <= target_width) {
		target_width = image->width;
		fprintf(stderr, "Source image is smaller than requested width!\n");
	}

	const int target_height = image->height / (image->width / (float)target_width);
	stbir_resize_uint8_linear(image->data, image->width, image->height, image->width * image->channels, image->data, target_width, target_height, target_width * image->channels, image->channels);

	image->width = target_width;
	image->height = target_height;

	return true;
}

uint8_t image_get_pixel_intensity(const Image *image, const int index) {
	return image->data[index * image->channels + 0] * 0.21f + image->data[index * image->channels + 1] * 0.72f + image->data[index * image->channels + 2] * 0.07f;
}
