#include <atae_fp/oscillators/saw_oscillator.h>
#include <atae_fp/io/audio_file.h>

const double SAMPLE_RATE = 100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 2.0;
const double AMPLITUDE = 0.5;


int main() {
	SawOscillator saw;
	saw.setAmplitude(AMPLITUDE);
	saw.setFrequency(WAVE_FREQUENCY);
	saw.setSampleRate(SAMPLE_RATE);
	AudioBuffer buffer = saw.generate(WAVE_DURATION_S);

	AudioFile output;
	output.save(OUTPUT_DIR "saw_wave.wav", buffer, SAMPLE_RATE);
	
	return 0;
}