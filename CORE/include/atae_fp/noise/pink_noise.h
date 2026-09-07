#pragma once
#include <atae_fp/types/audio_buffer.h>

class PinkNoise {
public:
	void setSampleRate(double sample_rate);
	AudioBuffer generate(double duration_s);
private:
	const int NUM_ROWS = 20;
	double sample_rate_ = 44100.0;
};