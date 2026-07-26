#pragma once
#include <vector>
#include <atae_fp/oscillators/oscillator.h>
#include <numbers>

class SquareOscillator : public Oscillator {
public:
	std::vector<double> generate(double duration_s) override;
	void setDutyCycle(double duty_cycle);
	SquareOscillator() {
		setDutyCycle(0.5);
	}
protected:
	double duty_cycle_ = 0.5;
private:
	double threshold_ = std::numbers::pi;
};