#include <math.h>
#include <stdio.h>
#include "img2ascii.h"

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

const char characters[] = {
	' ', '.', ',', ':', ';', '!', '?', '#', 
};

int main(const int argc, const char *argv[]) {
	const char *input_file = argv[1];
	
	Image image;
	load_image(&image, input_file, 32);

	for(int y = 0; y < image.height; y++) {
		for(int x = 0; x < image.width; x++) {
			const size_t idx = y * image.width + x; 
			const uint8_t intensity = get_intensity(&image, idx);
			const uint8_t character_idx = (uint8_t)floorf((intensity / 255.0f) * (LENGTH(characters) - 1));
			const char character = characters[character_idx];

			// Usually monospace fonts are in 1:2 ratio
			putchar(character);
			putchar(character);
		}
		printf("\n");
	}

	free((void*)image.data);
	return 0;
}
