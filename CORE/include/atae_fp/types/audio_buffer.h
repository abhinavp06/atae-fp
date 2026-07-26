#pragma once
#include <vector>

class AudioBuffer {
public:
	void setSampleRate(double sample_rate);
	// buffer expose ...??
private:
	double sample_rate_ = 44100.0;
	std::vector<double> buffer_ = { 0 };
};