#pragma once
#include <vector>

class Oscillator {
public:
	virtual ~Oscillator() = default;
	virtual std::vector<double> generate(const double duration_s) = 0;
	virtual void setSampleRate(double sample_rate);
	virtual void setFrequency(double frequency);
	virtual void setAmplitude(double amplitude);
	virtual void setPhase(double phase);
protected:
	void advancePhase();

	double sample_rate_s_ = 44100.0;
	double frequency_ = 0.0;
	double amplitude_ = 0.0;
	double phase_ = 0.0;
	double phase_increment_ = 0.0;
};