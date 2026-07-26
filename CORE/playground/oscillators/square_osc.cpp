#include <atae_fp/oscillators/square_oscillator.h>
#include <atae_fp/io/audio_file.h>

const double SAMPLE_RATE = 100.0;
const int WAVE_DURATION_S = 2;
const double WAVE_FREQUENCY = 2.0;
const double DUTY_CYCLE = 0.5;
const double AMPLITUDE = 0.5;

int main() {
	SquareOscillator square;
	square.setAmplitude(AMPLITUDE);
	square.setFrequency(WAVE_FREQUENCY);
	square.setSampleRate(SAMPLE_RATE);
	square.setDutyCycle(0.5);
	AudioBuffer buffer = square.generate(WAVE_DURATION_S);

	AudioFile output;
	output.save(OUTPUT_DIR "square_wave.wav", buffer, SAMPLE_RATE);

	return 0;
}