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
#include "audio_amp.h"

int main(int argc, char *argv[])
{
	/*char in_path[] = "D:\\C++\\pliki_wav\\drill5k.wav";
	char out_path[] = "D:\\C++\\pliki_wav\\out.wav";
	int amp_db = 3;
	*/

	auto start = std::chrono::steady_clock::now();

	int i = NULL;
	if (argc == 1) {
		std::cout << "No arguments passed" << "\n";
		return 1;
	}
	else if (argc > 5) {
		std::cout << "Too little arguments" << "\n";
		return 1;
	}
	std::string path_in = argv[1];
	std::cout << path_in << "\n";
	std::string path_out = argv[2];
	std::cout << path_out << "\n";
	int amp = atoi(argv[3]);
	std::cout << amp << "\n";

	//audio_amp song1(path_in, path_out, amp);
	audio_amp song1;
	song1.read_file(path_in);
	song1.amp_write(path_out, amp);
	
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
	
	return 0;
}