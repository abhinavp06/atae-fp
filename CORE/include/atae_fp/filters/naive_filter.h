#include <atae_fp/types/audio_buffer.h>

class NaiveFilter {
public:
    double process(double input);
private:
    double gain = 0.0;
}