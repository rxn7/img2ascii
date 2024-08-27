#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "image.h"
#include "debug.h"

#include <time.h>

void image_free(Image *image) {
	stbi_image_free((void*)image->data);
}

bool image_load(Image *image, Arguments *args) {
	if(args->verbose) {
		printf("Loading image: %s\n", args->image_path);
	}

	const clock_t image_load_start_time = clock();
	image->data = stbi_load(args->image_path, &image->width, &image->height, &image->channels, 0);

	if(args->verbose) {
		print_time_took("Loading image", image_load_start_time);
	}

	if(image->data == NULL) {
		fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
		return false;
	}

	if(args->target_width > image->width) {
		args->target_width = image->width;
		fprintf(stderr, "Source image is smaller than requested width!\n");
	}

	const int target_height = image->height / (image->width / (float)args->target_width);

	const clock_t image_resize_start_time = clock();
	stbir_resize_uint8_linear(image->data, image->width, image->height, image->width * image->channels, image->data, args->target_width, target_height, args->target_width * image->channels, image->channels);

	if(args->verbose) {
		print_time_took("Resizing image", image_load_start_time);
	}

	image->width = args->target_width;
	image->height = target_height;

	return true;
}

uint8_t image_get_pixel_intensity(const Image *image, const int index) {
	return image->data[index * image->channels + 0] * 0.21f + image->data[index * image->channels + 1] * 0.72f + image->data[index * image->channels + 2] * 0.07f;
}
