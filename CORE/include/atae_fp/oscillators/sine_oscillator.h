#pragma once
#include <vector>
#include <atae_fp/oscillators/oscillator.h>

class SineOscillator : public Oscillator {
public:
	std::vector<double> generate(double duration_s) override;
};