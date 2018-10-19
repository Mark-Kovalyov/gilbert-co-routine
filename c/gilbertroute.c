#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <io.h>

#ifdef _WIN32
#include "windows.h"
#endif

const int u = 1;  // pixel step

int glx;
int gly;

// BGI emulation
void linerel(int x, int y)
{
	glx += x;
	gly += y;
	printf("%d,%d\n", glx, gly);
}

void moveto(int x, int y)
{
	glx = x;
	gly = y;
	printf("%d,%d\n", glx, gly);
}

int offset_1[] = { u, -u, 0, 0 };
int offset_2[] = { 0, 0, -u, u };

void gilbert(int type, int level) {
	if (level > 0) {
		gilbert(3 - type, level - 1);
		linerel(offset_1[type], offset_2[type]);
		gilbert(type, level - 1);
		linerel(offset_2[type], offset_1[type]);
		gilbert(type, level - 1);
		linerel(-offset_1[type], -offset_2[type]);
		gilbert((3 - type) ^ 1, level - 1);
	}
}

int main(int argc, char **arg, char **env) {
	int level = 2;

	moveto(0, 0);
	gilbert(0, level);

	return 0;
}