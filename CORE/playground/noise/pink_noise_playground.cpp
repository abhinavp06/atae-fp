#include <atae_fp/noise/pink_noise.h>
#include <atae_fp/io/audio_file.h>

int main() {
	PinkNoise pn;
	pn.setSampleRate(44100.0);

	AudioBuffer buffer = pn.generate(10.0);

	AudioFile output;
	output.save(OUTPUT_DIR "pink_noise.wav", buffer, 44100.0);
}