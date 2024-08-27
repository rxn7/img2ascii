#include "color.h"

// https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
uint8_t rgb_to_ansi(uint8_t r, uint8_t g, uint8_t b) {
	// 0 >= rgb <= 5
	r /= 51;
	g /= 51;
	b /= 51;

	return 16 + (36 * r) + (6 * g) + b;
}
