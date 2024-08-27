#define REDFLAG_IMPLEMENTATION
#include "args.h"
#include "redflag.h"

bool settings_init(Settings *settings, int argc, const char *argv[]) {
	rf_init_context(&settings->rf_ctx);
	rf_flag_t *path_flag = rf_flag_str(&settings->rf_ctx, "path", "Image path", NULL);
	rf_flag_t *width_flag = rf_flag_int(&settings->rf_ctx, "width", "Target width", 32);
	rf_flag_t *verbose_flag = rf_flag_bool(&settings->rf_ctx, "verbose", "Verbose output", false);
	rf_flag_t *help_flag = rf_flag_bool(&settings->rf_ctx, "help", "Print help", false);
	rf_flag_t *color_flag = rf_flag_str(&settings->rf_ctx, "color", "Color type to use (truecolor, none, ansi)", "truecolor");
	rf_parse_flags(&settings->rf_ctx, argc, argv);

	if(argc < 2 || help_flag->value.as_bool) {
		rf_print_options(&settings->rf_ctx);
		return false;
	}

	settings->image_path = path_flag->value.as_str;
	if(settings->image_path == NULL) {
		fprintf(stderr, "Missing image path!\n");
		rf_print_options(&settings->rf_ctx);
		return false;
	}

	settings->target_width = width_flag->value.as_int;

	if(strcmp(color_flag->value.as_str, "truecolor") == 0) {
		settings->color_type = TrueColor;
	} else if(strcmp(color_flag->value.as_str, "ansi") == 0) {
		settings->color_type = Ansi256;
	} else {
		settings->color_type = NoColor;
	}

	settings->verbose = verbose_flag->value.as_bool;

	rf_free_context(&settings->rf_ctx);
	return true;
}
