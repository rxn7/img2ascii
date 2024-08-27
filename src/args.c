#define REDFLAG_IMPLEMENTATION
#include "args.h"
#include "redflag.h"

bool args_init(Arguments *args, int argc, const char *argv[]) {
	rf_init_context(&args->rf_ctx);
	rf_flag_t *path_flag = rf_flag_str(&args->rf_ctx, "path", "Image path", NULL);
	rf_flag_t *width_flag = rf_flag_int(&args->rf_ctx, "width", "Target width", 32);
	rf_flag_t *verbose_flag = rf_flag_bool(&args->rf_ctx, "verbose", "Verbose output", false);
	rf_flag_t *background_flag = rf_flag_bool(&args->rf_ctx, "bg", "Use background instead of foreground", false);
	rf_flag_t *help_flag = rf_flag_bool(&args->rf_ctx, "help", "Print help", false);
	rf_flag_t *color_flag = rf_flag_str(&args->rf_ctx, "color", "Color type to use (truecolor, none, ansi)", "truecolor");
	rf_parse_flags(&args->rf_ctx, argc, argv);

	if(argc < 2 || help_flag->value.as_bool) {
		rf_print_options(&args->rf_ctx);
		return false;
	}

	args->image_path = path_flag->value.as_str;
	if(args->image_path == NULL) {
		fprintf(stderr, "Missing image path!\n");
		rf_print_options(&args->rf_ctx);
		return false;
	}

	printf("Width flag: %d\n", width_flag->value.as_int);

	args->target_width = width_flag->value.as_int;

	if(strcmp(color_flag->value.as_str, "truecolor") == 0) {
		args->color_type = TrueColor;
	} else if(strcmp(color_flag->value.as_str, "ansi") == 0) {
		args->color_type = Ansi256;
	} else {
		args->color_type = NoColor;
	}

	args->verbose = verbose_flag->value.as_bool;
	args->background = background_flag->value.as_bool;

	rf_free_context(&args->rf_ctx);
	return true;
}
