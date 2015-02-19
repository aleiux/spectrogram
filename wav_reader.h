/**
copyright something something. author: Alex Liu. 
I don't know how it work. I'll figure it out later.
*/


#ifndef WAV_READER
#define WAV_READER
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdint.h>


struct wav_details {
	int audio_format;
	int num_channels;
	int sample_rate; 
	int bytes_per_sample;
	int num_samples;
	int file_size;
	wav_details(){}
	wav_details(int a_fmt, int nc, int sr, int bps, int ns, int fs);
};

void print_wav_info(wav_details info);


//wav reader should only be used on .wav files encoded in 16 or 32 bit PCM without compression or other fancy stuff.
//this class is only tested for 16 bit dual channel pcm. though in theory it should work for any number of channels for 32 bit as well.
class wav_reader {
	private:
		int format; //hopefully is 1
		int num_channels;
		int sample_rate;
		int bytes_per_sample; //confusing, but num_samples is actually bytes_per_sample * num_channels
		int num_samples;
		//
		FILE *fp;
		int data_start;
		int file_size;
		int current_pos;
	public:
		wav_reader() {}

		int wav_reader::open_file(char *file_name);
		
		//get the information for the wav file. you must call this in
		//order for the reader to know where the data starts and other important information
		wav_details wav_reader::get_wav_details(); 
		//print the wav file information
		void wav_reader::print_wav_info();

		//reset the file pointer to the start of the data chunk
		void wav_reader::set_stream_to_data();

		//gets the next sample as an int.
		/**
		
			get_type: 's' for skip
			returns the first value of the next sample.
			advances the stream pointer to the next sample (basically skips all the other channels)

			get_type: 'm' for mono
			returns the next value regardless of how many channels there are and 
			advances the stream pointer to the next value. 
		*/
		int wav_reader::get_next_sample(char get_type);
		
		//returns true if there exists another (complete) sample to read.
		int wav_reader::has_next_sample();

		////basic accessors.
		int wav_reader::get_format() {
			return format;
		}
		int wav_reader::get_num_channels() {
			return num_channels;
		}
		int wav_reader::get_sample_rate() {
			return sample_rate;
		}
		int wav_reader::get_bytes_per_sample() {
			return bytes_per_sample;
		}
		int wav_reader::get_num_samples() {
			return num_samples;
		}
		int wav_reader::get_current_position() {
			return current_pos;
		}

};






#endif /*wav_reader.h*/