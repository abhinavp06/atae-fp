#include <atae_fp/oscillators/saw_oscillator.h>
#include <vector>
#include <cmath>
#include <numbers>

std::vector<double> SawOscillator::generate(double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	std::vector<double> samples(sample_count);

	for (int i = 0; i < sample_count; i++) {
		samples[i] = (phase_ / std::numbers::pi - 1) * amplitude_;
		advancePhase();
	}

	return samples;
}