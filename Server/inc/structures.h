#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include "types.h"

/**
 * @author xiao.hy
 */

struct Position
{
	_uintd x, y;
};

struct Chunk
{
	static const WIDTH = 16, HEIGHT = 8;
	char data[WIDTH * HEIGHT];
};

struct Connection
{
	int fd;
	_uintd world;
	Position ltn[4];
	Connection* nexts[4];
};

struct DBSaveMsg
{
	_vintd version;
	Position pos;
};

struct DBGetMsg
{
	Position pos;
	Chunk* p;
};

struct DBMsg
{
	int fd;
	_msize remained;
	union
	{
		DBGetMsg getMsg;
		DBSaveMsg saveMsg;
	}
};

struct DBQueryMsg
{
	_byted type;
	_uintd world;
	Position pos;
	Chunk* p;
};

struct EpollMsg
{
	_byted type;
	union
	{
		DBMsg msg;
	};
};

#endif