#include <atae_fp/oscillators/sine_oscillator.h>
#include <atae_fp/io/audio_file.h>

const double SAMPLE_RATE = 44100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 441.0;
const double AMPLITUDE = 0.5;

int main() {
	SineOscillator sine;
	sine.setAmplitude(AMPLITUDE);
	sine.setFrequency(WAVE_FREQUENCY);
	sine.setSampleRate(SAMPLE_RATE);
	AudioBuffer buffer = sine.generate(WAVE_DURATION_S);

	AudioFile output;
	output.save(OUTPUT_DIR "sine_wave.wav", buffer, SAMPLE_RATE);

	return 0;
}