#pragma once
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <amp.h>
#include <amp_math.h>
#include <time.h>
#include <string>
#include <array>
#include <math.h>


struct Complex1
{
	float x;
	float y;
};


using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::ofstream;

using std::chrono::duration_cast;
typedef std::chrono::steady_clock the_clock;
using namespace Concurrency::precise_math;



class Julia {

	Complex1 c;
	float iR;
	int itr; 
	void compute_JULIA_tile2(int width, int height, Complex1 c, double radius, int n);
	void compute_JULIA_tile4(int width, int height, Complex1 c, double radius, int n);
	void compute_JULIA_tile8(int width, int height, Complex1 c, double radius, int n);
	void compute_JULIA_tile16(int width, int height, Complex1 c, double radius, int n);
	void compute_JULIA_tile32(int width, int height, Complex1 c, double radius, int n);



public:
	Julia();
	~Julia();

	void Benchmark();
	void Ouput();
};