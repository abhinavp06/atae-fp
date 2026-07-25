#include <iostream>
#include <numbers>
#include <cmath>
#include <string>
#include <format>
#include <vector>
#include <fstream>

const double SAMPLE_RATE = 100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 2.0;

void generateCSV(const std::vector<double>& samples) {
	std::string result = "time,amplitude\n";
	const std::size_t sample_count = samples.size();

	for (std::size_t i = 0; i < sample_count; i++) {
		result += std::format("{},{}", i / SAMPLE_RATE, samples[i]);

		if (i != sample_count - 1) result += "\n";
	}

	std::ofstream output("./output/01_OSCILLATORS/square/square_wave.csv");

	if (!output.is_open()) {
		std::cerr << "Error: Could not open the file!" << std::endl;
		return;
	}

	output << result;

	output.close();
}

int main() {
	int sample_count = static_cast<int>(SAMPLE_RATE) * WAVE_DURATION_S;
	std::vector<double> samples(sample_count);

	double phase = 0.0;
	const double phase_increment = 2 * std::numbers::pi * WAVE_FREQUENCY / SAMPLE_RATE;

	for (int i = 0; i < sample_count; i++) {
		if (phase < std::numbers::pi) samples[i] = 1;
		else samples[i] = -1;

		phase += phase_increment;

		if (phase >= 2 * std::numbers::pi) phase -= 2 * std::numbers::pi;
	}

	generateCSV(samples);

	return 0;
}