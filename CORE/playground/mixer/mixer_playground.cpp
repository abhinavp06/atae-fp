#include <atae_fp/mixer/mixer.h>
#include <atae_fp/io/audio_file.h>
#include <atae_fp/oscillators/sine_oscillator.h>
#include <atae_fp/noise/white_noise.h>

const double SAMPLE_RATE = 44100.0;
const double DURATION_S = 10.0;

int main() {
    Mixer mixer;
    std::vector<MixInput> inputs;

    SineOscillator sine_osc;
    sine_osc.setSampleRate(SAMPLE_RATE);
    sine_osc.setFrequency(440.0); // A4 note
    sine_osc.setAmplitude(0.5);
    AudioBuffer sine_buffer = sine_osc.generate(DURATION_S);
    inputs.push_back({sine_buffer, 1.0});

    WhiteNoise white_noise;
    white_noise.setSampleRate(SAMPLE_RATE);
    AudioBuffer noise_buffer = white_noise.generate(DURATION_S);
    inputs.push_back({noise_buffer, 1.0});

    AudioBuffer mixed_buffer = mixer.mix(inputs, true);

    AudioFile audio_file;
    audio_file.save(OUTPUT_DIR "mixed_output.wav", mixed_buffer, SAMPLE_RATE);
}