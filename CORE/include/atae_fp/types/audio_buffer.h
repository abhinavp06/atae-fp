#pragma once
#include <vector>

struct AudioBuffer {
	std::vector<double> samples;
	double sample_rate;
};