#pragma once
#include <atae_fp/oscillators/oscillator.h>

class SineOscillator : public Oscillator {
public:
	AudioBuffer generate(double duration_s) override;
};