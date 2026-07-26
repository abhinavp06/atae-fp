#pragma once
#include <vector>
#include <atae_fp/oscillators/oscillator.h>
#include <atae_fp/types/audio_buffer.h>

class SawOscillator : public Oscillator {
public:
	AudioBuffer generate(double duration_s) override;
};