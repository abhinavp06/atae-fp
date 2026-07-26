#pragma once
#include <vector>

class AudioBuffer {
public:
	void setSampleRate(double sample_rate);
	void setDuration(double duration_s);
	void reset();
private:
	double sample_rate_ = 44100.0;
	double duration_s_ = 0.0;
protected:
	std::vector<double> buffer_;
};