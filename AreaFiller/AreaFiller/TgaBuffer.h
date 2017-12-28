#pragma once
#include "Buffer.h"
#include <string>
#include <map>

class TgaBuffer :
	public Buffer
{
public:
	TgaBuffer(int width, int height) : Buffer(width, height) {};
	~TgaBuffer();

	void drawRect(const std::pair<int, int>& start, const std::pair<int, int>& end, unsigned int color);
	void fillArea(const std::pair<int, int>& p, unsigned int fillColor);


	bool save(const std::string name, const int windowWidth, const int windowHeight) const;

private:
	unsigned int* computeImage(const int wWidth, const int wHeight) const;
	int at(int x, int y);
	void fill(int x, int y, unsigned int col, unsigned int checkCol);
};

