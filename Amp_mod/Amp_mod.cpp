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


char in_path[] = "D:\\Studia\\ECE\\Semestr 6\\Electroacoustics\\Laboratory\\Lab2\\svan files\\svan files\\pliki WAV\\drill5k.wav";
char out_path[] = "C:\\Users\\Alicja\\Documents\\Audio_out.wav";
int amp_db = 3;
int items;

int amp_change(float *table_in, int amp, float *table_out) {

	amp = 10 ^ (amp / 20); //dB -> V conversion
	for (int i = 0; table_in[i] != NULL; i++) {
		table_out[i] = table_in[i] * amp;
	}

	return 0;
}
int main()
{
	auto start = std::chrono::steady_clock::now();

	int i = NULL;

	SNDFILE *infile, *outfile; //anonymus pointer to data which is private to the library, gwiazdka przy outfile!
	SF_INFO sfinfo_in, sfinfo_out; //structure for passing data between the calling function and the library when opening for reading or writing
	
	std::filesystem::copy(in_path, out_path); //creating outfile

	infile = sf_open(in_path, SFM_READ, &sfinfo_in); //opens the sound file at the specified path
	outfile = sf_open(out_path, SFM_WRITE, &sfinfo_out);
	if (infile != nullptr) {
		std::cout << "SUCCESS";
	}
	else {
		std::cout << "ERROR";
	}

	/*if (infile != nullptr && outfile != nullptr) {
		std::cout << "SUCCESS";
	}
	else if (infile != nullptr) {
		std::cout << "ERROR, but infile is ok!";
	}
	else {
		std::cout << "FULL ERROR";
	}*/

	items = sfinfo_in.frames;

	float elements[items];	//should be a vector?
	float new_elements[items];

	//std::vector::vector<float> elements(items);

	sf_read_float(infile, elements, sfinfo_in.frames);

	for (int i = 0; i < 20; i++) {
		std::cout << "Element " << i << ": " << elements[i] << std::endl;
	}

	if (amp_change(elements, amp_db, new_elements) == 0) {
		std::cout << "Succesfully changed amplitude";
	}
	else {
		std::cout << "Something went wrong with the amplitude change";
	}

	sf_write_float(outfile, new_elements, sfinfo_out.frames);

	sf_close(infile);
	sf_close(outfile);

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;

	return 0;
}
