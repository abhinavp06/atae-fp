#include <atae_fp/filters/one_pole_lpf.h>

void OnePoleLpf::calculateAlpha() {
    alpha_ = 0.5;
}

void OnePoleLpf::setCutoffFrequency(double cutoff_frequency) {
    cutoff_frequency_ = cutoff_frequency;
    calculateAlpha();
}

void OnePoleLpf::setSampleRate(double sample_rate) {
    sample_rate_ = sample_rate;
    calculateAlpha();
}

double OnePoleLpf::process(double input) {
    double output = alpha_ * input + (1 - alpha_) * previous_output_;
    previous_output_ = output;
    return output;
}