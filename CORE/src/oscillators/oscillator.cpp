#include <atae_fp/oscillators/oscillator.h>
#include <numbers>

void Oscillator::updatePhaseIncrement() {
	phase_increment_ = (2.0 * std::numbers::pi * frequency_) / sample_rate_;
}

void Oscillator::advancePhase() {
	phase_ += phase_increment_;

	if (phase_ >= 2 * std::numbers::pi) phase_ -= 2 * std::numbers::pi;
}

void Oscillator::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
	updatePhaseIncrement();
}

void Oscillator::setFrequency(double frequency) {
	frequency_ = frequency;
	updatePhaseIncrement();
}

void Oscillator::setAmplitude(double amplitude) {
	amplitude_ = amplitude;
}

void Oscillator::setPhase(double phase) {
	phase_ = phase;
}