#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <array>
#include <cstdlib>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>

using namespace std;

class Common
{
public:
	static void FlushInput()
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
#endif

