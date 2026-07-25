#include <iostream>
#include <numbers>
#include <math.h>

const double SAMPLE_RATE = 44100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 441.0;

int main() {
	int sample_count = static_cast<int>(SAMPLE_RATE) * WAVE_DURATION_S;
	double samples[sample_count] = { 0 };

	double phase = 0.0, phase_increment = 2 * std::numbers::pi * WAVE_FREQUENCY / SAMPLE_RATE;

	for (int i = 0; i < sample_count; i++) {
		samples[i] = std::sin(phase);
		phase += phase_increment;

		if (phase >= 2 * std::numbers::pi) phase -= 2 * std::numbers * pi;
	}


	return 1;
}