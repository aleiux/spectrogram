#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdint.h>
#include "dft.h"

#define PI 3.14159265


//returns the frequency per multiplier of the fundamental frequency.
// yes it's simple, but it saves the headache of trying to derive it or remember it properly.
float frequency_per_bucket(int sampling_frequency, int samples_per_transform) {
	return ((float)sampling_frequency)/samples_per_transform;
}

//solves the number of samples per transform needed to achieve the desired fundamental frequency.
float solve_from_fundamental(int sampling_frequency, int fundamental_frequency) {
	return sampling_frequency/fundamental_frequency;
}
//standard hann window /hamming. whatever.
float window_function(int value, int num_values) {
	return 0.5 * (1 - cos((2*PI*value)/(num_values - 1)));
}
float calculate_dft(int* values, int num_values, int m) {
	float w = (2*PI)/num_values;
	float real = 0;
	float imaginary = 0;
	for(int k = 0; k < num_values; k++) {
		real += values[k] * cos(-1*(w * m * k)) * window_function(k, num_values);
		imaginary += values[k] * sin(-1*(w*m*k)) * window_function(k, num_values);
	}
	return sqrt(real*real + imaginary*imaginary);
}



void spectral_band_linear(float* result, int* values, int num_values, int num_buckets) {
	for(int i = 1; i <= num_buckets; i++) {
		result[i-1] = calculate_dft(values, num_values, i);
	}
}

float spectral_sum(float* result, int* values, int num_values, int num_buckets, int low, int high) {
	float sum = 0;
	for(int i = low; i <= high; i++) {
		sum += calculate_dft(values, num_values, i);
	}
	return sum;
}




