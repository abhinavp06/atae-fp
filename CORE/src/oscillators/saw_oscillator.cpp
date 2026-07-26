#include <atae_fp/oscillators/saw_oscillator.h>
#include <cmath>
#include <numbers>

AudioBuffer SawOscillator::generate(double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	
	buffer_.samples.clear();
	buffer_.samples.reserve(sample_count);

	for (int i = 0; i < sample_count; i++) {
		buffer_.samples.push_back((phase_ / std::numbers::pi - 1) * amplitude_);
		advancePhase();
	}

	return buffer_;
}