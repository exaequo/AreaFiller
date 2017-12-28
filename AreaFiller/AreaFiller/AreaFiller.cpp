// AreaFiller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	TgaBuffer buff{ 15,10 };
	buff.ClearColor(0x00e0e0e0);
	/*for (int i = 0; i < 10; ++i)
	{

		buff.SetColor(15 * i + i, 0x00000000);
	}
	*/
	buff.drawRect({ 2,1 }, { 11,7 }, 0x00000000);
	buff.drawRect({ 5,-1 }, { 8,5 }, 0x00000000);
	buff.fillArea({ 4,3 }, 0x00ff0000);
	/*buff.fillArea({ 6,3 }, 0x000000ff);
	buff.fillArea({ 1,1 }, 0x0000ff00);
	buff.fillArea({ 2,1 }, 0x0000ff00);
	buff.fillArea({ 1,1 }, 0x00000000);
*/
	buff.save("test.tga", 1500, 1000);

    return 0;
}

