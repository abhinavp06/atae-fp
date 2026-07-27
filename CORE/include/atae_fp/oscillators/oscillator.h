#pragma once
#include <atae_fp/types/audio_buffer.h>

class Oscillator {
public:
	virtual ~Oscillator() = default;
	virtual AudioBuffer generate(const double duration_s) = 0;
	void setSampleRate(double sample_rate);
	void setFrequency(double frequency);
	void setAmplitude(double amplitude);
	void setPhase(double phase);
protected:
	void advancePhase();

	double sample_rate_ = 44100.0;
	double frequency_ = 0.0;
	double amplitude_ = 1.0;
	double phase_ = 0.0;
	double phase_increment_ = 0.0;
	AudioBuffer buffer_;

private:
	void updatePhaseIncrement();
};