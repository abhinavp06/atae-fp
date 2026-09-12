#include <atae_fp/noise/pink_noise.h>
#include <cmath>
//#include <iostream>

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
	* update_period = 2^k samples
	* so from 20 to 20,000 how many octaves?
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
		running_sum += rows[i];
	}

	uint32_t n = 0;

	// iterate over samples
	for (int i = 0; i < sample_count; i++) {
		// Every row contributes to every output sample.
		// Rows differ only in how frequently their held value is refreshed.
		//
		// row 0 -> every 1 sample
		// row 1 -> every 2 samples
		// row 2 -> every 4 samples
		// row 3 -> every 8 samples
		//
		// XOR between consecutive counter values tells us which binary
		// bits changed, which directly tells us which rows need updating.

		// naive loop to check for highest power of two
		//int j = 0;
		//while ((std::pow(2, j)) <= i) {
		//	j++;
		//}

		// now loop through all rows up until that index
		//double row_sum = 0.0;
		//for (int k = 0; k < j; k++) {
		//	row_sum += rows[k];
		//}

		// what rows to update?
		// only those rows where 2^k is a multiple of 2^row_index
		// row that should be updated - position of 1s in binary representation of i
		// 
		// bit changes when sample counter increases
		// row 0 updates every sample.. row 1 updates once every 2 samples.. row 2 updates once every 4 samples and so on..
		// 
		// perform XOR between i and i-1.. that gives which bits changed.. only update those rows

		result_buffer.samples.push_back(running_sum / NUM_ROWS);

		n++;
		uint32_t changed_bits = n ^ (n - 1);
		for (int k = 0; k < NUM_ROWS; k++) {
			if (changed_bits & (1u << k)) {
				running_sum -= rows[k];
				rows[k] = white_noise_.processSample();
				running_sum += rows[k];
			}
		}
		// normalize this sum
		// normalize by NUM_ROWS or j?
		//row_sum /= NUM_ROWS;
		//std::cout << row_sum << std::endl;
	}

	return result_buffer;
}