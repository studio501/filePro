#ifndef __MAZE_TEST__HH_
#define __MAZE_TEST__HH_

struct PosType
{
	int x;
	int y;
};

#define MAXLENGTH 25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

MazeType m;
int g_x,g_y;
PosType g_begin,g_end;

void mazeTest();
#endif