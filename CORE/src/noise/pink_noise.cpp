#include <atae_fp/noise/pink_noise.h>

void PinkNoise::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
	white_noise_.setSampleRate(sample_rate);
}

AudioBuffer PinkNoise::generate(const double duration_s) {
	std::vector<double> rows(NUM_ROWS, 0.0);

	double running_sum = 0.0;

	/**
	* 1. emit white noise at different frequencies... 2^k
	* 2. running_sum for better operations
	* 3. each row is an emitter...
	*/
}