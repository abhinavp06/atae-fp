#include <atae_fp/envelope/adsr.h>
#include <atae_fp/io/audio_file.h>
#include <atae_fp/oscillators/sine_oscillator.h>
#include <algorithm>
#include <cmath>
#include <iostream>

const double SAMPLE_RATE = 44100.0;
const double DURATION_S = 30.0;

int main()
{
    SineOscillator sine_osc;
    sine_osc.setSampleRate(SAMPLE_RATE);
    sine_osc.setFrequency(440.0); // A4 note
    sine_osc.setAmplitude(0.5);
    AudioBuffer sine_buffer = sine_osc.generate(DURATION_S);

    double raw_peak = 0.0;
    for (const auto& s : sine_buffer.samples) raw_peak = std::max(raw_peak, std::abs(s));
    std::cout << "raw sine peak: " << raw_peak << "\n";

    Adsr adsr;
    adsr.setAttack(4.0, SAMPLE_RATE);
    adsr.setDecay(8.0, SAMPLE_RATE);
    adsr.setSustain(0.5);
    adsr.setRelease(5.0, SAMPLE_RATE);
    int note_off_sample = static_cast<int>(DURATION_S - 5.0) * SAMPLE_RATE; // duration_s - release time

    adsr.noteOn();

    double max_sample = 0.0;

    int index = 0;
    for (auto &sample : sine_buffer.samples)
    {
        sample *= adsr.process();
        const char* state_str = adsr.getState() == AdsrState::Idle ? "Idle" :
                              adsr.getState() == AdsrState::Attack ? "Attack" :
                              adsr.getState() == AdsrState::Decay ? "Decay" :
                              adsr.getState() == AdsrState::Sustain ? "Sustain" :
                              adsr.getState() == AdsrState::Release ? "Release" : "Unknown";

        if(sample >= 1.0) {
            std::cout << "Sample value exceeded 1.0 at index " << index << ", value: " << sample << ", state: " << state_str << std::endl;
        }

        // max_sample = std::max(max_sample, std::abs(sample));
        if(std::abs(sample) > max_sample) {
            std::cout << "New max sample value: " << std::abs(sample) << " at index " << index << ", state: " << state_str << std::endl;
            max_sample = std::abs(sample);
        }

        if(index == note_off_sample)
        {
            adsr.noteOff();
        }

        ++index;
    }

    std::cout << "Max sample value after applying ADSR: " << max_sample << std::endl;

    AudioFile audio_file;
    audio_file.save(OUTPUT_DIR "adsr_output.wav", sine_buffer, SAMPLE_RATE);
}