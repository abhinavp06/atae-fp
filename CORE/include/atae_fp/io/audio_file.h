#pragma once
#include <vector>
#include <string>
#include <atae_fp/types/audio_buffer.h>

class AudioFile {
public:
	bool save(const std::string& path, const AudioBuffer& buffer, const double sample_rate);
};