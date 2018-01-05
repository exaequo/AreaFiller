#include "stdafx.h"
#include "functions.h"
#include <filesystem>
#include <sstream>
#include <stdio.h>
#include <iostream>

namespace fs = std::experimental::filesystem;

void removeFilesAt(std::string filesLocation)
{
	int i = 0;
	for (auto & p : fs::recursive_directory_iterator(filesLocation))
	{
		std::string line = p.path().filename().string().substr(0, p.path().filename().string().size() - 7);
		auto dot = divideLine(p.path().filename().string(), '.');

		if (dot.size() == 2) //if lines size would be 1 it means that we are looking at a directory not a png file
		{
			++i;
			std::stringstream ss{};
			ss << "result/";
			ss << p.path().filename().string().c_str();
			int val = std::remove(ss.str().c_str());

			if (val != 0)
			{				
				//std::cout << ss.str()<<"\n";
			}
		}
	}
	//std::cout << "Deleted " << i << "files\n";
}

std::vector<std::string> divideLine(const std::string & str, const char divider)
{
	std::vector<std::string> result{};
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, divider))
	{
		result.push_back(token);
	}
	return result;
}
