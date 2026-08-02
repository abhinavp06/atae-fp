#include <atae_fp/types/audio_buffer.h>

class NaiveFilter {
public:
    double process(double input);
    void setGain(double gain);
private:
    double gain_ = 0.0;
};