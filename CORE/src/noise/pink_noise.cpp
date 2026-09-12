#include <atae_fp/noise/pink_noise.h>

void PinkNoise::setSampleRate(double sample_rate) {
	sample_rate_ = sample_rate;
	white_noise_.setSampleRate(sample_rate);
}

AudioBuffer PinkNoise::generate(const double duration_s) {
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
}