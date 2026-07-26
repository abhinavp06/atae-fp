#include <atae_fp/noise/white_noise.h>

void WhiteNoise::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
}

void WhiteNoise::setAmplitude(double amplitude) {
	amplitude_ = amplitude;
}

std::vector<double> WhiteNoise::generate(const double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	std::vector<double> samples(sample_count);


	for (int i = 0; i < sample_count; i++) {
		samples[i] = dist_(engine_) * amplitude_;
	}

	return samples;
}