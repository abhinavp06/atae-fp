#include <atae_fp/noise/white_noise.h>
#include <atae_fp/io/audio_file.h>

int main() {
	WhiteNoise wn;
	wn.setSampleRate(44100.0);
	wn.setAmplitude(0.5);
	AudioBuffer buffer = wn.generate(2);

	AudioFile output;
	output.save(OUTPUT_DIR "white_noise.wav", buffer, 44100.0);

	return 0;
}