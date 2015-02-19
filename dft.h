#ifndef DFT_H
#define DFT_H
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

//returns the frequency per multiplier of the fundamental frequency.
// yes it's simple, but it saves the headache of trying to derive it or remember it properly.
float frequency_per_bucket(int sampling_frequency, int samples_per_transform);


//calculates the discrete fourier transform over the given values, which there should be
//num_values of. m is the multiplier on the fundamental frequency. (p/2pi)
//return value is the magnitude of the result
float calculate_dft(int* values, int num_values, int m);


/*
	returns a float array of the results of taking the DFT over the values at multipliers of the fundamental frequency from 1 to num_buckets (inclusive).
	result should be an array of size num_buckets.
	gets dft's linearly and might not be a great tool for practical purposes.
*/
void spectral_band_linear(float* result, int* values, int num_values, int num_buckets);


/* provides a sum from bucket low to bucket high (inclusive) */
float spectral_sum(int* values, int num_values, int num_buckets, int low, int high);

#endif /*dft.h*/