#include <iostream>
#include <numbers>
#include <cmath>
#include <string>
#include <format>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>

const double SAMPLE_RATE = 100;
const int WAVE_DURATION_S = 2;

void generateCSV(const std::vector<double>& samples) {
	std::string result = "time,amplitude\n";
	const std::size_t sample_count = samples.size();

	for (std::size_t i = 0; i < sample_count; i++) {
		result += std::format("{},{}", i / SAMPLE_RATE, samples[i]);

		if (i != sample_count - 1) result += "\n";
	}

	std::string output_path = std::string(OUTPUT_DIR) + "/white_noise.csv";
	std::ofstream output(output_path);

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

	std::mt19937 engine(std::random_device{}() ^ static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	for (int i = 0; i < sample_count; i++) {
		samples[i] = dist(engine);
	}

	generateCSV(samples);

	return 0;
}