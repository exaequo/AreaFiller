#include "stdafx.h"
#include "TGABuffer.h"
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
//std::map<std::string, class Texture> TgaBuffer::textures = std::map<std::string, class Texture>{};
//std::map<int, std::string> TgaBuffer::materialsToTextureNames = std::map<int, std::string>{};

TgaBuffer::~TgaBuffer()
{
}

void TgaBuffer::drawRect(const std::pair<int, int>& start, const std::pair<int, int>& end, unsigned int color)
{
	for (int j = start.second; j < end.second; ++j) {
		for (int i = start.first; i < end.first; ++i) {
			if (i == start.first || i == end.first - 1 ||
				j == start.second || j == end.second - 1)
			{
				SetColor(at(i, j), color);
			}
		}
	}
}



bool TgaBuffer::save(const std::string filename) const
{
	int wWidth = endx, wHeight = endy;

	unsigned int* newColorBuffer = computeImage(wWidth, wHeight);
	
	unsigned short header[9] =
	{
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, 0x0820
	};
	FILE *f;
	fopen_s(&f, filename.c_str(), "wb+");

	if (!f) {
		delete[] newColorBuffer;
		return false;
	}

	header[6] = wWidth;
	header[7] = wHeight;

	fwrite(header, 2, 9, f);
	fwrite(newColorBuffer, 4, wWidth * wHeight, f);

	fclose(f);

	delete[] newColorBuffer;
	return true;
}

void TgaBuffer::setEndResolution(const std::pair<int, int>& res)
{
	endx = res.first;
	endy = res.second;
}

unsigned int * TgaBuffer::computeImage(const int wWidth, const int wHeight) const
{
	unsigned int* cb = new unsigned int[wWidth * wHeight];

	int
		xratio = wWidth / width,
		yratio = wHeight / height;

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			for (int n = 0; n < yratio; ++n) {
				for (int m = 0; m < xratio; ++m) {
					unsigned int which = (int)((j * yratio + n) * wWidth + i * xratio + m);
					unsigned int size = wWidth * wHeight;
					if (which < size) {
						cb[which] = colorBuffer[j*width + i];//0x00ff0000;
					}
					//cb[(j + n) * wWidth + i + m] = colorBuffer[j*width + i];
				}
			}
		}
	}

	//for (int j = 0; j < wHeight; ++j) {
	//	for (int i = 0; i < wWidth; ++i) {
	//		cb[j*wWidth + i] = 0x00ff0000;
	//	}
	//}
	return cb;
}

int TgaBuffer::at(int x, int y)
{
	return y*width + x;
}

int TgaBuffer::at(const std::pair<int, int>& p)
{
	return at(p.first, p.second);
}


void TgaBuffer::fillArea(const std::pair<int, int>& p, unsigned int fillColor, int step)
{
	unsigned int color = colorBuffer[at(p.first, p.second)];
	this->step = step;

	fill(p.first, p.second, fillColor, color);

}

void TgaBuffer::fillAreaSmith(const std::pair<int, int>& p, unsigned int fillColor, int step)
{
	unsigned int workColor = colorBuffer[at(p.first, p.second)];
	std::stack<Line> st{};
	this->step = step;

	st.push(findLine(p, workColor));
		
	do {
		Line line = st.top();
		st.pop();

		if (colorBuffer[at(line.x, line.y)] == workColor)
		{
			//std::cout << "Line: (" << line.x << "," << line.y << ") " << line.len << "\n";

			for (int i = line.x; i < line.x + line.len; ++i)
			{
				fillColorAt({ i, line.y }, fillColor);
			}

			if (line.y + 1 < height)
			{
				lookForLinesFromPoint({ line.x, line.y + 1 }, workColor, line.len, st);
			}

			if (line.y - 1 >= 0)
			{
				//std::cout << "Parent line: (" << line.x << ", " << line.y << ")\n";
				lookForLinesFromPoint({ line.x, line.y - 1 }, workColor, line.len, st);
			}
		}

		
	} while (!st.empty());

}



void TgaBuffer::fill(int x, int y, unsigned int col, unsigned int checkCol)
{
	if (coordCheck(x, y)) {
		if (colorBuffer[at(x, y)] == checkCol) {
			//static int counter = 0;
			//colorBuffer[at(x, y)] = col;

			//if (++counter % step == 0) {
			//	std::stringstream s{};
			//	s << "fill" << counter << ".tga";
			//	save(s.str());
			//	//std::cin.get();
			//}
			
			fillColorAt({ x,y }, col);

			fill(x + 1, y, col, checkCol);
			fill(x - 1, y, col, checkCol);
			fill(x, y + 1, col, checkCol);
			fill(x, y - 1, col, checkCol);
		}

	}

}

void TgaBuffer::fillColorAt(const std::pair<int, int>& p, unsigned int color)
{
	static int counter = 0;
	colorBuffer[at(p.first, p.second)] = color;

	if (++counter % step == 0) {
		std::stringstream s{};
		s << "result/fill" << counter << ".tga";
		save(s.str());
		//std::cin.get();
	}
}

Line TgaBuffer::findLine(const std::pair<int, int>& p, unsigned int workColor)
{
	int i = 1;
	int j = 1;

	//std::cout << "Work: " << workColor << ", at0: " << colorBuffer[at(p.first - i, p.second)] << "\n";


	while (p.first - i >= 0 && colorBuffer[at(p.first - i, p.second)] == workColor)
	{
		++i;
	}
	--i;

	while (p.first - i + j < width && colorBuffer[at(p.first - i + j, p.second)] == workColor)
	{
		++j;
	}

	return Line{ p.first - i, p.second, j };
}

void TgaBuffer::lookForLinesFromPoint(const std::pair<int, int>& p, unsigned int color, int len, std::stack<Line>& st)
{
	//std::cout << "Point start: " << p.first<<","<<p.second << "\n";
	bool waitForNext = true;
	for (int i = 0; i < len; ++i)
	{
		if (colorBuffer[at(p.first + i, p.second)] == color)
		{
			if (waitForNext)
			{
				st.push(findLine({ p.first + i, p.second }, color));
				waitForNext = false;
			}
		}
		else
		{
			waitForNext = true;
		}
	}
}










