#include <atae_fp/noise/white_noise.h>

void WhiteNoise::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
}

double WhiteNoise::processSample() {
	return dist_(engine_);
}

AudioBuffer WhiteNoise::generate(const double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	
	buffer_.samples.clear();
	buffer_.samples.reserve(sample_count);

	for (int i = 0; i < sample_count; i++) {
		buffer_.samples.push_back(processSample());
	}

	return buffer_;
}