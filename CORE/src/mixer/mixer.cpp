#include <atae_fp/mixer/mixer.h>

AudioBuffer Mixer::mix(const std::vector<MixInput>& inputs) {

	// assuming input lengths are the same
	size_t sample_count = inputs[0].audio_buffer.samples.size();
	AudioBuffer output;
	output.samples.clear();
	output.samples.resize(sample_count, 0.0);
	double mixed = 0.0;

	for (size_t i = 0; i < sample_count; ++i) {
		for (size_t j = 0; j < inputs.size(); ++j) {
			mixed += inputs[j].audio_buffer.samples[i] * inputs[j].gain;
		}

		output.samples[i] = mixed;
		mixed = 0.0;
	}

	return output;
}