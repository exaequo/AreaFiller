#include "stdafx.h"
#include "TGABuffer.h"
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

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



bool TgaBuffer::save(const std::string filename, const int wWidth, const int wHeight) const
{
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


void TgaBuffer::fillArea(const std::pair<int, int>& p, unsigned int fillColor)
{
	unsigned int color = colorBuffer[at(p.first, p.second)];

	fill(p.first, p.second, fillColor, color);
}

void TgaBuffer::fill(int x, int y, unsigned int col, unsigned int checkCol)
{
	if (coordCheck(x, y)) {
		if (colorBuffer[at(x, y)] == checkCol) {
			colorBuffer[at(x, y)] = col;

			fill(x + 1, y, col, checkCol);
			fill(x - 1, y, col, checkCol);
			fill(x, y + 1, col, checkCol);
			fill(x, y - 1, col, checkCol);
		}

	}

}








