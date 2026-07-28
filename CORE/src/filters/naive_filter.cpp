#include <atae_fp/filters/naive_filter.h>

void NaiveFilter::setGain(double gain) {
    gain_ = gain;
}

double NaiveFilter::process(double input) {
    return input - input * gain_;
}