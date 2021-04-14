#include "POP.h"
#include "options.h"
#include "stdlib.h"

void* g_assets;

void POP_opts_init() {
	g_assets = malloc(10);
}

void POP_opts_cleanup(){
	free(g_assets);
}