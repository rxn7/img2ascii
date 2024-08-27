#pragma once

#include <stdint.h>
#include <redflag.h>

typedef enum ColorType : uint8_t {
	NoColor,
	Ansi256,
	TrueColor
} ColorType;

typedef struct Arguments {
	rf_context_t rf_ctx;
	const char *image_path;
	uint8_t target_width;
	ColorType color_type;
	bool verbose;
	bool background;
} Arguments;

bool args_init(Arguments *args, int argc, const char *argv[]);
