#include <atae_fp/oscillators/sine_oscillator.h>
#include <vector>
#include <cmath>

std::vector<double> SineOscillator::generate(double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	std::vector<double> samples(sample_count);

	for (int i = 0; i < sample_count; i++) {
		samples[i] = std::sin(phase_) * amplitude_;
		advancePhase();
	}

	return samples;
}