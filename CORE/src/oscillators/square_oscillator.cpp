#include <atae_fp/oscillators/square_oscillator.h>
#include <vector>
#include <cmath>

void SquareOscillator::setDutyCycle(double duty_cycle) {
	duty_cycle_ = duty_cycle;
	threshold_ = duty_cycle_ * 2 * std::numbers::pi;
}

std::vector<double> SquareOscillator::generate(double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);
	std::vector<double> samples(sample_count);

	for (int i = 0; i < sample_count; i++) {
		samples[i] = ((phase_ < threshold_) ? 1.0 : -1.0 ) * amplitude_;
		advancePhase();
	}

	return samples;
}