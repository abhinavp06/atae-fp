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

        max_sample = std::max(max_sample, std::abs(sample));

        if(index == note_off_sample)
        {
            adsr.noteOff();
        }

        ++index;
    }

    AudioFile audio_file;
    audio_file.save(OUTPUT_DIR "adsr_output.wav", sine_buffer, SAMPLE_RATE);
}