#include "debug.h"
#include "image.h"
#include "args.h"
#include "color.h"

#include <math.h>
#include <stdio.h>

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

const char characters[] = { '.', ',', ':', ';', '!', '?', '#', '@' };

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

static void print_true_color_background(const Image *image, const size_t idx) {
	uint8_t r,g,b;
	get_rgb(image, idx, &r, &g, &b);
	printf("\033[48;2;%d;%d;%dm \033[0m", r, g, b);
}

static void print_ansi_256(const char character, const Image *image, const size_t idx) {
	uint8_t r,g,b;
	get_rgb(image, idx, &r, &g, &b);
	uint8_t ansi_color = rgb_to_ansi(r, g, b);

	printf("\033[48;5;%dm%c\033[0m", ansi_color, character); 
}

static void print_ansi_256_background(const Image *image, const size_t idx) {
	uint8_t r,g,b;
	get_rgb(image, idx, &r, &g, &b);
	uint8_t ansi_color = rgb_to_ansi(r, g, b);

	printf("\033[48;5;%dm \033[0m", ansi_color); 
}

int main(const int argc, const char *argv[]) {
	const clock_t args_init_start_time = clock();
	Arguments args; 
	if(!args_init(&args, argc, argv)) {
		return 1;
	}

	if(args.verbose) {
		print_time_took("Initializing args", args_init_start_time);
	}
	
	Image image;
	if(!image_load(&image, &args)) {
		return 1;
	}

	const clock_t draw_start_time = clock();
	for(int y = 0; y < image.height; y++) {
		for(int x = 0; x < image.width; x++) {
			const size_t idx = y * image.width + x; 
			const uint8_t intensity = image_get_pixel_intensity(&image, idx);

			if(args.background) {

				// Usually monospace fonts have 1:2 ratio
				// TODO: optimize this if needed
				for(int i = 0; i < 2; i++) {
					switch(args.color_type) {
						default:
							break;

						case TrueColor:
							print_true_color_background(&image, idx);
							break;

						case Ansi256:
							print_ansi_256_background(&image, idx);
							break;
					}
				}
			} else {
				const uint8_t character_idx = (uint8_t)floorf((intensity / 255.0f) * (LENGTH(characters) - 1));
				const char character = characters[character_idx];

				// Usually monospace fonts have 1:2 ratio
				// TODO: optimize this if needed
				for(int i = 0; i < 2; i++) {
					switch(args.color_type) {
						case NoColor:
							putchar(character);
							break;

						case TrueColor:
							print_true_color(character, &image, idx);
							break;

						case Ansi256:
							print_ansi_256(character, &image, idx);
							break;
					}
				}
			}
		}
		printf("\n");
	}

	if(args.verbose) {
		print_time_took("Drawing", draw_start_time);
	}

	image_free(&image);
	return 0;
}
