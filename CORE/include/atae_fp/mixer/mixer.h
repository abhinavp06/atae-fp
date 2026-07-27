#pragma once
#include <atae_fp/types/audio_buffer.h>

struct MixInput {
	AudioBuffer audio_buffer;
	double gain;
};

class Mixer {
public:
	AudioBuffer mix(const std::vector<MixInput>& inputs);
};