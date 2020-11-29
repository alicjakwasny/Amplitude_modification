// Amp_mod.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<sndfile.h>
#include <filesystem>
#include <chrono>
#include<vector>

enum class ErrorsAmpMod {
	SUCCESS = 0,
	SIZE_MISSMATCH = 1,
	FILE_ERROR = 2
};

ErrorsAmpMod amp_change(const std::vector<float>& table_in, int amp, std::vector<float>& table_out) {
	if (table_in.size() != table_out.size()) {
		return ErrorsAmpMod::SIZE_MISSMATCH;
	}
	amp = 10 ^ (amp / 20); //dB -> V conversion
	for (int i = 0; table_in[i] != NULL; i++) {
		table_out[i] = table_in[i] * amp;
	}
	
	return ErrorsAmpMod::SUCCESS;
}
int main()
{
	char in_path[] = "D:\\C++\\pliki_wav\\drill5k.wav";
	char out_path[] = "D:\\C++\\pliki_wav\\out.wav";
	int amp_db = 3;

	auto start = std::chrono::steady_clock::now();

	int i = NULL;

	SNDFILE *infile, *outfile; //anonymus pointer to data which is private to the library, gwiazdka przy outfile!
	SF_INFO sfinfo_in, sfinfo_out; //structure for passing data between the calling function and the library when opening for reading or writing
	
	infile = sf_open(in_path, SFM_READ, &sfinfo_in); //opens the sound file at the specified path

	sfinfo_out = sfinfo_in;

	/*if (sf_format_check(&sfinfo_out)) {
		std::cout << "sfinfo_out is ok";
	}*/

	outfile = sf_open(out_path, SFM_WRITE, &sfinfo_out);

	const int items_count = 160;

	std::vector<float> input_data(items_count);
	std::vector<float> output_data(items_count);

	while (sf_read_float(infile, input_data.data(), input_data.size()-1)) {
		/*for (int i = 0; i < 2; i++) {
			if (input_data[i]) {
				std::cout << "Element " << i << ": " << input_data[i] << std::endl;
			}
		}*/
		ErrorsAmpMod err = amp_change(input_data, amp_db, output_data);
		if ( ErrorsAmpMod::SUCCESS != err) {
			return 1;
		}
		sf_write_float(outfile, output_data.data(), output_data.size());
	}

	sf_close(infile);
	sf_close(outfile);

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
	
	return 0;
}
