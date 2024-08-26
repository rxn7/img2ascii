#include "image.h"
#include "args.h"

#include <math.h>
#include <stdio.h>

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

const char characters[] = { ' ', '.', ',', ':', ';', '!', '?', '#', };

static void get_rgb(const Image *image, const size_t idx, uint8_t *r, uint8_t *g, uint8_t *b) {
	*r = image->data[idx * image->channels + 0];
	*g = image->data[idx * image->channels + 1];
	*b = image->data[idx * image->channels + 2];
}

static void print_true_color(const char character, const Image *image, const size_t idx) {
	uint8_t r,g,b;
	get_rgb(image, idx, &r, &g, &b);
	printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, character);
}

int main(const int argc, const char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <input image>\n", argv[0]);
		return 1;
	}

	Settings settings; 
	settings_init(&settings, argc, argv);
	
	Image image;
	if(!image_load(&image, settings.image_path, settings.target_width)) {
		return 1;
	}

	for(int y = 0; y < image.height; y++) {
		for(int x = 0; x < image.width; x++) {
			const size_t idx = y * image.width + x; 
			const uint8_t intensity = image_get_pixel_intensity(&image, idx);
			const uint8_t character_idx = (uint8_t)floorf((intensity / 255.0f) * (LENGTH(characters) - 1));
			const char character = characters[character_idx];

			// Usually monospace fonts have 1:2 ratio
			// TODO: optimize this if needed
			for(int i = 0; i < 2; i++) {
				switch(settings.color_type) {
					case NoColor:
						putchar(character);
						break;

					case TrueColor:
						print_true_color(character, &image, idx);
						break;

					case Ansi256:
						// TODO:
						putchar(character);
						break;
				}
			}
		}
		printf("\n");
	}

	image_free(&image);
	return 0;
}
