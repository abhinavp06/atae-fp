#include <atae_fp/filters/one_pole_lpf.h>
#include <cmath>
#include <numbers>

void OnePoleLpf::calculateAlpha() {
    alpha_ = 1.0 - std::exp(-2.0 * std::numbers::pi * cutoff_frequency_ / sample_rate_ );
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