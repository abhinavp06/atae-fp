#include <iostream>
#include <atae_fp/io/audio_file.h>

#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

bool AudioFile::save(const std::string& path, const AudioBuffer& buffer, const double sample_rate) {
	drwav_data_format format;
	format.container = drwav_container_riff;
	format.format =	DR_WAVE_FORMAT_IEEE_FLOAT;
	format.channels = 2;
	format.sampleRate = sample_rate;
	format.bitsPerSample = 32;
	
	drwav wav;
	const size_t buffer_size = buffer.samples.size();

	if (!drwav_init_file_write(&wav, path.c_str(), &format, NULL)) {
		std::cerr << "[Error] Could not open file for writing: " << path << std::endl;
		return false;
	}

	std::vector<float> temp_buffer(buffer_size);
	for (size_t i = 0; i < buffer_size; i++) {
		double sample = buffer.samples[i];

		// clamping to -1,1
		if (sample > 1.0) sample = 1.0;
		if (sample < -1.0) sample = -1.0;

		temp_buffer[i] = static_cast<float>(sample);
	}

	drwav_uint64 framesToWrite = buffer.samples.size() / format.channels;
	drwav_write_pcm_frames(&wav, framesToWrite, temp_buffer.data());

	drwav_uninit(&wav);

	std::cout << "[Save] Saved to " << path << std::endl;
	return true;
}