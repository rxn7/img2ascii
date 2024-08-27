#pragma once

#include <stdio.h>
#include <time.h>

static inline void print_time_took(const char *prefix, const clock_t start_time) {
	const clock_t end_time = clock();
	printf("%s took %f ms\n", prefix, (end_time - start_time) * 1000.0f / CLOCKS_PER_SEC);
}
