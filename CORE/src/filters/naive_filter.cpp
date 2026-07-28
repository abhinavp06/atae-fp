#include <atae_fp/filters/naive_filter.h>

double NaiveFilter::process(double input) {
    return input - input * gain;
}