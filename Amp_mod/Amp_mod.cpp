// Amp_mod.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<sndfile.h>

char path[] = "D:\Studia\ECE\Semestr 6\Electroacoustics\Laboratory\Lab2\svan files\svan files\pliki WAV\drill5k.wav";

int main()
{
	SNDFILE *infile, *outfile; //anonymus pointer to data which is private to the library
	SF_INFO sfinfo; //structure for passing data between the calling function and the library when opening for reading or writing
	infile = sf_open(path, SFM_READ, &sfinfo); //opens the sound file at the specified path
	if (infile == NULL) {
		std::cout << "ERROR";
	}
	else {
		std::cout << "SUCCESS";
	}
	sf_close(infile);
	return 1;
}
