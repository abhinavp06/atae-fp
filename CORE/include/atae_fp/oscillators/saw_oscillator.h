#pragma once
#include <vector>
#include <atae_fp/oscillators/oscillator.h>

class SawOscillator : public Oscillator {
public:
	AudioBuffer generate(double duration_s) override;
};