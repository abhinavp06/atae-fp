#include <atae_fp/noise/pink_noise.h>
#include <cmath>

void PinkNoise::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
	white_noise_.setSampleRate(sample_rate);
}

AudioBuffer PinkNoise::generate(const double duration_s) {
	int sample_count = static_cast<int>(sample_rate_ * duration_s);

	AudioBuffer result_buffer;
	result_buffer.samples.clear();
	result_buffer.samples.reserve(sample_count);

	std::vector<double> rows(NUM_ROWS, 0.0);

	double running_sum = 0.0;

	/**
	* 1. emit white noise at different frequencies... 2^k
	* 2. running_sum for better operations
	* 3. each row is an emitter...
	*/

	/**
	* rows[0] = "* * * * * * *"
	* rows[1] = "  *   *   *  "
	* rows[2] = "      *      "
	* 
	* octave = 2^k
	* so from 20 to 20,000 how many octaves?
	* lower octaves to have "more" energy compared to the higher ones because of density.. lower octaves have less width in terms of frequency, hence more energy per "point" (upto a certain precision)
	* 
	* so either fill all rows first and then remove.. or fill rows for a sample and then push that to the buffer?
	* latter is better
	* 
	* for(  i < total_samples )
	*	1. find out which rows need to be added
	*	2. add those rows, get a value, normalize it by the number of rows, save to buffer
	*/

	// filling up rows initially with an "energy" value
	for (int i = 0; i < NUM_ROWS; i++) {
		rows[i] = white_noise_.processSample();
	}

	// iterate over samples
	for (int i = 0; i < sample_count; i++) {
		// I have rows 0 to NUM_ROWS
		// find highest power of 2 which can contain the current value of i
		// that gives you the highest index till which rows should be added up to
		// add all row values till that index, normalize and push

		// naive loop to check for highest power of two
		int j = 0;
		while ((std::pow(2, j)) < i) {
			j++;
		}

		// now loop through all rows up until that index
		double row_sum = 0.0;
		for (int k = 0; k < j; k++) {
			row_sum += rows[k];
		}

		// normalize this sum
		// normalize by NUM_ROWS or j?
		row_sum /= NUM_ROWS;

		result_buffer.samples.push_back(row_sum);
	}

	return result_buffer;
}