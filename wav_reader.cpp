
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdint.h>
#include <stdint.h>
#include "wav_reader.h"



wav_details::wav_details(int a_fmt, int nc, int sr, int bps, int ns, int fs) {
		audio_format = a_fmt; 
		num_channels = nc;
		sample_rate = sr;
		bytes_per_sample = bps;
		num_samples = ns;
		file_size = fs;
}

void print_wav_info(wav_details info) {
	std::cout<<".wav file information for ";
	std::cout<<"\naudio format: " << info.audio_format;
	std::cout<<"\nnum channels: " << info.num_channels;
	std::cout<<"\nsample rate: " << info.sample_rate;
	std::cout<<"\nbytes per sample: " << info.bytes_per_sample << " (x" << info.num_channels << " channels)";
	std::cout<<"\nnum samples: " <<info.num_samples;
	std::cout<<"\nfile size:   " <<info.file_size <<" bytes\n";
}


//class implementation below:

//returns whether or not it was successful.
int wav_reader::open_file(char *file_name) {
	fp = fopen(file_name, "rb");
	if(fp) {
		return 1;
	} else {
		return 0;
	}
}
		
//get the information for the wav file
wav_details wav_reader::get_wav_details() {
	rewind(fp);
	if(fp) {
		unsigned char id[5]; //RIFF
		id[4] = '\0'; 
		fread(id, 1, 4, fp); 

		int chunk_size[1];
		fread(chunk_size, 4, 1, fp);

		char format[5]; //WAVE
		format[4] = '\0';
		fread(format, 1, 4, fp);

		char subchunk1ID[5]; // fmt
		subchunk1ID[4] = '\0';
		fread(subchunk1ID, 1, 4, fp);
	
		int subchunk_size[1];
		fread(subchunk_size, 4, 1, fp);

		int16_t audioFormat[1];
		fread(audioFormat, 2, 1, fp);

		int16_t numChannels[1];
		fread(numChannels, 2, 1, fp);

		int samp_rate[1];
		fread(samp_rate, 4, 1, fp);

		int byte_rate[1];
		fread(byte_rate, 4, 1, fp);

		int16_t blockAlign[1];
		fread( blockAlign, 2, 1, fp);

		int16_t bitsPerSample[1];
		fread( bitsPerSample, 2, 1, fp);

		int16_t extraBytes[1];
		fread(extraBytes, 2, 1, fp);

		fseek(fp, long(subchunk_size[0] + 20), SEEK_SET);

		char subchunk2ID[5];
		subchunk2ID[4] = '\0';
		fread(subchunk2ID, 1, 4, fp);

		int data_size[1];
		fread(data_size, 4, 1, fp);

		int current_pos = ftell(fp);

		wav_reader::format = audioFormat[0] ;
		wav_reader::num_channels = numChannels[0];
		wav_reader::sample_rate = samp_rate[0];
		wav_reader::bytes_per_sample = bitsPerSample[0]/8;
		wav_reader::num_samples = data_size[0]/(numChannels[0] * bytes_per_sample);
		wav_reader::data_start = current_pos;
		fseek(fp, 0L, SEEK_END);
		wav_reader::file_size = ftell(fp);
		wav_reader::current_pos = ftell(fp);
		return wav_details(wav_reader::format, wav_reader::num_channels, wav_reader::sample_rate, wav_reader::bytes_per_sample, wav_reader::num_samples, wav_reader::file_size);

	}
	else {
		std::cout<<"error fp is null\n";
		return wav_details();
	}	
}
//print the wav file information
void wav_reader::print_wav_info() {
	rewind(fp);
	if(fp) {
		unsigned char id[5]; //RIFF
		id[4] = '\0'; 
		fread(id, 1, 4, fp); 
		std::cout<<id<<" :first 4 bytes \n"; 
		
		int chunk_size[1];
		fread(chunk_size, 4, 1, fp);
		std::cout<<chunk_size[0]<<" chunk size\n";
		
		char format[5]; //WAVE
		format[4] = '\0';
		fread(format, 1, 4, fp);
		std::cout<<format<<" :format\n";

		char subchunk1ID[5]; // fmt
		subchunk1ID[4] = '\0';
		fread(subchunk1ID, 1, 4, fp);
		std::cout<<subchunk1ID<<" :sub chunk 1 ID\n";
			
		int subchunk_size[1];
		fread(subchunk_size, 4, 1, fp);
		std::cout<<subchunk_size[0]<<" :subchunk size \n";

		int16_t audioFormat[1];
		fread(audioFormat, 2, 1, fp);
		std::cout<<audioFormat[0]<<" :audio format. \n";

		int16_t numChannels[1];
		fread(numChannels, 2, 1, fp);
		std::cout<<numChannels[0]<<" :number of channels. \n";

		int samp_rate[1];
		fread(samp_rate, 4, 1, fp);
		std::cout<<samp_rate[0]<<" :sample rate \n";

		int byte_rate[1];
		fread(byte_rate, 4, 1, fp);
		std::cout<<byte_rate[0]<<" :byte rate \n";

		int16_t blockAlign[1];
		fread( blockAlign, 2, 1, fp);
		std::cout<<blockAlign[0]<<" :block Align \n";
		
		int16_t bitsPerSample[1];
		fread( bitsPerSample, 2, 1, fp);
		std::cout<<bitsPerSample[0]<<" :bits per sample \n";

		int16_t extraBytes[1];
		fread(extraBytes, 2, 1, fp);
		std::cout<<extraBytes[0]<<" :extra bytes before data??\n"; //accounts for extra bytes.
		fseek(fp, long(subchunk_size[0] + 20), SEEK_SET);

		char subchunk2ID[5];
		subchunk2ID[4] = '\0';
		fread(subchunk2ID, 1, 4, fp);
		std::cout<<subchunk2ID<<" :sub chunk 2 ID \n";

		int data_size[1];
		fread(data_size, 4, 1, fp);
		std::cout<<data_size[0]<<" :data size (num bytes) \n";

		int current_pos = ftell(fp);
	}
	else {
		std::cout<<"error fp is null\n";
	}
}

//reset the file pointer to the start of the data chunk
void wav_reader::set_stream_to_data() {
	fseek(fp, long(wav_reader::data_start), SEEK_SET);
	current_pos = data_start;
}

//gets the next sample as an int.
/**
get_type: 's' for skip
returns the first value of the next sample.
advances the stream pointer to the next sample (basically skips all the other channels)

get_type: 'm' for mono
returns the next value regardless of how many channels there are and 
advances the stream pointer to the next value. 
*/
int wav_reader::get_next_sample(char get_type) {
	if(get_type == 's') {
		if(bytes_per_sample == 2) {
			int16_t ret[1];
			fread(ret, 2, 1, fp);
			fseek(fp, long(current_pos + bytes_per_sample), SEEK_SET);
			current_pos += 2*num_channels;
			return (int)ret[0];
		}
		else if(bytes_per_sample == 4) {
			int32_t ret[1];
			fread(ret, 4, 1, fp);
			fseek(fp, long(current_pos + bytes_per_sample), SEEK_SET);
			current_pos += 4*num_channels;
			return (int)ret[0];
		}
	}
	else if(get_type == 'm') {
		if(bytes_per_sample == 2) {
			int16_t ret[1];
			fread(ret, 2, 1, fp);
			current_pos+=2;
			return (int)ret[0];
		}
		else if(bytes_per_sample == 4) {
			int32_t ret[1];
			fread(ret, 4, 1, fp);
			current_pos += 4;
			return (int)ret[0];
		}
	}
	else {
		std::cout<<"bad type for get_next_sample\n";
		return 0;
	}
	std::cout<<"incorrect number of bytes per sample\n";
	return 0;
}

//returns true if there exists another (complete) sample to read.
//might return false on the last sample.
int wav_reader::has_next_sample() {
	if(current_pos + bytes_per_sample < file_size) {
		return 1;
	}
	else {
		return 0;
	}

}
