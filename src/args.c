#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_int_opt(const char *short_opt, const char *long_opt, int idx, const int argc, const char *argv[]) {
	if(strcmp(argv[idx], short_opt) != 0 && strcmp(argv[idx], long_opt) != 0) {
		return -1;
	}

	if(idx + 1 >= argc) {
		return -1;
	}

	return atoi(argv[++idx]);
}

static bool get_bool_opt(const char *short_opt, const char *long_opt, const int idx, const int argc, const char *argv[]) {
	return strcmp(argv[idx], short_opt) == 0 || strcmp(argv[idx], long_opt) == 0;
}

void settings_init(Settings *settings, int argc, const char *argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <input image>\n", argv[0]);
		exit(1);
	}

	settings->image_path = argv[1];
	settings->target_width = 32;
	settings->color_type = NoColor;

	for(int i = 2; i < argc; i++) {
		int width = get_int_opt("-w", "--width", i, argc, argv);

		if(width != -1) {
			settings->target_width = width;
			continue;
		}

		if(get_bool_opt("-a", "--ansi", i, argc, argv)) {
			settings->color_type = Ansi256;
			continue;
		}

		if(get_bool_opt("-t", "--truecolor", i, argc, argv)) {
			settings->color_type = TrueColor;
			continue;
		}
	}
}
