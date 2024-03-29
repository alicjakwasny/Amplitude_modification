#ifndef AUDIO_AMP_H
#define AUDIO_AMP_H
#include <iostream>
#include<stdio.h>
#include<sndfile.h>
#include <filesystem>
#include <string.h>

enum class ErrorsAmpMod {
	SUCCESS = 0,
	SIZE_MISSMATCH = 1,
	FILE_ERROR = 2
};

class audio_amp {
	//std::string in_path;
	//std::string out_path;
	//int amp_db;

	SNDFILE *infile, *outfile; //anonymus pointer to data which is private to the library, gwiazdka przy outfile!
	SF_INFO sfinfo_in, sfinfo_out; //structure for passing data between the calling function and the library when opening for reading or writing

public:
	//audio_amp(std::string path_in, std::string path_out, int amp);

	ErrorsAmpMod amp_change(const std::vector<float>& table_in, int amp, std::vector<float>& table_out);

	ErrorsAmpMod read_file(const std::string &file_in);

	ErrorsAmpMod amp_write(const std::string &out_path, int &amp_db, int buff_items = 160);
};

#endif