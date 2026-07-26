#include <atae_fp/oscillators/sine_oscillator.h>
#include <vector>
#include <cmath>

AudioBuffer SineOscillator::generate(double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	
	buffer_.samples.clear();
	buffer_.samples.reserve(sample_count);

	for (int i = 0; i < sample_count; i++) {
		buffer_.samples.push_back(std::sin(phase_) * amplitude_);
		advancePhase();
	}

	return buffer_;
}