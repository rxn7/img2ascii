#pragma once

#include <stdint.h>

typedef enum ColorType : uint8_t {
	NoColor,
	Ansi256,
	TrueColor
} ColorType;

typedef struct Settings {
	const char *image_path;
	uint8_t target_width;
	ColorType color_type;
} Settings;

void settings_init(Settings *settings, int argc, const char *argv[]);
