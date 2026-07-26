#pragma once
#include <vector>
#include <atae_fp/oscillators/oscillator.h>

class SawOscillator : public Oscillator {
public:
	std::vector<double> generate(double duration_s) override;
};