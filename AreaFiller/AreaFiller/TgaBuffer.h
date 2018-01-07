#pragma once
#include "Buffer.h"
#include <string>
#include <map>
#include <stack>

struct Line {
	int x, y, len;
};

class TgaBuffer :
	public Buffer
{
public:
	TgaBuffer(int width, int height) : Buffer(width, height) {};
	TgaBuffer(std::string fileName);

	~TgaBuffer();

	void drawRect(const std::pair<int, int>& start, const std::pair<int, int>& end, unsigned int color);
	void fillArea(const std::pair<int, int>& p, unsigned int fillColor, int step);
	void fillAreaSmith(const std::pair<int, int>& p, unsigned int fillColor, int step);

	bool save(const std::string name) const;
	void setEndResolution(const std::pair<int, int> &res);

private:
	unsigned int* computeImage(const int wWidth, const int wHeight) const;
	int at(int x, int y);
	int at(const std::pair<int, int>& p);
	void fill(int x, int y, unsigned int col, unsigned int checkCol);
	void fillColorAt(const std::pair<int, int>& p, unsigned int color);
	Line findLine(const std::pair<int, int>& p, unsigned int workingColor);
	void lookForLinesFromPoint(const std::pair<int, int>& p, unsigned int color, int len, std::stack<Line>& st);

	int step;
	int endx, endy;
};

