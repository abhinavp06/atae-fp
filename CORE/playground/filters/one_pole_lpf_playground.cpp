#include <atae_fp/filters/one_pole_lpf.h>
#include <atae_fp/noise/white_noise.h>
#include <atae_fp/io/audio_file.h>

const double SAMPLE_RATE = 44100.0;

int main() {
    
    OnePoleLpf filter;
    filter.setSampleRate(SAMPLE_RATE);
    filter.setCutoffFrequency(1000.0);

    WhiteNoise noise;
    noise.setSampleRate(SAMPLE_RATE);
    noise.setAmplitude(1.0);
    AudioBuffer buffer = noise.generate(5.0);

    AudioFile output;
    output.save(OUTPUT_DIR "one_pole_lpf_white_noise_input.wav", buffer, SAMPLE_RATE);

    for(auto& sample : buffer.samples) {
        sample = filter.process(sample);
    }

    output.save(OUTPUT_DIR "one_pole_lpf_white_noise_output.wav", buffer, SAMPLE_RATE);

    return 0;
}