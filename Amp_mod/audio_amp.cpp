#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<sndfile.h>
#include <filesystem>
#include<vector>
#include "audio_amp.h"

audio_amp::audio_amp(std::string path_in, std::string path_out, int amp) {
	in_path = path_in;
	/*in_path = ReplaceAll(in_path, std::string("\ "), std::string("\\")); //czy da siê to zrobiæ inaczej ni¿ z t¹ spacj¹ po \.
	std::cout << in_path << "\n";*/

	out_path = path_out;
	/*out_path = ReplaceAll(out_path, std::string("\ "), std::string("\\"));
	std::cout << out_path << "\n";*/

	amp_db = amp;
}

ErrorsAmpMod audio_amp::amp_change(const std::vector<float>& table_in, int amp, std::vector<float>& table_out) {
	if (table_in.size() != table_out.size()) {
		return ErrorsAmpMod::SIZE_MISSMATCH;
	}
	float amp1 = std::powf(10.0f, (static_cast<float>(amp) / 20.0f)); //conversion from dB
	for (int i = 0; table_in[i] != NULL; i++) {
		table_out[i] = table_in[i] * amp1;
	}

	return ErrorsAmpMod::SUCCESS;
}

ErrorsAmpMod audio_amp::read_file() {
	const char* in = in_path.c_str();
	infile = sf_open(in, SFM_READ, &sfinfo_in);
	return ErrorsAmpMod::SUCCESS;
}

ErrorsAmpMod audio_amp::amp_write(int buff_items) {
	sfinfo_out = sfinfo_in;

	const char* out = out_path.c_str();
	outfile = sf_open(out, SFM_WRITE, &sfinfo_out);

	const int items_count = buff_items;

	std::vector<float> input_data(items_count);
	std::vector<float> output_data(items_count);

	while (sf_read_float(infile, input_data.data(), input_data.size() - 1)) {
		ErrorsAmpMod err = amp_change(input_data, amp_db, output_data);
		if (ErrorsAmpMod::SUCCESS != err) {
			return ErrorsAmpMod::SIZE_MISSMATCH; //size mismatch?
		}
		sf_write_float(outfile, output_data.data(), output_data.size());
	}

	sf_close(infile);
	sf_close(outfile);

	return ErrorsAmpMod::SUCCESS;
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}