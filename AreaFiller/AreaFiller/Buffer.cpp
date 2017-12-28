#include "stdafx.h"
#include "Buffer.h"
#include <exception>

Buffer::Buffer(int bufferWidth, int bufferHeight) : width{ bufferWidth }, height{ bufferHeight }, len{ width * height }
{
	colorBuffer = new unsigned int[len];
	
}

Buffer::~Buffer()
{
	delete[] colorBuffer;
	
}



bool Buffer::coordCheck(int x, int y) const
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

void Buffer::ClearColor(unsigned int color)
{
	clearColor = color;
	for (unsigned int i = 0; i < len; ++i)
	{
		colorBuffer[i] = color;
	}
}


void Buffer::SetColor(unsigned int pos, unsigned int color)
{
	if (pos >= len)return;//throw std::exception{ "out of buffer length" };

	colorBuffer[pos] = color;
}

