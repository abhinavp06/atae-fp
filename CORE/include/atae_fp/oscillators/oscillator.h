#pragma once
#include <vector>

class Oscillator {
public:
	virtual ~Oscillator() = default;
	virtual std::vector<double> generate(const double duration_s) = 0;
	void setSampleRate(double sample_rate);
	void setFrequency(double frequency);
	void setAmplitude(double amplitude);
	void setPhase(double phase);
protected:
	void advancePhase();

	double sample_rate_ = 44100.0;
	double frequency_ = 0.0;
	double amplitude_ = 0.0;
	double phase_ = 0.0;
	double phase_increment_ = 0.0;

private:
	void updatePhaseIncrement();
};