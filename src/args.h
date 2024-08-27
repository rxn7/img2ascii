#pragma once

#include <stdint.h>
#include <redflag.h>

typedef enum ColorType : uint8_t {
	NoColor,
	Ansi256,
	TrueColor
} ColorType;

typedef struct Settings {
	rf_context_t rf_ctx;
	const char *image_path;
	uint8_t target_width;
	ColorType color_type;
	bool verbose;
} Settings;

bool settings_init(Settings *settings, int argc, const char *argv[]);
