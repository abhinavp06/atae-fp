#include <atae_fp/envelope/adsr.h>

void Adsr::setAttack(double attack, double sample_rate)
{
    if (attack <= 0.0)
    {
        attack_ = 1.0;
    }
    else
    {
        attack_ = 1.0 / (attack * sample_rate);
    }
}

void Adsr::setDecay(double decay, double sample_rate)
{
    if (decay <= 0.0)
    {
        decay_ = 1.0;
    }
    else
    {
        decay_ = 1.0 / (decay * sample_rate);
    }
}

void Adsr::setSustain(double sustain)
{
    sustain_ = sustain;
}

void Adsr::setRelease(double release, double sample_rate)
{
    if (release <= 0.0)
    {
        release_ = current_value_;
    }
    else
    {
        release_ = current_value_ / (release * sample_rate);
    }
}

void Adsr::noteOn()
{
    current_value_ = 0.0;
    current_state_ = AdsrState::Attack;
}

void Adsr::noteOff()
{
    current_value_ = 0.0;
    current_state_ = AdsrState::Release;
}

double Adsr::process()
{
    switch (current_state_)
    {
    case AdsrState::Idle:
        return 0.0;
    case AdsrState::Attack:
        if (current_value_ >= 1.0)
        {
            current_state_ = AdsrState::Decay;
            current_value_ = 1.0;
        }
        else
        {
            current_value_ += attack_;
        }
        break;
    case AdsrState::Decay:
        if (current_value_ <= sustain_)
        {
            current_value_ = sustain_;
            current_state_ = AdsrState::Sustain;
        }
        else
        {
            current_value_ -= decay_;
        }
        break;
    }

    return current_value_;
}