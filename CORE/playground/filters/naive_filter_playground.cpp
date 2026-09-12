#include <atae_fp/filters/naive_filter.h>
#include <atae_fp/io/audio_file.h>
#include <atae_fp/noise/white_noise.h>

const double SAMPLE_RATE = 44100.0;

int main() {
    // Create an instance of the NaiveFilter
    NaiveFilter filter;

    // Generate some white noise
    WhiteNoise noise;
    noise.setSampleRate(SAMPLE_RATE);
    AudioBuffer buffer = noise.generate(5.0);

    AudioFile output;
    output.save(OUTPUT_DIR "naive_filter_white_noise_input.wav", buffer, SAMPLE_RATE);

    filter.setGain(0.8);
    
    for(auto& sample : buffer.samples) {
        sample = filter.process(sample);
    }
    
    output.save(OUTPUT_DIR "naive_filter_white_noise_output.wav", buffer, SAMPLE_RATE);

    return 0;
}