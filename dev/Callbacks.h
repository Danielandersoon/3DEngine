#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <stdio.h>
#include "Utilities.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error:%s\n", description);
	throw("error");
}

static void window_open_callback()
{
	write_log("app open ");
}

static void window_close_callback()
{
	write_log("app closed ");
}

#endif CALLBACKS_H