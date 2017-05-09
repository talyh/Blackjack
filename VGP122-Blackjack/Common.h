#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <array>
#include <cstdlib>

using namespace std;

#ifndef COMMON_H
#define COMMON_H

class Common
{
public:
	static void FlushInput()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
#endif

