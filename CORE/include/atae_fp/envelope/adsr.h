#pragma once

enum class AdsrState
{
    Idle,
    Attack,
    Decay,
    Sustain,
    Release
};

class Adsr
{
public:
    void setAttack(double attack, double sample_rate);
    void setDecay(double decay, double sample_rate);
    void setSustain(double sustain);
    void setRelease(double release, double sample_rate);
    void noteOn();
    void noteOff();
    double process();
    AdsrState getState();
private:
    double current_value_ = 0.0;
    AdsrState current_state_ = AdsrState::Idle;
    double attack_ = 0.0;
    double decay_ = 0.0;
    double decay_samples_ = 0.0;
    double sustain_ = 0.0;
    double release_ = 0.0;
};