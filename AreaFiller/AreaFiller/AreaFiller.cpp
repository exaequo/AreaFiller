// AreaFiller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

int getInput()
{
	int result = 0;
	int input = _getch() - '0';
	while (input >= 0 && input < 10)
	{
		result *= 10;
		result += input;
		std::cout << input;
		input = _getch() - '0';


	}
	return result;
}

int main()
{
	removeFilesAt("result/");
	int x, y, step;
	
	bool loadFromFile = false;
	std::string filename;

	std::cout << "Load from file? [y/n]";
	loadFromFile =_getch() == 'y';
	

	if (loadFromFile)
	{
		std::cout << "\nFilename: ";
		std::cin >> filename;
		//std::cout << "\n";
	}

	std::cout << "\nPoint: (";
	//x = std::cin.get();
	x = getInput();//_getch() - '0';
	std::cout << ",";
	y = getInput();//_getch() - '0';
	std::cout << ")\n Step: ";
	step = getInput();//_getch() - '0';
	std::cout << "\n";

	TgaBuffer* buff;
	if (loadFromFile)
	{
		//TgaBuffer buff{ "example.tga" };
		//TgaBuffer buff{ "example.tga" };
		buff = new TgaBuffer("example.tga");
	}
	else
	{
		//TgaBuffer buff{ 19,10 };
		buff = new TgaBuffer(19,10);
		buff->ClearColor(0x00e0e0e0);
		buff->drawRect({ 2,1 }, { 15,7 }, 0x00000000);
		buff->drawRect({ 5,-1 }, { 8,5 }, 0x00000000);

	}
	//TgaBuffer buff{ 19,10 };
	//buff.ClearColor(0x00e0e0e0);
	
	
	buff->setEndResolution({ 1280, 720 });
	/*
	buff.drawRect({ 2,1 }, { 15,7 }, 0x00000000);
	buff.drawRect({ 5,-1 }, { 8,5 }, 0x00000000);
	*/
	buff->save("clear.tga");

	buff->fillAreaSmith({ x,y }, 0x00ff0000, step);
	
	buff->save("result/fillFinal.tga");

	delete buff;
	//std::cin.get();
    return 0;
}

