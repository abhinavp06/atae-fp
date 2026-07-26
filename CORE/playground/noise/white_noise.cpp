#include <atae_fp/noise/white_noise.h>

int main() {
	WhiteNoise wn;
	wn.setSampleRate(44100.0);
	wn.setAmplitude(0.5);
	wn.generate(2);

	return 0;
}