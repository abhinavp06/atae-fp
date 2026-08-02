#include <atae_fp/envelope/adsr.h>

void Adsr::setAttack(double attack)
{
    attack_ = attack;
}

void Adsr::setDecay(double decay)
{
    decay_ = decay;
}

void Adsr::setSustain(double sustain)
{
    sustain_ = sustain;
}

void Adsr::setRelease(double release)
{
    release_ = release;
}

void Adsr::noteOn()
{
    current_value_ = 0.0;
    current_state_ = AdsrState::Idle;
}

void Adsr::noteOff()
{
    current_value_ = 0.0;
    current_state_ = AdsrState::Release;
}