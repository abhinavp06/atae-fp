#pragma once
#include <vector>
#include <chrono>
#include <random>
#include <atae_fp/types/audio_buffer.h>

class WhiteNoise {
public:
	void setSampleRate(double sample_rate);
	double processSample();
	AudioBuffer generate(const double duration_s);
	double processSample();

	WhiteNoise()
		: engine_(
			std::random_device{}() ^
			static_cast<unsigned>(
				std::chrono::high_resolution_clock::now()
				.time_since_epoch()
				.count()))
	{
	}
private:
	double sample_rate_ = 44100.0;
	std::mt19937 engine_;
	std::uniform_real_distribution<double> dist_{ -1.0, 1.0 };
	AudioBuffer buffer_;
};